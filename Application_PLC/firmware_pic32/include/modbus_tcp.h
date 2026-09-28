#ifndef MODBUS_TCP_H
#define MODBUS_TCP_H

#include <stdbool.h>
#include <stdint.h>

#ifndef MELACS_MODBUS_PORT
#define MELACS_MODBUS_PORT 1502
#endif

bool modbus_tcp_start(uint16_t port);
void modbus_tcp_stop(void);

#endif
