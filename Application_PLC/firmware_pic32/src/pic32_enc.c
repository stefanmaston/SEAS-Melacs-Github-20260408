#include "pic32_board.h"
#include "pin_map.h"

#define OP_RCRU 0x20u
#define OP_WCRU 0x22u
#define OP_BFSU 0x24u
#define OP_BFCU 0x26u
#define OP_RRXDATA 0x2Cu
#define OP_WGPDATA 0x2Au
#define OP_WGPRDPT 0x60u
#define OP_WRXRDPT 0x64u
#define OP_WGPWRPT 0x6Cu
#define OP_SETETHRST 0xCAu
#define OP_SETPKTDEC 0xCCu
#define OP_SETTXRTS 0xD4u
#define OP_ENABLERX 0xE8u

#define REG_ETXST 0x00u
#define REG_ETXLEN 0x02u
#define REG_ERXST 0x04u
#define REG_ERXTAIL 0x06u
#define REG_EUDAST 0x16u
#define REG_EUDAND 0x18u
#define REG_ESTAT 0x1Au
#define REG_ECON1 0x1Eu
#define REG_ERXFCON 0x34u
#define REG_MACON1 0x40u
#define REG_MACON2 0x42u
#define REG_MABBIPG 0x44u
#define REG_MAMXFL 0x4Au
#define REG_MAADR3 0x60u
#define REG_MAADR2 0x62u
#define REG_MAADR1 0x64u
#define REG_ECON2 0x6Eu

#define RX_START 0x2000u
#define RX_END 0x5FFEu
#define SRAM_SIZE 0x6000u
/* Återställningsvärde 0x40B2: DEFER, PADCFG=101, CRC på, reserverad bit 1 satt. */
#define MACON2_BASE 0x40B2u
#define MACON2_FULDPX 0x0001u
/* Samma normalfilter som Linux-drivrutinen för ENCX24J600: unicast till oss, broadcast, giltig CRC. Ingen mönstermatchning. */
#define ERXFCON_ACCEPT 0x0049u
/* MACON1: reserverade bitar som ska vara 1, RXPAUS av så en pausram inte stoppar sändning. */
#define MACON1_INIT 0x0009u
#define ECON2_RUN 0xC000u
#define ECON2_TXRST 0x0040u

static int g_enc_ok;
static int g_duplex = -1;
static int g_got_rx;
static int g_tx_fail;
static uint16_t g_next = RX_START;

static void cs(int on)
{
    PIN_CS_ETH_LAT = on ? 0 : 1;
}

static void enc_cmd(uint8_t op)
{
    cs(1);
    delay_us(1);
    spi_xfer(op);
    cs(0);
}

static void enc_bfs(uint8_t addr, uint16_t mask)
{
    cs(1);
    delay_us(1);
    spi_xfer(OP_BFSU);
    spi_xfer(addr);
    spi_xfer((uint8_t)mask);
    spi_xfer((uint8_t)(mask >> 8));
    cs(0);
}

static void enc_bfc(uint8_t addr, uint16_t mask)
{
    cs(1);
    delay_us(1);
    spi_xfer(OP_BFCU);
    spi_xfer(addr);
    spi_xfer((uint8_t)mask);
    spi_xfer((uint8_t)(mask >> 8));
    cs(0);
}

/* TXRST håller sändaren i reset tills biten nollställs. */
static void enc_tx_abort(void)
{
    enc_bfs(REG_ECON2, ECON2_TXRST);
    delay_us(100);
    enc_bfc(REG_ECON2, ECON2_TXRST);
    enc_cmd(OP_ENABLERX);
}

static void enc_w16(uint8_t addr, uint16_t value)
{
    cs(1);
    delay_us(1);
    spi_xfer(OP_WCRU);
    spi_xfer(addr);
    spi_xfer((uint8_t)value);
    spi_xfer((uint8_t)(value >> 8));
    cs(0);
}

static uint16_t enc_r16(uint8_t addr)
{
    uint16_t value;

    cs(1);
    delay_us(1);
    spi_xfer(OP_RCRU);
    spi_xfer(addr);
    value = spi_xfer(0);
    value |= (uint16_t)spi_xfer(0) << 8;
    cs(0);
    return value;
}

static void enc_ptr(uint8_t op, uint16_t addr)
{
    cs(1);
    delay_us(1);
    spi_xfer(op);
    spi_xfer((uint8_t)addr);
    spi_xfer((uint8_t)(addr >> 8));
    cs(0);
}

static void read_mac(uint8_t mac[6])
{
    uint16_t a = enc_r16(REG_MAADR1);
    uint16_t b = enc_r16(REG_MAADR2);
    uint16_t c = enc_r16(REG_MAADR3);

    mac[0] = (uint8_t)a;
    mac[1] = (uint8_t)(a >> 8);
    mac[2] = (uint8_t)b;
    mac[3] = (uint8_t)(b >> 8);
    mac[4] = (uint8_t)c;
    mac[5] = (uint8_t)(c >> 8);
    if (mac[0] != 0x00 && mac[5] == 0x00 && mac[4] == 0x04) {
        int i;
        for (i = 0; i < 3; i++) {
            uint8_t swap = mac[i];
            mac[i] = mac[5 - i];
            mac[5 - i] = swap;
        }
    }
}

bool enc_ok(void)
{
    return g_enc_ok ? true : false;
}

