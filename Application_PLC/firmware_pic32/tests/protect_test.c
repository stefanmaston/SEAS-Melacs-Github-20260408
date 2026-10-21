#include "fast_ctrl.h"
#include "protect.h"
#include "register_image.h"

#include <stdio.h>
#include <string.h>

static int g_fails;

static void expect(int cond, const char *what)
{
    if (!cond) {
        fprintf(stderr, "FAIL: %s\n", what);
        g_fails++;
    }
}

static uint16_t wrap_image(uint8_t *dst, const uint8_t *body, uint16_t body_len)
{
    uint32_t crc = protect_crc32(body, body_len);

    dst[0] = 'M';
    dst[1] = 'P';
    dst[2] = 'I';
    dst[3] = '1';
    dst[4] = 1;
    dst[5] = 0;
    dst[6] = (uint8_t)body_len;
    dst[7] = (uint8_t)(body_len >> 8);
    dst[8] = (uint8_t)crc;
    dst[9] = (uint8_t)(crc >> 8);
    dst[10] = (uint8_t)(crc >> 16);
    dst[11] = (uint8_t)(crc >> 24);
    memcpy(dst + 12, body, body_len);
    return (uint16_t)(12u + body_len);
}

static int load_image(const uint8_t *img, uint16_t len)
{
    uint16_t off;
    uint16_t begin = 1;
    uint16_t commit = 2;

    if (register_image_write_regs(PROT_REG_CTRL, 1, &begin) != 0) {
        return -1;
    }
    if (register_image_write_regs(PROT_REG_LEN, 1, &len) != 0) {
        return -1;
    }
    for (off = 0; off < len;) {
        uint16_t chunk = (uint16_t)(len - off);
        uint16_t words;
        uint16_t w;
        uint16_t regs[17];

        if (chunk > 32u) {
            chunk = 32u;
        }
        words = (uint16_t)((chunk + 1u) / 2u);
        regs[0] = off;
        for (w = 0; w < words; w++) {
            uint16_t pos = (uint16_t)(off + w * 2u);
            uint8_t hi = img[pos];
            uint8_t lo = (uint16_t)(pos + 1u) < len ? img[pos + 1u] : 0;
            regs[1u + w] = (uint16_t)(((uint16_t)hi << 8) | lo);
        }
        if (register_image_write_regs(PROT_REG_OFF, (uint16_t)(1u + words), regs) != 0) {
            return -1;
        }
        off = (uint16_t)(off + chunk);
    }
    if (register_image_write_regs(PROT_REG_CTRL, 1, &commit) != 0) {
        return -1;
    }
    return 0;
}

static void step_mask(const ProtectIn *in, uint16_t *mask)
{
    ProtectOut out;

    protect_step(in, &out);
    *mask = out.mask;
}

