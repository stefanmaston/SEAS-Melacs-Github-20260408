#include "board_pins.h"
#include "node_display.h"
#include "node_logic.h"

#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

#include <string.h>

#define OLED_ADDR 0x3C

static uint8_t g_fb[NODE_FB_SIZE];
static int g_ow_busy;
static uint32_t g_ow_at;
static uint8_t g_frame[64];
static int g_frame_n;
static uint32_t g_frame_us;

static void cs_init(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 1);
}

static void spi_mode(int max_chip)
{
    spi_set_format(spi0, 8, SPI_CPOL_0,
                   max_chip ? SPI_CPHA_1 : SPI_CPHA_0, SPI_MSB_FIRST);
}

static void spi_xfer(int cs, int max_chip, const uint8_t *tx, uint8_t *rx, int n)
{
    spi_mode(max_chip);
    gpio_put(cs, 0);
    busy_wait_us(1);
    spi_write_read_blocking(spi0, tx, rx, (size_t)n);
    gpio_put(cs, 1);
}

static void chip_write(int cs, int max_chip, uint8_t reg, uint8_t value)
{
    uint8_t tx[2] = { reg, value };
    uint8_t rx[2];

    spi_xfer(cs, max_chip, tx, rx, 2);
}

static void chip_read(int cs, int max_chip, uint8_t reg, uint8_t *dst, int n)
{
    uint8_t tx[8];
    uint8_t rx[8];
    int i;

    tx[0] = reg;
    for (i = 1; i <= n; i++) {
        tx[i] = 0;
    }
    spi_xfer(cs, max_chip, tx, rx, n + 1);
    for (i = 0; i < n; i++) {
        dst[i] = rx[i + 1];
    }
}

static void dac_write(int channel, uint16_t code)
{
    uint16_t word = (uint16_t)(0x3000u | ((channel & 1) << 15) | (code & 0x0FFFu));
    uint8_t tx[2] = { (uint8_t)(word >> 8), (uint8_t)word };
    uint8_t rx[2];

    spi_xfer(BOARD_PIN_CS_DAC, 0, tx, rx, 2);
}

static void oled_cmd(uint8_t cmd)
{
    uint8_t buf[2] = { 0x00, cmd };

    i2c_write_blocking(i2c1, OLED_ADDR, buf, 2, false);
}

static void oled_init(void)
{
    static const uint8_t seq[] = {
        0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x14,
        0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1,
        0xDB, 0x40, 0xA4, 0xA6, 0xAF
    };
    int i;

    for (i = 0; i < (int)sizeof seq; i++) {
        oled_cmd(seq[i]);
    }
}

static void oled_flush(const uint8_t *fb)
{
    int page;

    oled_cmd(0x21);
    oled_cmd(0);
    oled_cmd(127);
    oled_cmd(0x22);
    oled_cmd(0);
    oled_cmd(7);
    for (page = 0; page < 8; page++) {
        uint8_t pkt[129];

        pkt[0] = 0x40;
        memcpy(pkt + 1, fb + page * NODE_FB_W, NODE_FB_W);
        i2c_write_blocking(i2c1, OLED_ADDR, pkt, 129, false);
    }
}

static void ow_low(void)
{
    gpio_set_dir(BOARD_PIN_OW, GPIO_OUT);
    gpio_put(BOARD_PIN_OW, 0);
}

static void ow_release(void)
{
    gpio_set_dir(BOARD_PIN_OW, GPIO_IN);
    gpio_pull_up(BOARD_PIN_OW);
}

static int ow_reset(void)
{
    int present;

    ow_low();
    busy_wait_us(480);
    ow_release();
    busy_wait_us(70);
    present = !gpio_get(BOARD_PIN_OW);
    busy_wait_us(410);
    return present;
}

static void ow_write_bit(int bit)
{
    ow_low();
    if (bit) {
        busy_wait_us(6);
        ow_release();
        busy_wait_us(64);
    } else {
        busy_wait_us(60);
        ow_release();
        busy_wait_us(10);
    }
}

static int ow_read_bit(void)
{
    int bit;

    ow_low();
    busy_wait_us(3);
    ow_release();
    busy_wait_us(10);
    bit = gpio_get(BOARD_PIN_OW);
    busy_wait_us(53);
    return bit;
}

static void ow_write(uint8_t value)
{
    int i;

    for (i = 0; i < 8; i++) {
        ow_write_bit(value & 1);
        value >>= 1;
    }
}

static uint8_t ow_read(void)
{
    uint8_t value = 0;
    int i;

    for (i = 0; i < 8; i++) {
        if (ow_read_bit()) {
            value |= (uint8_t)(1u << i);
        }
    }
    return value;
}

static int ow_start(void)
{
    if (!ow_reset()) {
        return 0;
    }
    ow_write(0xCC);
    ow_write(0x44);
    return 1;
}

static int ow_fetch(int16_t *c10)
{
    uint8_t lo;
    uint8_t hi;
    int16_t raw;

    if (!ow_reset()) {
        return 0;
    }
    ow_write(0xCC);
    ow_write(0xBE);
    lo = ow_read();
    hi = ow_read();
    raw = (int16_t)((hi << 8) | lo);
    *c10 = (int16_t)(raw * 10 / 16);
    return 1;
}

static uint16_t adc_at(int input)
{
    adc_select_input(input);
    return adc_read();
}

