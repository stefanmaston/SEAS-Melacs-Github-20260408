#include "modbus_slave.h"

static uint16_t rd16(const uint8_t *p) {
    return (uint16_t)((p[0] << 8) | p[1]);
}

static void wr16(uint8_t *p, uint16_t v) {
    p[0] = (uint8_t)(v >> 8);
    p[1] = (uint8_t)v;
}

static size_t exception(const uint8_t *req, uint8_t code, uint8_t *rsp, size_t rsp_max) {
    if (rsp_max < 9) {
        return 0;
    }
    rsp[0] = req[0];
    rsp[1] = req[1];
    rsp[2] = 0;
    rsp[3] = 0;
    wr16(rsp + 4, 3);
    rsp[6] = req[6];
    rsp[7] = (uint8_t)(req[7] | 0x80);
    rsp[8] = code;
    return 9;
}

static size_t echo_head(const uint8_t *req, uint8_t *rsp, size_t rsp_max) {
    if (rsp_max < 12) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        rsp[i] = req[i];
    }
    wr16(rsp + 4, 6);
    rsp[6] = req[6];
    rsp[7] = req[7];
    wr16(rsp + 8, rd16(req + 8));
    wr16(rsp + 10, rd16(req + 10));
    return 12;
}

size_t melacs_modbus_tcp(MelacsImage *img, const uint8_t *req, size_t req_len,
                         uint8_t *rsp, size_t rsp_max) {
    if (req_len < 8) {
        return 0;
    }
    if (rd16(req + 2) != 0) {
        return 0;
    }
    uint16_t mbap_len = rd16(req + 4);
    if (mbap_len < 2 || (size_t)(6 + mbap_len) > req_len) {
        return 0;
    }
    uint8_t fc = req[7];
    const uint8_t *pdu = req + 7;
    size_t pdu_len = (size_t)mbap_len - 1;

    if (fc == 1 || fc == 2 || fc == 3 || fc == 4) {
        if (pdu_len < 5) {
            return exception(req, 3, rsp, rsp_max);
        }
        uint16_t addr = rd16(pdu + 1);
        uint16_t qty = rd16(pdu + 3);
        if (qty == 0) {
            return exception(req, 3, rsp, rsp_max);
        }
        if (fc == 1 || fc == 2) {
            uint16_t space = (fc == 1) ? MELACS_COIL_COUNT : MELACS_DISCRETE_COUNT;
            if (qty > 64 || addr >= space || qty > space - addr) {
                return exception(req, addr >= space || qty > space - addr ? 2 : 3, rsp, rsp_max);
            }
            uint8_t nbytes = (uint8_t)((qty + 7) / 8);
            if (rsp_max < (size_t)(9 + nbytes)) {
                return 0;
            }
            rsp[0] = req[0];
            rsp[1] = req[1];
            rsp[2] = 0;
            rsp[3] = 0;
            wr16(rsp + 4, (uint16_t)(3 + nbytes));
            rsp[6] = req[6];
            rsp[7] = fc;
            rsp[8] = nbytes;
            for (uint8_t i = 0; i < nbytes; i++) {
                rsp[9 + i] = 0;
            }
            for (uint16_t i = 0; i < qty; i++) {
                uint8_t bit = (fc == 1) ? img->coils[addr + i] : img->discrete[addr + i];
                if (bit) {
                    rsp[9 + (i / 8)] |= (uint8_t)(1u << (i % 8));
                }
            }
            return (size_t)(9 + nbytes);
        }
        uint16_t space = (fc == 3) ? MELACS_HOLDING_COUNT : MELACS_INPUT_REG_COUNT;
        if (qty > 60 || addr >= space || qty > space - addr) {
            return exception(req, addr >= space || qty > space - addr ? 2 : 3, rsp, rsp_max);
        }
        if (rsp_max < (size_t)(9 + qty * 2)) {
            return 0;
        }
        rsp[0] = req[0];
        rsp[1] = req[1];
        rsp[2] = 0;
        rsp[3] = 0;
        wr16(rsp + 4, (uint16_t)(3 + qty * 2));
        rsp[6] = req[6];
        rsp[7] = fc;
        rsp[8] = (uint8_t)(qty * 2);
        for (uint16_t i = 0; i < qty; i++) {
            uint16_t value = (fc == 3) ? img->holding[addr + i] : img->input_reg[addr + i];
            if (fc == 3 && (uint16_t)(addr + i) == 209) {
                value = 0;
            }
            wr16(rsp + 9 + i * 2, value);
        }
        return (size_t)(9 + qty * 2);
    }

    if (fc == 5 || fc == 6) {
        if (pdu_len < 5) {
            return exception(req, 3, rsp, rsp_max);
        }
        uint16_t addr = rd16(pdu + 1);
        uint16_t value = rd16(pdu + 3);
        if (fc == 5) {
            if (addr >= MELACS_COIL_COUNT) {
                return exception(req, 2, rsp, rsp_max);
            }
            if (value == 0xFF00) {
                img->coils[addr] = 1;
            } else if (value == 0) {
                img->coils[addr] = 0;
            } else {
                return exception(req, 3, rsp, rsp_max);
            }
        } else {
            if (addr >= MELACS_HOLDING_COUNT) {
                return exception(req, 2, rsp, rsp_max);
            }
            img->holding[addr] = value;
        }
        return echo_head(req, rsp, rsp_max);
    }

    if (fc == 15) {
        if (pdu_len < 6) {
            return exception(req, 3, rsp, rsp_max);
        }
        uint16_t addr = rd16(pdu + 1);
        uint16_t qty = rd16(pdu + 3);
        uint8_t nbytes = pdu[5];
        if (qty == 0 || qty > 64 || nbytes != (qty + 7) / 8 || pdu_len < (size_t)(6 + nbytes)) {
            return exception(req, 3, rsp, rsp_max);
        }
        if (addr >= MELACS_COIL_COUNT || qty > MELACS_COIL_COUNT - addr) {
            return exception(req, 2, rsp, rsp_max);
        }
        for (uint16_t i = 0; i < qty; i++) {
            img->coils[addr + i] = (pdu[6 + (i / 8)] >> (i % 8)) & 1;
        }
        return echo_head(req, rsp, rsp_max);
    }

    if (fc == 16) {
        if (pdu_len < 6) {
            return exception(req, 3, rsp, rsp_max);
        }
        uint16_t addr = rd16(pdu + 1);
        uint16_t qty = rd16(pdu + 3);
        uint8_t nbytes = pdu[5];
        if (qty == 0 || qty > 60 || nbytes != qty * 2 || pdu_len < (size_t)(6 + nbytes)) {
            return exception(req, 3, rsp, rsp_max);
        }
        if (addr >= MELACS_HOLDING_COUNT || qty > MELACS_HOLDING_COUNT - addr) {
            return exception(req, 2, rsp, rsp_max);
        }
        for (uint16_t i = 0; i < qty; i++) {
            img->holding[addr + i] = rd16(pdu + 6 + i * 2);
        }
        return echo_head(req, rsp, rsp_max);
    }

    return exception(req, 1, rsp, rsp_max);
}
