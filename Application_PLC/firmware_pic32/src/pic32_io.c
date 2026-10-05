#include "pic32_board.h"
#include "pin_map.h"

#include <xc.h>

static int g_rtc_ok;
static int g_led_hold;
static int g_led_pulse;
static uint32_t g_led_until;
static int g_beep_on;
static uint32_t g_beep_until;

static void memled_apply(void)
{
    PIN_LED7_LAT = (g_led_hold > 0 || g_led_pulse) ? 0 : 1;
}

void memled_init(void)
{
    g_led_hold = 0;
    g_led_pulse = 0;
    PIN_LED7_LAT = 1;
    PIN_LED7_TRIS = 0;
}

void memled_pulse(void)
{
    g_led_pulse = 1;
    g_led_until = board_millis() + 80u;
    memled_apply();
}

void memled_sd(int on)
{
    if (on) {
        g_led_hold++;
    } else if (g_led_hold > 0) {
        g_led_hold--;
    }
    memled_apply();
}

void memled_poll(void)
{
    if (g_led_pulse && (int32_t)(board_millis() - g_led_until) >= 0) {
        g_led_pulse = 0;
    }
    memled_apply();
}

void buzzer_pulse(void)
{
    g_beep_on = 1;
    g_beep_until = board_millis() + 30u;
    PIN_BUZZER_LAT = 1;
}

void buzzer_poll(void)
{
    if (g_beep_on && (int32_t)(board_millis() - g_beep_until) >= 0) {
        g_beep_on = 0;
        PIN_BUZZER_LAT = 0;
    }
}

static void pwm_init(void)
{
    T2CON = 0;
    TMR2 = 0;
    PR2 = 0x2FFF;
    T2CONbits.TCKPS = 0;
    T2CONbits.ON = 1;

    OC1CON = 0;
    OC1R = 0;
    OC1RS = 0;
    OC1CONbits.OCM = 6;
    OC1CONbits.ON = 1;

    OC2CON = 0;
    OC2R = 0;
    OC2RS = 0;
    OC2CONbits.OCM = 6;
    OC2CONbits.ON = 1;

    OC3CON = 0;
    OC3R = 0;
    OC3RS = 0;
    OC3CONbits.OCM = 6;
    OC3CONbits.ON = 1;

    OC4CON = 0;
    OC4R = 0;
    OC4RS = 0;
    OC4CONbits.OCM = 6;
    OC4CONbits.ON = 1;
}

static void adc_init(void)
{
    const uint32_t mask =
        (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) |
        (1u << 10) | (1u << 13) | (1u << 14) | (1u << 15);

    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1PCFG = 0xFFFFu;
    AD1PCFGCLR = mask;
    AD1CSSL = (uint16_t)mask;
    AD1CHS = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.ASAM = 1;
    AD1CON2bits.CSCNA = 1;
    AD1CON2bits.SMPI = 9;
    AD1CON3bits.ADRC = 1;
    AD1CON3bits.SAMC = 15;
    AD1CON1bits.ON = 1;
}

static uint16_t adc_sample(int index)
{
    volatile uint32_t *base = (volatile uint32_t *)&ADC1BUF0;

    return (uint16_t)base[(unsigned)index * 4u];
}

static uint16_t mcp3208(uint8_t channel)
{
    uint8_t hi;
    uint8_t lo;

    spi_hw_off();
    PIN_SPI_SCK_LAT = 0;
    PIN_CS_AD_LAT = 0;
    delay_us(2);
    (void)bb_xfer((uint8_t)(0x06u | (channel >> 2)));
    hi = bb_xfer((uint8_t)((channel & 3u) << 6));
    lo = bb_xfer(0);
    PIN_CS_AD_LAT = 1;
    spi_hw_on(0);
    return (uint16_t)(((hi & 0x0Fu) << 8) | lo);
}

static int board_celsius(uint16_t counts)
{
    int mv = (int)counts * 3300 / 1024;
    int c = (mv - 500) / 10;

    if (c < 0) {
        return 0;
    }
    if (c > 200) {
        return 200;
    }
    return c;
}

