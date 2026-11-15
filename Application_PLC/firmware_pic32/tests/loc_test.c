#include "loc_runtime.h"
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

static uint16_t wrap_loc(uint8_t *dst, uint32_t mask, const uint8_t *code, uint16_t code_len)
{
    uint8_t body[LOC_MAX_IMAGE];
    uint16_t body_len;
    uint32_t crc;

    body[0] = (uint8_t)mask;
    body[1] = (uint8_t)(mask >> 8);
    body[2] = (uint8_t)(mask >> 16);
    body[3] = (uint8_t)(mask >> 24);
    memcpy(body + 4, code, code_len);
    body_len = (uint16_t)(4u + code_len);
    dst[0] = 'M';
    dst[1] = 'P';
    dst[2] = 'L';
    dst[3] = '1';
    dst[4] = 1;
    dst[5] = 0;
    dst[6] = (uint8_t)body_len;
    dst[7] = (uint8_t)(body_len >> 8);
    crc = protect_crc32(body, body_len);
    dst[8] = (uint8_t)crc;
    dst[9] = (uint8_t)(crc >> 8);
    dst[10] = (uint8_t)(crc >> 16);
    dst[11] = (uint8_t)(crc >> 24);
    memcpy(dst + 12, body, body_len);
    return (uint16_t)(12u + body_len);
}

static int load_loc(const uint8_t *img, uint16_t len)
{
    uint16_t off;
    uint16_t begin = 1;
    uint16_t commit = 2;

    if (register_image_write_regs(LOC_REG_CTRL, 1, &begin) != 0) {
        return -1;
    }
    if (register_image_write_regs(LOC_REG_LEN, 1, &len) != 0) {
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
        if (register_image_write_regs(LOC_REG_OFF, (uint16_t)(1u + words), regs) != 0) {
            return -1;
        }
        off = (uint16_t)(off + chunk);
    }
    if (register_image_write_regs(LOC_REG_CTRL, 1, &commit) != 0) {
        return -1;
    }
    return 0;
}

int test_loc(void)
{
    uint8_t image[LOC_MAX_IMAGE];
    uint8_t code[32];
    uint16_t n;
    uint16_t len;
    uint16_t status;
    uint16_t own_lo;
    PlcInputs in;
    PlcOutputs local;
    PlcOutputs out;
    uint16_t master_before;
    uint16_t master_after;

    register_image_init();
    memset(&in, 0, sizeof(in));
    expect(!loc_ok(), "saknad lokal bild är inte giltig");

    n = 0;
    code[n++] = LOC_OP_LDC;
    code[n++] = 1;
    code[n++] = 0;
    code[n++] = LOC_OP_ST_Q_BOOL;
    code[n++] = 0;
    code[n++] = LOC_OP_END;
    len = wrap_loc(image, LOC_OWN_DIO4, code, n);
    expect(load_loc(image, len) == 0, "lokal bild laddas");
    expect(loc_ok(), "lokal bild är giltig");
    expect(register_image_read_regs(true, LOC_REG_OWN_LO, 1, &own_lo) == 0
           && own_lo == (uint16_t)LOC_OWN_DIO4, "ägarmask DIO4");
    loc_step(&in, &local);
    expect(local.dio_out[0], "konstant sann sätter DIO4");
    safe_outputs(&out);
    loc_apply(loc_own_mask(), &local, &out);
    expect(out.dio_out[0] && out.h1_dis && out.h2_dis, "bara ägd DIO4 slås på");

    n = 0;
    code[n++] = LOC_OP_LD_BOOL;
    code[n++] = 0;
    code[n++] = LOC_OP_ST_Q_BOOL;
    code[n++] = 0;
    code[n++] = LOC_OP_END;
    len = wrap_loc(image, LOC_OWN_DIO4, code, n);
    expect(load_loc(image, len) == 0, "spegelbild laddas");
    in.dio_in[0] = true;
    loc_step(&in, &local);
    expect(local.dio_out[0], "DIO4 följer DIO0 hög");
    in.dio_in[0] = false;
    loc_step(&in, &local);
    expect(!local.dio_out[0], "DIO4 följer DIO0 låg");

    {
        uint16_t coil_on = 1;
        PlcOutputs cmd;
        uint16_t safe_mode;
        uint16_t period;
        bool master;

        register_image_commands(&cmd, &safe_mode, &period, &master);
        master_before = master ? 1 : 0;
        expect(register_image_write_regs(LOC_REG_CTRL, 1, &coil_on) == 0,
               "ctrl-skrivning tas emot");
        register_image_commands(&cmd, &safe_mode, &period, &master);
        master_after = master ? 1 : 0;
        expect(master_before == master_after, "lokal holding sätter inte mastern");
    }

    image[16] ^= 0xFFu;
    expect(load_loc(image, len) == 0, "ogiltig lokal bild tas emot");
    expect(!loc_ok(), "fel kontrollsumma fäller lokal bild");
    expect(register_image_read_regs(false, LOC_IN_STATUS, 1, &status) == 0
           && (status & 2u) != 0, "status bit1 fel");
    expect(loc_own_mask() == 0, "fält bild äger inget");

    return g_fails;
}