bool enc_start(uint8_t mac[6])
{
    uint32_t start;
    int i;

    g_enc_ok = 0;
    g_duplex = -1;
    g_tx_fail = 0;
    g_next = RX_START;
    spi_hw_on(0);
    PIN_CS_ETH_LAT = 1;
    for (i = 0; i < 8; i++) {
        enc_w16(REG_EUDAST, 0x1234);
        if (enc_r16(REG_EUDAST) == 0x1234) {
            break;
        }
        delay_ms(2);
    }
    if (enc_r16(REG_EUDAST) != 0x1234) {
        return false;
    }
    start = board_millis();
    while ((enc_r16(REG_ESTAT) & 0x1000u) == 0) {
        if (board_millis() - start > 50u) {
            return false;
        }
    }
    enc_cmd(OP_SETETHRST);
    delay_ms(1);
    start = board_millis();
    while (enc_r16(REG_EUDAST) != 0) {
        if (board_millis() - start > 20u) {
            return false;
        }
    }
    delay_ms(1);
    enc_w16(REG_ECON2, ECON2_RUN);
    read_mac(mac);
    enc_w16(REG_ERXST, RX_START);
    enc_w16(REG_ERXTAIL, RX_END);
    enc_ptr(OP_WRXRDPT, RX_START);
    /* Parkera användarfönstret utanför SRAM så det inte ligger över mottagningsbufferten. */
    enc_w16(REG_EUDAST, SRAM_SIZE);
    enc_w16(REG_EUDAND, SRAM_SIZE + 1u);
    enc_w16(REG_ERXFCON, ERXFCON_ACCEPT);
    enc_w16(REG_MACON1, MACON1_INIT);
    enc_w16(REG_MACON2, MACON2_BASE | MACON2_FULDPX);
    enc_w16(REG_MABBIPG, 0x0015);
    enc_w16(REG_MAMXFL, 1518);
    enc_cmd(OP_ENABLERX);
    g_enc_ok = 1;
    return true;
}

bool enc_take_rx(void)
{
    int got = g_got_rx;

    g_got_rx = 0;
    return got ? true : false;
}

bool enc_link(void)
{
    if (!g_enc_ok) {
        return false;
    }
    return (enc_r16(REG_ESTAT) & 0x0100u) != 0;
}

void enc_apply_duplex(void)
{
    int full;

    if (!g_enc_ok || !enc_link()) {
        g_duplex = -1;
        return;
    }
    full = (enc_r16(REG_ESTAT) & 0x0400u) != 0;
    if (g_duplex == full) {
        return;
    }
    if (full) {
        enc_w16(REG_MACON2, MACON2_BASE | MACON2_FULDPX);
        enc_w16(REG_MABBIPG, 0x0015);
    } else {
        enc_w16(REG_MACON2, MACON2_BASE);
        enc_w16(REG_MABBIPG, 0x0012);
    }
    enc_cmd(OP_ENABLERX);
    g_duplex = full;
}

bool enc_tx(const uint8_t *frame, int len)
{
    uint32_t start;
    int attempt;
    int i;

    if (!g_enc_ok || len <= 0 || len > 1514 || !enc_link()) {
        return false;
    }
    for (attempt = 0; attempt < 2; attempt++) {
        if (enc_r16(REG_ECON1) & 0x0002u) {
            enc_tx_abort();
        }
        if (enc_r16(REG_ECON1) & 0x0002u) {
            continue;
        }
        enc_ptr(OP_WGPWRPT, 0);
        cs(1);
        delay_us(1);
        spi_xfer(OP_WGPDATA);
        for (i = 0; i < len; i++) {
            spi_xfer(frame[i]);
        }
        cs(0);
        enc_w16(REG_ETXST, 0);
        enc_w16(REG_ETXLEN, (uint16_t)len);
        enc_cmd(OP_SETTXRTS);
        start = board_millis();
        while (enc_r16(REG_ECON1) & 0x0002u) {
            if (board_millis() - start > 30u) {
                enc_tx_abort();
                break;
            }
        }
        if ((enc_r16(REG_ECON1) & 0x0002u) == 0) {
            g_tx_fail = 0;
            return true;
        }
    }
    if (g_tx_fail < 3) {
        g_tx_fail++;
    }
    if (g_tx_fail >= 3) {
        g_enc_ok = 0;
    }
    return false;
}

bool enc_rx(uint8_t *frame, int *len, int max_len)
{
    uint8_t hdr[8];
    int frame_len;
    int copy;
    int extra;
    int i;
    uint16_t next;
    uint16_t tail;

    *len = 0;
    if (!g_enc_ok || (enc_r16(REG_ESTAT) & 0x00FFu) == 0) {
        return false;
    }
    g_got_rx = 1;
    enc_ptr(OP_WRXRDPT, g_next);
    cs(1);
    delay_us(1);
    spi_xfer(OP_RRXDATA);
    for (i = 0; i < 8; i++) {
        hdr[i] = spi_xfer(0xFF);
    }
    next = (uint16_t)(hdr[0] | (hdr[1] << 8));
    frame_len = hdr[2] | (hdr[3] << 8);
    if (frame_len < 14 || frame_len > 1518) {
        cs(0);
        g_next = next;
        tail = (next == RX_START) ? RX_END : (uint16_t)(next - 2u);
        enc_w16(REG_ERXTAIL, tail);
        enc_cmd(OP_SETPKTDEC);
        return false;
    }
    copy = frame_len > 4 ? frame_len - 4 : frame_len;
    extra = 0;
    if (copy > max_len) {
        extra = copy - max_len;
        copy = max_len;
    }
    for (i = 0; i < copy; i++) {
        frame[i] = spi_xfer(0xFF);
    }
    for (i = 0; i < extra; i++) {
        spi_xfer(0xFF);
    }
    cs(0);
    g_next = next;
    tail = (next == RX_START) ? RX_END : (uint16_t)(next - 2u);
    enc_w16(REG_ERXTAIL, tail);
    enc_cmd(OP_SETPKTDEC);
    *len = copy;
    return copy >= 14;
}
