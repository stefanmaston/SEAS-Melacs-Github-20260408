#include "node_bus.h"
#include "pin_map.h"

#include <xc.h>

/*
 * PBCLK är 36 MHz. BRGH = 0 ger U5BRG = 36e6 / (16 * 9600) - 1 = 233.
 * Det blir 9615 baud, 0,16 procent fel.
 */
#define NODE_UART_BRG 233

void node_uart_init(void)
{
    PIN_NODE_DE_CLR();
    PIN_NODE_DE_TRIS = 0;
    PIN_NODE_TX_TRIS = 0;
    PIN_NODE_RX_TRIS = 1;

    U5MODE = 0;
    U5STA = 0;
    U5BRG = NODE_UART_BRG;
    U5STAbits.UTXEN = 1;
    U5STAbits.URXEN = 1;
    U5MODEbits.UARTEN = 1;
}

void node_uart_set_de(int transmit)
{
    if (transmit) {
        PIN_NODE_DE_SET();
    } else {
        PIN_NODE_DE_CLR();
    }
}

int node_uart_write(const uint8_t *data, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        while (U5STAbits.UTXBF) {
        }
        U5TXREG = data[i];
    }
    return len;
}

int node_uart_read(uint8_t *data, int cap)
{
    int n = 0;

    if (U5STAbits.OERR) {
        U5STAbits.OERR = 0;
    }
    while (n < cap && U5STAbits.URXDA) {
        data[n++] = (uint8_t)U5RXREG;
    }
    return n;
}

int node_uart_tx_done(void)
{
    return U5STAbits.TRMT != 0;
}
