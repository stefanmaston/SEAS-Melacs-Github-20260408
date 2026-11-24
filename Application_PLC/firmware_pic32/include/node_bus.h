#ifndef NODE_BUS_H
#define NODE_BUS_H

#include <stdint.h>

#define NODE_BUS_SLAVE 1
#define NODE_BUS_REG_LM35 2
#define NODE_BUS_FAULT ((int16_t)0x8000)

typedef struct {
    void (*set_de)(int transmit);
    int (*write)(const uint8_t *data, int len);
    int (*read)(uint8_t *data, int cap);
    int (*tx_done)(void);
} NodeBusIo;

void node_uart_init(void);
void node_uart_set_de(int transmit);
int node_uart_write(const uint8_t *data, int len);
int node_uart_read(uint8_t *data, int cap);
int node_uart_tx_done(void);

/* Testet byter ut UART:en. NULL återgår till node_uart_*. */
void node_bus_set_io(const NodeBusIo *io);
void node_bus_poll(uint32_t now_ms);
int16_t node_bus_lm35_c10(void);
int node_bus_fresh(void);

#endif