void io_init(void)
{
    PIN_DIO0_TRIS = 1;
    PIN_DIO1_TRIS = 1;
    PIN_DIO2_TRIS = 1;
    PIN_DIO3_TRIS = 1;

    PIN_DIO4_LAT = 0;
    PIN_DIO5_LAT = 0;
    PIN_DIO6_LAT = 0;
    PIN_DIO7_LAT = 0;
    PIN_DIO4_TRIS = 0;
    PIN_DIO5_TRIS = 0;
    PIN_DIO6_TRIS = 0;
    PIN_DIO7_TRIS = 0;

    PIN_SIP1_LAT = 0;
    PIN_SIP2_LAT = 0;
    PIN_SIP4_LAT = 0;
    PIN_SIP5_LAT = 0;
    PIN_SIP6_LAT = 0;
    PIN_SIP7_LAT = 0;
    PIN_SIP1_TRIS = 0;
    PIN_SIP2_TRIS = 0;
    PIN_SIP4_TRIS = 0;
    PIN_SIP5_TRIS = 0;
    PIN_SIP6_TRIS = 0;
    PIN_SIP7_TRIS = 0;

    PIN_H1_DIS_LAT = 1;
    PIN_H1_ALI_LAT = 0;
    PIN_H1_BLI_LAT = 0;
    PIN_H1_AHI_LAT = 0;
    PIN_H1_BHI_LAT = 0;
    PIN_H2_DIS_LAT = 1;
    PIN_H2_ALI_LAT = 0;
    PIN_H2_BLI_LAT = 0;
    PIN_H2_AHI_LAT = 0;
    PIN_H2_BHI_LAT = 0;
    PIN_H1_DIS_TRIS = 0;
    PIN_H1_ALI_TRIS = 0;
    PIN_H1_BLI_TRIS = 0;
    PIN_H1_AHI_TRIS = 0;
    PIN_H1_BHI_TRIS = 0;
    PIN_H2_DIS_TRIS = 0;
    PIN_H2_ALI_TRIS = 0;
    PIN_H2_BLI_TRIS = 0;
    PIN_H2_AHI_TRIS = 0;
    PIN_H2_BHI_TRIS = 0;

    g_beep_on = 0;
    PIN_BUZZER_LAT = 0;
    PIN_BUZZER_TRIS = 0;

    pwm_init();
    adc_init();
    memled_init();
}

void io_read(PlcInputs *in)
{
    int i;

    in->dio_in[0] = PIN_DIO0_PORT ? true : false;
    in->dio_in[1] = PIN_DIO1_PORT ? true : false;
    in->dio_in[2] = PIN_DIO2_PORT ? true : false;
    in->dio_in[3] = PIN_DIO3_PORT ? true : false;

    for (i = 0; i < 8; i++) {
        in->ad[i] = mcp3208((uint8_t)i);
    }
    in->p = in->ad[5];
    in->t1 = in->ad[6];
    in->t2 = in->ad[7];
    in->value = 0;
    in->t_board = (uint16_t)board_celsius(adc_sample(3));
    for (i = 0; i < 6; i++) {
        in->ai[i] = adc_sample(4 + i);
    }
}

static uint16_t pwm_duty(uint16_t value)
{
    uint32_t duty = ((uint32_t)value * 0x3000u) >> 16;

    if (duty > 0x2FFFu) {
        duty = 0x2FFFu;
    }
    return (uint16_t)duty;
}

void io_write(const PlcOutputs *out)
{
    int h1_on = out->h1_dis ? 0 : 1;
    int h2_on = out->h2_dis ? 0 : 1;

    PIN_DIO4_LAT = out->dio_out[0] ? 1 : 0;
    PIN_DIO5_LAT = out->dio_out[1] ? 1 : 0;
    PIN_DIO6_LAT = out->dio_out[2] ? 1 : 0;
    PIN_DIO7_LAT = out->dio_out[3] ? 1 : 0;

    PIN_SIP1_LAT = out->sip[1] ? 1 : 0;
    PIN_SIP2_LAT = out->sip[2] ? 1 : 0;
    PIN_SIP4_LAT = out->sip[4] ? 1 : 0;
    PIN_SIP5_LAT = out->sip[5] ? 1 : 0;
    PIN_SIP6_LAT = out->sip[6] ? 1 : 0;
    PIN_SIP7_LAT = out->sip[7] ? 1 : 0;

    PIN_H1_DIS_LAT = h1_on ? 0 : 1;
    PIN_H1_ALI_LAT = (h1_on && out->h1_ali) ? 1 : 0;
    PIN_H1_BLI_LAT = (h1_on && out->h1_bli) ? 1 : 0;
    PIN_H2_DIS_LAT = h2_on ? 0 : 1;
    PIN_H2_ALI_LAT = (h2_on && out->h2_ali) ? 1 : 0;
    PIN_H2_BLI_LAT = (h2_on && out->h2_bli) ? 1 : 0;

    OC1RS = h1_on ? pwm_duty(out->h1_ahi) : 0;
    OC2RS = h1_on ? pwm_duty(out->h1_bhi) : 0;
    OC3RS = h2_on ? pwm_duty(out->h2_ahi) : 0;
    OC4RS = h2_on ? pwm_duty(out->h2_bhi) : 0;
}

