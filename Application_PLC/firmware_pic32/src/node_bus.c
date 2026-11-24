#include "node_bus.h"

#include "modbus_rtu.h"

#define NODE_BUS_PERIOD_MS 1000u
#define NODE_BUS_RX_MS 40u

enum { ST_IDLE = 0, ST_TX, ST_RX };

static const NodeBusIo *g_io;
static uint8_t g_rx[16];
static int g_rx_n;
static uint32_t g_stamp;
static int g_same;
static int g_armed;
static int g_phase;
static int16_t g_lm35 = NODE_BUS_FAULT;
static int g_fresh;

static void set_de(int transmit)
{
    if (g_io != 0 && g_io->set_de != 0) {
        g_io->set_de(transmit);
    } else {
        node_uart_set_de(transmit);
    }
}

static int write_bytes(const uint8_t *data, int len)
{
    if (g_io != 0 && g_io->write != 0) {
        return g_io->write(data, len);
    }
    return node_uart_write(data, len);
}

static int read_bytes(uint8_t *data, int cap)
{
    if (g_io != 0 && g_io->read != 0) {
        return g_io->read(data, cap);
    }
    return node_uart_read(data, cap);
}

static int tx_idle(void)
{
    if (g_io != 0 && g_io->tx_done != 0) {
        return g_io->tx_done();
    }
    return node_uart_tx_done();
}

static void begin_tx(uint32_t now)
{
    uint8_t req[8];
    int n = modbus_rtu_read_req(req, (int)sizeof req, NODE_BUS_SLAVE, 4,
                                NODE_BUS_REG_LM35, 1);

    set_de(1);
    write_bytes(req, n);
    g_phase = ST_TX;
    g_stamp = now;
    g_same = 0;
    g_rx_n = 0;
    g_armed = 1;
}

static void go_idle(uint32_t now)
{
    set_de(0);
    g_phase = ST_IDLE;
    g_stamp = now;
}

static int bus_once(uint32_t now, int count_wait)
{
    if (g_phase == ST_IDLE) {
        if (g_armed && now == g_stamp) {
            return 0;
        }
        if (g_armed && (now - g_stamp) < NODE_BUS_PERIOD_MS) {
            return 0;
        }
        begin_tx(now);
        return 1;
    }

    if (g_phase == ST_TX) {
        if (tx_idle()) {
            set_de(0);
            g_phase = ST_RX;
            g_rx_n = 0;
            g_stamp = now;
            g_same = 0;
            return 1;
        }
        if (count_wait && now == g_stamp && ++g_same >= 2) {
            go_idle(now);
            return 0;
        }
        if (now != g_stamp && (now - g_stamp) > 20u) {
            go_idle(now);
        }
        return 0;
    }

    {
        uint8_t chunk[16];
        int n = read_bytes(chunk, (int)sizeof chunk);
        int i;

        for (i = 0; i < n && g_rx_n < (int)sizeof g_rx; i++) {
            g_rx[g_rx_n++] = chunk[i];
        }
        if (g_rx_n >= 7) {
            uint16_t reg = 0;
            int got = modbus_rtu_parse_read(g_rx, g_rx_n, NODE_BUS_SLAVE, &reg, 1);

            if (got == 1) {
                g_lm35 = (int16_t)reg;
                g_fresh = 1;
                go_idle(now);
                return 0;
            }
            if (got < 0) {
                go_idle(now);
                return 0;
            }
        }
        if (n == 0) {
            if (!count_wait && g_same == 0) {
                g_same = 1;
            } else if (count_wait && ++g_same >= 2) {
                go_idle(now);
                return 0;
            }
        }
        if (now != g_stamp && (now - g_stamp) > NODE_BUS_RX_MS) {
            go_idle(now);
        }
        return 0;
    }
}

void node_bus_set_io(const NodeBusIo *io)
{
    g_io = io;
}

void node_bus_poll(uint32_t now)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (!bus_once(now, i == 0)) {
            break;
        }
    }
}

int16_t node_bus_lm35_c10(void)
{
    return g_lm35;
}

int node_bus_fresh(void)
{
    return g_fresh;
}
