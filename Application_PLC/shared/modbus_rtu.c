#include "modbus_rtu.h"

uint16_t modbus_crc(const uint8_t *data, int len)
{
    uint16_t crc = 0xFFFFu;
    int i;
    int bit;

    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (bit = 0; bit < 8; bit++) {
            if (crc & 1u) {
                crc = (uint16_t)((crc >> 1) ^ 0xA001u);
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

static int put_crc(uint8_t *frame, int len)
{
    uint16_t crc = modbus_crc(frame, len);

    frame[len] = (uint8_t)crc;
    frame[len + 1] = (uint8_t)(crc >> 8);
    return len + 2;
}

static int crc_ok(const uint8_t *frame, int len)
{
    uint16_t got;
    uint16_t expect;

    if (len < 4) {
        return 0;
    }
    got = (uint16_t)frame[len - 2] | ((uint16_t)frame[len - 1] << 8);
    expect = modbus_crc(frame, len - 2);
    return got == expect;
}

int modbus_rtu_read_req(uint8_t *dst, int cap, uint8_t slave, uint8_t func,
                        uint16_t addr, uint16_t count)
{
    if (dst == 0 || cap < 8 || count == 0 || count > 125) {
        return 0;
    }
    dst[0] = slave;
    dst[1] = func;
    dst[2] = (uint8_t)(addr >> 8);
    dst[3] = (uint8_t)addr;
    dst[4] = (uint8_t)(count >> 8);
    dst[5] = (uint8_t)count;
    return put_crc(dst, 6);
}

int modbus_rtu_parse_read(const uint8_t *frame, int len, uint8_t slave,
                          uint16_t *regs, int max_regs)
{
    int nbytes;
    int nreg;
    int i;

    if (frame == 0 || len < 7 || !crc_ok(frame, len)) {
        return -1;
    }
    if (frame[0] != slave) {
        return 0;
    }
    if (frame[1] & 0x80u) {
        return -1;
    }
    if (frame[1] != 3 && frame[1] != 4) {
        return -1;
    }
    nbytes = frame[2];
    if (nbytes != len - 5 || (nbytes & 1) != 0) {
        return -1;
    }
    nreg = nbytes / 2;
    if (nreg > max_regs) {
        return -1;
    }
    for (i = 0; i < nreg; i++) {
        regs[i] = (uint16_t)((frame[3 + 2 * i] << 8) | frame[4 + 2 * i]);
    }
    return nreg;
}

static int exception(uint8_t *rsp, int cap, uint8_t slave, uint8_t func, uint8_t code)
{
    if (cap < 5) {
        return 0;
    }
    rsp[0] = slave;
    rsp[1] = (uint8_t)(func | 0x80u);
    rsp[2] = code;
    return put_crc(rsp, 3);
}

int modbus_rtu_slave(const uint8_t *frame, int len, uint8_t slave,
                     modbus_read_fn read_reg, modbus_write_fn write_reg,
                     void *ctx, uint8_t *rsp, int rsp_cap)
{
    uint8_t func;
    uint16_t addr;
    uint16_t count;
    int holding;
    int i;
    int ok;
    int wr;

    if (frame == 0 || len < 8 || !crc_ok(frame, len)) {
        return -1;
    }
    if (frame[0] != slave) {
        return 0;
    }
    func = frame[1];
    addr = (uint16_t)((frame[2] << 8) | frame[3]);
    count = (uint16_t)((frame[4] << 8) | frame[5]);

    if (func == 3 || func == 4) {
        if (count == 0 || count > 16 || rsp_cap < 5 + count * 2) {
            return exception(rsp, rsp_cap, slave, func, 3);
        }
        holding = func == 3;
        rsp[0] = slave;
        rsp[1] = func;
        rsp[2] = (uint8_t)(count * 2);
        for (i = 0; i < (int)count; i++) {
            uint16_t value = read_reg(ctx, holding, (uint16_t)(addr + i), &ok);

            if (!ok) {
                return exception(rsp, rsp_cap, slave, func, 2);
            }
            rsp[3 + 2 * i] = (uint8_t)(value >> 8);
            rsp[4 + 2 * i] = (uint8_t)value;
        }
        return put_crc(rsp, 3 + count * 2);
    }

    if (func == 6) {
        wr = write_reg(ctx, addr, count);
        if (wr != 0) {
            return exception(rsp, rsp_cap, slave, func, (uint8_t)wr);
        }
        if (rsp_cap < 8) {
            return 0;
        }
        for (i = 0; i < 6; i++) {
            rsp[i] = frame[i];
        }
        return put_crc(rsp, 6);
    }

    if (func == 16) {
        int bytes;

        if (len < 9) {
            return -1;
        }
        bytes = frame[6];
        if (count == 0 || count > 16 || bytes != count * 2 || len != 9 + bytes) {
            return exception(rsp, rsp_cap, slave, func, 3);
        }
        for (i = 0; i < (int)count; i++) {
            uint16_t value = (uint16_t)((frame[7 + 2 * i] << 8) | frame[8 + 2 * i]);

            wr = write_reg(ctx, (uint16_t)(addr + i), value);
            if (wr != 0) {
                return exception(rsp, rsp_cap, slave, func, (uint8_t)wr);
            }
        }
        if (rsp_cap < 8) {
            return 0;
        }
        rsp[0] = slave;
        rsp[1] = func;
        rsp[2] = frame[2];
        rsp[3] = frame[3];
        rsp[4] = frame[4];
        rsp[5] = frame[5];
        return put_crc(rsp, 6);
    }

    return exception(rsp, rsp_cap, slave, func, 1);
}
