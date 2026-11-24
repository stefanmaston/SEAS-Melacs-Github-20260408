#include "node_bus.h"

void node_uart_init(void)
{
}

void node_uart_set_de(int transmit)
{
    (void)transmit;
}

int node_uart_write(const uint8_t *data, int len)
{
    (void)data;
    return len;
}

int node_uart_read(uint8_t *data, int cap)
{
    (void)data;
    (void)cap;
    return 0;
}

int node_uart_tx_done(void)
{
    return 1;
}
