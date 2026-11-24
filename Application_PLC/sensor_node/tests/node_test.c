#include "board_pins.h"
#include "modbus_rtu.h"
#include "node_display.h"
#include "node_logic.h"

#include <stdio.h>
#include <string.h>

static int g_fails;

static void expect(int cond, const char *msg)
{
    if (!cond) {
        fprintf(stderr, "fel: %s\n", msg);
        g_fails++;
    }
}

static const int g_used[BOARD_USED_COUNT] = {
    BOARD_PIN_UART_TX, BOARD_PIN_UART_RX, BOARD_PIN_SPI_SCK, BOARD_PIN_SPI_MOSI,
    BOARD_PIN_SPI_MISO, BOARD_PIN_CS_TC, BOARD_PIN_CS_RTD, BOARD_PIN_CS_DAC,
    BOARD_PIN_RS485_DE, BOARD_PIN_OW, BOARD_PIN_I2C_SDA, BOARD_PIN_I2C_SCL,
    BOARD_PIN_DI0, BOARD_PIN_DI1, BOARD_PIN_DI2, BOARD_PIN_DI3,
    BOARD_PIN_DO0, BOARD_PIN_DO1, BOARD_PIN_DO2, BOARD_PIN_DO3,
    BOARD_PIN_ADC_LM35, BOARD_PIN_ADC_V0, BOARD_PIN_ADC_MA, BOARD_PIN_ADC_V1
};

static void test_pins(void)
{
    int seen[BOARD_GPIO_COUNT];
    int i;

    memset(seen, 0, sizeof seen);
    for (i = 0; i < BOARD_USED_COUNT; i++) {
        int pin = g_used[i];

        expect(pin >= 0 && pin < BOARD_GPIO_COUNT, "ben inom GPIO0–GPIO29");
        expect(!seen[pin], "benet används bara en gång");
        seen[pin] = 1;
    }
    for (i = 0; i < BOARD_FREE_COUNT; i++) {
        expect(!seen[BOARD_FREE_FIRST + i], "GPIO20–GPIO25 är lediga");
    }
    expect(g_used[20] == 26 && g_used[21] == 27 && g_used[22] == 28 &&
               g_used[23] == 29,
           "de fyra ADC-benen är GPIO26–GPIO29");
    expect(BOARD_GPIO_COUNT - BOARD_USED_COUNT == BOARD_FREE_COUNT,
           "sex ben blir över");
}

static void test_scale(void)
{
    expect(scale_lm35_c10(0) == 0, "LM35 noll");
    expect(scale_lm35_c10(745) == 600, "LM35 60,0 grader");
    expect(scale_lm35_c10(4095) == 1500, "LM35 tak 150 grader");
    expect(scale_div_mv(0) == 0, "delare noll");
    expect(scale_div_mv(3792) == 9998, "delare nära 10 V");
    expect(scale_ma_c100(745) == 400, "4,00 mA");
    expect(scale_ma_c100(3723) == 2000, "20,00 mA");
    expect(scale_tc_c10(25 * 128, 0) == 250, "termoelement 25,0 grader");
    expect(scale_tc_c10(523008, 0) == -100, "termoelement -10,0 grader");
    expect(scale_tc_c10(0, 1) == NODE_TEMP_FAULT, "termoelement fel");
    expect(scale_pt1000_c10(8192, 0) == 0, "PT1000 vid 0 grader");
    expect(scale_pt1000_c10(11346, 0) == 1000, "PT1000 vid 100 grader");
    expect(scale_pt1000_c10(8192, 1) == NODE_TEMP_FAULT, "PT1000 fel");
    expect(scale_dac_mv(10000) == 4095, "DA 10 V är full skala");
    expect(scale_dac_mv(0) == 0, "DA 0 V");
    expect(scale_dac_ca(2000) == 4095, "DA 20 mA är full skala");
    expect(scale_dac_ca(400) == 819, "DA 4 mA");
}

