#include "modbus_pdu.h"

#include "register_image.h"

#include <string.h>

static int exception_pdu(uint8_t *pdu, uint8_t fc, uint8_t code)
{
    pdu[0] = (uint8_t)(fc | 0x80u);
    pdu[1] = code;
    return 2;
}

int modbus_pdu_handle(const uint8_t *pdu, int len, uint8_t *out)
{
    uint8_t fc;
    uint16_t addr;
    uint16_t count;
    int ex;

    if (len < 1) {
        return 0;
    }
    fc = pdu[0];

    if (fc == 1 || fc == 2 || fc == 3 || fc == 4) {
        uint8_t bits[250];
        uint16_t regs[125];
        uint16_t i;

        if (len < 5) {
            return exception_pdu(out, fc, 3);
        }
        addr = (uint16_t)((pdu[1] << 8) | pdu[2]);
        count = (uint16_t)((pdu[3] << 8) | pdu[4]);
        if (fc == 1 || fc == 2) {
            ex = register_image_read_bits(fc == 1, addr, count, bits);
            if (ex != 0) {
                return exception_pdu(out, fc, (uint8_t)ex);
            }
            out[0] = fc;
            out[1] = (uint8_t)((count + 7u) / 8u);
            memcpy(out + 2, bits, out[1]);
            return 2 + out[1];
        }
        ex = register_image_read_regs(fc == 3, addr, count, regs);
        if (ex != 0) {
            return exception_pdu(out, fc, (uint8_t)ex);
        }
        out[0] = fc;
        out[1] = (uint8_t)(count * 2u);
        for (i = 0; i < count; i++) {
            out[2 + i * 2] = (uint8_t)(regs[i] >> 8);
            out[3 + i * 2] = (uint8_t)(regs[i] & 0xffu);
        }
        return 2 + (int)count * 2;
    }

    if (fc == 5) {
        uint8_t coil;
        uint16_t val;

        if (len < 5) {
            return exception_pdu(out, fc, 3);
        }
        addr = (uint16_t)((pdu[1] << 8) | pdu[2]);
        val = (uint16_t)((pdu[3] << 8) | pdu[4]);
        if (val != 0x0000 && val != 0xFF00) {
            return exception_pdu(out, fc, 3);
        }
        coil = (uint8_t)(val == 0xFF00 ? 1 : 0);
        ex = register_image_write_coils(addr, 1, &coil);
        if (ex != 0) {
            return exception_pdu(out, fc, (uint8_t)ex);
        }
        memcpy(out, pdu, 5);
        return 5;
    }

    if (fc == 6) {
        uint16_t val;

        if (len < 5) {
            return exception_pdu(out, fc, 3);
        }
        addr = (uint16_t)((pdu[1] << 8) | pdu[2]);
        val = (uint16_t)((pdu[3] << 8) | pdu[4]);
        ex = register_image_write_regs(addr, 1, &val);
        if (ex != 0) {
            return exception_pdu(out, fc, (uint8_t)ex);
        }
        memcpy(out, pdu, 5);
        return 5;
    }

    if (fc == 15) {
        uint8_t nbytes;

        if (len < 6) {
            return exception_pdu(out, fc, 3);
        }
        addr = (uint16_t)((pdu[1] << 8) | pdu[2]);
        count = (uint16_t)((pdu[3] << 8) | pdu[4]);
        nbytes = pdu[5];
        if (count == 0 || nbytes != (uint8_t)((count + 7u) / 8u) || len < 6 + nbytes) {
            return exception_pdu(out, fc, 3);
        }
        ex = register_image_write_coils(addr, count, pdu + 6);
        if (ex != 0) {
            return exception_pdu(out, fc, (uint8_t)ex);
        }
        memcpy(out, pdu, 5);
        return 5;
    }

    if (fc == 16) {
        uint8_t nbytes;
        uint16_t regs[123];
        uint16_t i;

        if (len < 6) {
            return exception_pdu(out, fc, 3);
        }
        addr = (uint16_t)((pdu[1] << 8) | pdu[2]);
        count = (uint16_t)((pdu[3] << 8) | pdu[4]);
        nbytes = pdu[5];
        if (count == 0 || count > 123 || nbytes != (uint8_t)(count * 2u) || len < 6 + nbytes) {
            return exception_pdu(out, fc, 3);
        }
        for (i = 0; i < count; i++) {
            regs[i] = (uint16_t)((pdu[6 + i * 2] << 8) | pdu[7 + i * 2]);
        }
        ex = register_image_write_regs(addr, count, regs);
        if (ex != 0) {
            return exception_pdu(out, fc, (uint8_t)ex);
        }
        memcpy(out, pdu, 5);
        return 5;
    }

    return exception_pdu(out, fc, 1);
}