static void rtc_out_bit(int bit)
{
    PIN_SPI_SCK_LAT = 1;
    delay_us(2);
    PIN_SPI_MOSI_LAT = bit ? 1 : 0;
    delay_us(2);
    PIN_SPI_SCK_LAT = 0;
    delay_us(2);
}

static int rtc_in_bit(void)
{
    PIN_SPI_SCK_LAT = 1;
    delay_us(2);
    PIN_SPI_SCK_LAT = 0;
    delay_us(2);
    return PIN_SPI_MISO_PORT ? 1 : 0;
}

static void rtc_out_byte(uint8_t value)
{
    int i;

    for (i = 0; i < 8; i++) {
        rtc_out_bit(value & 0x80u);
        value <<= 1;
    }
}

static uint8_t rtc_in_byte(void)
{
    uint8_t value = 0;
    int i;

    for (i = 0; i < 8; i++) {
        value <<= 1;
        if (rtc_in_bit()) {
            value |= 1u;
        }
    }
    return value;
}

static void rtc_begin(uint8_t cmd)
{
    spi_hw_off();
    PIN_SPI_SCK_LAT = 1;
    PIN_CS_RTC_LAT = 1;
    delay_us(2);
    PIN_CS_RTC_LAT = 0;
    delay_us(2);
    rtc_out_byte(cmd);
}

static void rtc_end(void)
{
    PIN_CS_RTC_LAT = 1;
    PIN_SPI_SCK_LAT = 0;
    spi_hw_on(0);
}

static uint8_t from_bcd(uint8_t value)
{
    return (uint8_t)(((value >> 4) & 0x0Fu) * 10u + (value & 0x0Fu));
}

static uint8_t to_bcd(uint8_t value)
{
    return (uint8_t)(((value / 10u) << 4) | (value % 10u));
}

bool rtc_chip_ok(void)
{
    return g_rtc_ok ? true : false;
}

static void rtc_write_reg(uint8_t addr, uint8_t value)
{
    rtc_begin(addr);
    rtc_out_byte(value);
    rtc_end();
}

bool rtc_chip_read(RtcClock *clk)
{
    uint8_t raw[8];
    uint8_t century;
    unsigned dow;
    RtcClock next;
    int i;

    rtc_begin(0xBF);
    for (i = 0; i < 8; i++) {
        raw[i] = rtc_in_byte();
    }
    rtc_end();
    rtc_begin(0x93);
    century = rtc_in_byte();
    rtc_end();

    raw[0] &= 0x7Fu;
    raw[2] &= 0x3Fu;
    dow = from_bcd(raw[5] & 0x07u);
    next.second = from_bcd(raw[0]);
    next.minute = from_bcd(raw[1]);
    next.hour = from_bcd(raw[2]);
    next.day = from_bcd(raw[3]);
    next.month = from_bcd(raw[4] & 0x1Fu);
    next.weekday = (uint8_t)(dow - 1u);
    next.year = (uint16_t)(from_bcd(century) * 100u + from_bcd(raw[6]));
    if (dow < 1u || dow > 7u || !rtc_valid(&next)) {
        g_rtc_ok = 0;
        return false;
    }
    *clk = next;
    g_rtc_ok = 1;
    return true;
}

bool rtc_chip_write(const RtcClock *clk)
{
    uint8_t raw[8];
    int i;

    if (!rtc_valid(clk)) {
        return false;
    }
    raw[0] = to_bcd(clk->second);
    raw[1] = to_bcd(clk->minute);
    raw[2] = to_bcd(clk->hour);
    raw[3] = to_bcd(clk->day);
    raw[4] = to_bcd(clk->month);
    /* Kretsen räknar veckodag 1–7, söndag är 1. */
    raw[5] = to_bcd((uint8_t)(clk->weekday + 1u));
    raw[6] = to_bcd((uint8_t)(clk->year % 100u));
    raw[7] = 0;

    /* WP måste vara 0, annars kastas hela burst-skrivningen. Exakt åtta byte. */
    rtc_write_reg(0x0F, 0x00);
    rtc_begin(0x3F);
    for (i = 0; i < 8; i++) {
        rtc_out_byte(raw[i]);
    }
    rtc_end();
    rtc_write_reg(0x13, 0x20);
    rtc_write_reg(0x0F, 0x80);
    return true;
}