static int frame_ok(const uint8_t *frame, int len)
{
    uint16_t got;
    uint16_t expect_crc;

    if (len < 4) {
        return 0;
    }
    got = (uint16_t)frame[len - 2] | ((uint16_t)frame[len - 1] << 8);
    expect_crc = modbus_crc(frame, len - 2);
    return got == expect_crc;
}

static void test_silent_and_modbus(void)
{
    NodeImage node;
    NodeSample sample;
    NodeOutputs out;
    uint8_t req[8];
    uint8_t rsp[32];
    uint16_t regs[4];
    int n;
    uint8_t known[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x01 };

    memset(&sample, 0, sizeof sample);
    sample.adc_lm35 = 745;
    sample.tc_fault = 1;
    sample.rtd_fault = 1;
    node_init(&node);
    node_on_sample(&node, &sample);
    node_outputs(&node, 0, &out);
    expect(out.ao_mv == 0 && out.ao_ca == 0 && out.dout == 0, "tyst master ger säkert läge");
    expect(node_display_c10(&node) == 600, "skärmen visar LM35 utan master");

    expect(modbus_crc(known, 6) == 0x0A84, "känd Modbus-CRC");
    n = modbus_rtu_read_req(req, 8, NODE_SLAVE_ID, 4, NODE_IR_LM35, 1);
    expect(n == 8 && frame_ok(req, n), "läsbegäran");
    n = node_modbus(&node, req, n, rsp, (int)sizeof rsp, 1000);
    expect(n == 7 && frame_ok(rsp, n), "slavsvar");
    expect(modbus_rtu_parse_read(rsp, n, NODE_SLAVE_ID, regs, 4) == 1, "ett register");
    expect(regs[0] == 600, "samma tal som på skärmen");

    req[0] = NODE_SLAVE_ID;
    req[1] = 6;
    req[2] = 0;
    req[3] = NODE_HR_AO_MV;
    req[4] = 0x13;
    req[5] = 0x88;
    n = 6;
    {
        uint16_t crc = modbus_crc(req, 6);
        req[6] = (uint8_t)crc;
        req[7] = (uint8_t)(crc >> 8);
    }
    n = node_modbus(&node, req, 8, rsp, (int)sizeof rsp, 1000);
    expect(n == 8, "skrivning kvitteras");
    node_outputs(&node, 1000, &out);
    expect(out.ao_mv == 5000 && out.dout == 0, "utgången följer holdingregistret");
    node_outputs(&node, 1000 + NODE_WATCH_MS + 1, &out);
    expect(out.ao_mv == 0 && out.dout == 0, "tystnad släcker utgången");
    expect(node_display_c10(&node) == 600, "skärmen ligger kvar");

    req[3] = NODE_HR_MODE;
    req[4] = 0;
    req[5] = 2;
    {
        uint16_t crc = modbus_crc(req, 6);
        req[6] = (uint8_t)crc;
        req[7] = (uint8_t)(crc >> 8);
    }
    n = node_modbus(&node, req, 8, rsp, (int)sizeof rsp, 2000);
    expect(n == 5 && rsp[1] == 0x86, "ogiltigt läge avvisas");
}

static void test_display(void)
{
    uint8_t fb[NODE_FB_SIZE];
    uint8_t before[NODE_FB_SIZE];

    display_begin(fb);
    expect(display_dirty(), "bilden ritas vid start");
    display_clear_dirty();
    display_set_c10(fb, 600);
    expect(display_dirty(), "siffrorna ritas första gången");
    memcpy(before, fb, sizeof fb);
    display_clear_dirty();
    display_set_c10(fb, 600);
    expect(!display_dirty(), "samma tal ritas inte om");
    expect(memcmp(before, fb, sizeof fb) == 0, "bufferten ligger still");
    display_set_c10(fb, NODE_TEMP_FAULT);
    expect(display_dirty(), "fel ritas om");
    expect(memcmp(fb, before, 16) == 0, "namnet överst ligger kvar");
}

int main(void)
{
    test_pins();
    test_scale();
    test_silent_and_modbus();
    test_display();
    if (g_fails) {
        fprintf(stderr, "%d fel\n", g_fails);
        return 1;
    }
    printf("node-test ok\n");
    return 0;
}