static void read_sensors(NodeSample *sample)
{
    uint8_t raw[4];
    int32_t aligned;

    memset(sample, 0, sizeof *sample);
    chip_read(BOARD_PIN_CS_TC, 1, 0x0C, raw, 3);
    aligned = ((int32_t)raw[0] << 16) | ((int32_t)raw[1] << 8) | raw[2];
    if (aligned & 0x800000) {
        aligned |= ~0xFFFFFF;
    }
    sample->tc_raw19 = aligned >> 5;
    chip_read(BOARD_PIN_CS_TC, 1, 0x0F, raw, 1);
    sample->tc_fault = raw[0] != 0;

    chip_read(BOARD_PIN_CS_RTD, 1, 0x01, raw, 2);
    sample->rtd_code = (uint16_t)(((raw[0] << 8) | raw[1]) >> 1);
    sample->rtd_fault = raw[1] & 1;

    sample->adc_lm35 = adc_at(0);
    sample->adc_v0 = adc_at(1);
    sample->adc_ma = adc_at(2);
    sample->adc_v1 = adc_at(3);
    sample->di = 0;
    if (gpio_get(BOARD_PIN_DI0)) sample->di |= 1u;
    if (gpio_get(BOARD_PIN_DI1)) sample->di |= 2u;
    if (gpio_get(BOARD_PIN_DI2)) sample->di |= 4u;
    if (gpio_get(BOARD_PIN_DI3)) sample->di |= 8u;

    if (!g_ow_busy) {
        g_ow_busy = ow_start();
        g_ow_at = time_us_32();
        sample->ow_ok = 0;
    } else if ((time_us_32() - g_ow_at) > 800000u) {
        sample->ow_ok = ow_fetch(&sample->ow_c10);
        g_ow_busy = 0;
    }
}

static void apply_outputs(const NodeOutputs *out)
{
    int i;
    static const int pins[4] = {
        BOARD_PIN_DO0, BOARD_PIN_DO1, BOARD_PIN_DO2, BOARD_PIN_DO3
    };

    dac_write(0, scale_dac_mv(out->ao_mv));
    dac_write(1, scale_dac_ca(out->ao_ca));
    for (i = 0; i < 4; i++) {
        gpio_put(pins[i], (out->dout >> i) & 1);
    }
}

static void uart_service(NodeImage *node)
{
    uint8_t rsp[64];

    while (uart_is_readable(uart0) && g_frame_n < (int)sizeof g_frame) {
        g_frame[g_frame_n++] = uart_getc(uart0);
        g_frame_us = time_us_32();
    }
    if (g_frame_n == 0) {
        return;
    }
    if ((time_us_32() - g_frame_us) < 4000u && g_frame_n < (int)sizeof g_frame) {
        return;
    }
    {
        int n = node_modbus(node, g_frame, g_frame_n, rsp, (int)sizeof rsp, time_us_32() / 1000u);

        if (n > 0) {
            gpio_put(BOARD_PIN_RS485_DE, 1);
            uart_write_blocking(uart0, rsp, (size_t)n);
            uart_tx_wait_blocking(uart0);
            gpio_put(BOARD_PIN_RS485_DE, 0);
        }
    }
    g_frame_n = 0;
}

int main(void)
{
    NodeImage node;
    int i;
    static const int outputs[4] = {
        BOARD_PIN_DO0, BOARD_PIN_DO1, BOARD_PIN_DO2, BOARD_PIN_DO3
    };
    static const int inputs[4] = {
        BOARD_PIN_DI0, BOARD_PIN_DI1, BOARD_PIN_DI2, BOARD_PIN_DI3
    };

    node_init(&node);
    spi_init(spi0, 1000 * 1000);
    gpio_set_function(BOARD_PIN_SPI_SCK, GPIO_FUNC_SPI);
    gpio_set_function(BOARD_PIN_SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(BOARD_PIN_SPI_MISO, GPIO_FUNC_SPI);
    cs_init(BOARD_PIN_CS_TC);
    cs_init(BOARD_PIN_CS_RTD);
    cs_init(BOARD_PIN_CS_DAC);
    chip_write(BOARD_PIN_CS_TC, 1, 0x80, 0x80);
    chip_write(BOARD_PIN_CS_TC, 1, 0x81, 0x03);
    chip_write(BOARD_PIN_CS_RTD, 1, 0x80, 0xD0);

    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(BOARD_PIN_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(BOARD_PIN_I2C_SCL, GPIO_FUNC_I2C);
    oled_init();
    display_begin(g_fb);

    uart_init(uart0, 9600);
    gpio_set_function(BOARD_PIN_UART_TX, GPIO_FUNC_UART);
    gpio_set_function(BOARD_PIN_UART_RX, GPIO_FUNC_UART);
    gpio_init(BOARD_PIN_RS485_DE);
    gpio_set_dir(BOARD_PIN_RS485_DE, GPIO_OUT);
    gpio_put(BOARD_PIN_RS485_DE, 0);

    adc_init();
    adc_gpio_init(BOARD_PIN_ADC_LM35);
    adc_gpio_init(BOARD_PIN_ADC_V0);
    adc_gpio_init(BOARD_PIN_ADC_MA);
    adc_gpio_init(BOARD_PIN_ADC_V1);

    gpio_init(BOARD_PIN_OW);
    ow_release();
    for (i = 0; i < 4; i++) {
        gpio_init(inputs[i]);
        gpio_set_dir(inputs[i], GPIO_IN);
        gpio_init(outputs[i]);
        gpio_set_dir(outputs[i], GPIO_OUT);
        gpio_put(outputs[i], 0);
    }

    for (;;) {
        NodeSample sample;
        NodeOutputs out;

        read_sensors(&sample);
        node_on_sample(&node, &sample);
        display_set_c10(g_fb, node_display_c10(&node));
        if (display_dirty()) {
            oled_flush(g_fb);
            display_clear_dirty();
        }
        node_outputs(&node, time_us_32() / 1000u, &out);
        apply_outputs(&out);
        uart_service(&node);
    }
}
