#include "modbus_rtu.h"
#include "node_bus.h"

#include <stdio.h>
#include <string.h>

static int g_fails;
static uint8_t g_tx[16];
static int g_tx_n;
static int g_writes;
static uint8_t g_rx[16];
static int g_rx_n;
static int g_rx_pos;

static void expect(int cond, const char *msg)
{
    if (!cond) {
        fprintf(stderr, "fel: %s\n", msg);
        g_fails++;
    }
}

static void test_de(int transmit)
{
    (void)transmit;
}

static int test_write(const uint8_t *data, int len)
{
    if (len > (int)sizeof g_tx) {
        len = (int)sizeof g_tx;
    }
    memcpy(g_tx, data, (size_t)len);
    g_tx_n = len;
    g_writes++;
    return len;
}

static int test_read(uint8_t *data, int cap)
{
    int n = g_rx_n - g_rx_pos;

    if (n > cap) {
        n = cap;
    }
    if (n <= 0) {
        return 0;
    }
    memcpy(data, g_rx + g_rx_pos, (size_t)n);
    g_rx_pos += n;
    return n;
}

static int test_tx_done(void)
{
    return 1;
}

static void load_rx(uint16_t value)
{
    uint16_t crc;

    g_rx[0] = NODE_BUS_SLAVE;
    g_rx[1] = 4;
    g_rx[2] = 2;
    g_rx[3] = (uint8_t)(value >> 8);
    g_rx[4] = (uint8_t)value;
    crc = modbus_crc(g_rx, 5);
    g_rx[5] = (uint8_t)crc;
    g_rx[6] = (uint8_t)(crc >> 8);
    g_rx_n = 7;
    g_rx_pos = 0;
}

int test_node_bus(void)
{
    NodeBusIo io;
    uint8_t expect_req[8];
    int n;

    io.set_de = test_de;
    io.write = test_write;
    io.read = test_read;
    io.tx_done = test_tx_done;
    node_bus_set_io(&io);

    load_rx(234);
    node_bus_poll(1000);
    n = modbus_rtu_read_req(expect_req, 8, NODE_BUS_SLAVE, 4, NODE_BUS_REG_LM35, 1);
    expect(g_writes == 1 && g_tx_n == n && memcmp(g_tx, expect_req, (size_t)n) == 0,
           "mastern läser LM35-registret");
    expect(node_bus_fresh() && node_bus_lm35_c10() == 234, "temperaturen tas emot");
    node_bus_poll(1000);
    expect(g_writes == 1, "samma millisekund skickar inte en ny fråga");

    g_rx_n = 0;
    g_rx_pos = 0;
    g_writes = 0;
    node_bus_poll(0);
    node_bus_poll(0);
    node_bus_poll(2000);
    expect(g_writes == 2, "tiden går vidare och frågan ställs igen");

    node_bus_set_io(0);
    if (g_fails) {
        fprintf(stderr, "node-bus: %d fel\n", g_fails);
    }
    return g_fails;
}