int test_protect(void)
{
    uint8_t image[PROT_MAX_IMAGE];
    uint8_t body[PROT_MAX_IMAGE];
    uint16_t n;
    uint16_t len;
    uint16_t mask;
    uint16_t status;
    ProtectIn in;
    int i;

    register_image_init();
    memset(&in, 0, sizeof(in));
    expect(!protect_ok(), "saknad bild är inte giltig");

    body[0] = PROT_OP_END;
    len = wrap_image(image, body, 1);
    expect(load_image(image, len) == 0, "tom bild laddas");
    expect(protect_ok(), "tom bild är giltig");
    step_mask(&in, &mask);
    expect(mask == 0, "tom bild spärrar inget");
    expect(register_image_read_regs(false, PROT_IN_STATUS, 1, &status) == 0
           && (status & 1u) != 0, "status bit0 giltig");

    n = 0;
    body[n++] = PROT_OP_LDC;
    body[n++] = 1;
    body[n++] = 0;
    body[n++] = PROT_OP_INHIBIT;
    body[n++] = (uint8_t)PROT_INH_H1;
    body[n++] = 0;
    body[n++] = PROT_OP_END;
    len = wrap_image(image, body, n);
    expect(load_image(image, len) == 0, "spärrbild laddas");
    step_mask(&in, &mask);
    expect(mask == PROT_INH_H1, "konstant sann spärrar H1");
    {
        uint16_t zero = 0;
        expect(register_image_write_regs(301, 1, &zero) == 0, "driftförregling skrivbar");
    }
    step_mask(&in, &mask);
    expect(mask == PROT_INH_H1, "Modbus kan inte släppa skyddsbilden");

    image[12] ^= 0xFFu;
    expect(load_image(image, len) == 0, "ogiltig bild tas emot som skrivning");
    expect(!protect_ok(), "fel kontrollsumma fäller bilden");
    expect(register_image_read_regs(false, PROT_IN_STATUS, 1, &status) == 0
           && (status & 2u) != 0, "status bit1 fel");

    n = 0;
    for (i = 0; i < (int)PROT_MAX_STEPS / 2; i++) {
        body[n++] = PROT_OP_LDC;
        body[n++] = 1;
        body[n++] = 0;
        body[n++] = PROT_OP_ST_LOCAL;
        body[n++] = 0;
    }
    len = wrap_image(image, body, n);
    expect(load_image(image, len) == 0, "lång bild bekräftas");
    expect(protect_ok(), "lång bild är giltig tills den körs");
    step_mask(&in, &mask);
    expect(!protect_ok() && mask == 0, "för lång körning ger safe");

    n = 0;
    body[n++] = PROT_OP_LDC;
    body[n++] = 1;
    body[n++] = 0;
    body[n++] = PROT_OP_TON;
    body[n++] = 0;
    body[n++] = 3;
    body[n++] = 0;
    body[n++] = PROT_OP_INHIBIT;
    body[n++] = (uint8_t)PROT_INH_H1;
    body[n++] = 0;
    body[n++] = PROT_OP_END;
    len = wrap_image(image, body, n);
    expect(load_image(image, len) == 0, "tidbild laddas");
    step_mask(&in, &mask);
    expect(mask == 0, "TON väntar");
    step_mask(&in, &mask);
    expect(mask == 0, "TON andra svepet");
    step_mask(&in, &mask);
    expect(mask == PROT_INH_H1, "TON löser på tredje svepet");

    n = 0;
    body[n++] = PROT_OP_LDC;
    body[n++] = 1;
    body[n++] = 0;
    body[n++] = PROT_OP_RTRIG;
    body[n++] = 0;
    body[n++] = PROT_OP_INHIBIT;
    body[n++] = (uint8_t)PROT_INH_H2;
    body[n++] = 0;
    body[n++] = PROT_OP_END;
    len = wrap_image(image, body, n);
    expect(load_image(image, len) == 0, "flankbild laddas");
    step_mask(&in, &mask);
    expect(mask == PROT_INH_H2, "stigande flank spärrar H2");
    step_mask(&in, &mask);
    expect(mask == 0, "hållen nivå ger ingen ny flank");

    protect_kick_tick();
    expect(register_image_read_regs(false, PROT_IN_STATUS, 1, &status) == 0
           && (status & 4u) != 0, "puls-fas växlar");
    protect_kick_tick();
    expect(register_image_read_regs(false, PROT_IN_STATUS, 1, &status) == 0
           && (status & 4u) == 0, "puls-fas växlar tillbaka");

    {
        FastIn fin;
        FastOut fout;
        memset(&fin, 0, sizeof(fin));
        fast_ctrl_init();
        fast_ctrl_set_guard(true, false);
        fast_ctrl_step(&fin, &fout);
        expect(fout.block[0] && !fout.block[1], "skyddsspärren ligger i avbrottet");
        fast_ctrl_step(&fin, &fout);
        expect(fout.block[0], "avstängd driftförregling släpper inte skyddsspärren");
        fast_ctrl_note_time(1000);
        fast_ctrl_sweep_kick(1000);
        fast_ctrl_set_guard(false, false);
        fast_ctrl_step(&fin, &fout);
        expect(!fout.block[0] && !fout.block[1], "färskt svep släpper tidsvakten");
        fast_ctrl_note_time(1000 + FAST_SWEEP_LATE_MS + 1u);
        fast_ctrl_step(&fin, &fout);
        expect(fout.block[0] && fout.block[1], "uteblivet svep spärrar båda bryggorna");
    }

    return g_fails;
}
