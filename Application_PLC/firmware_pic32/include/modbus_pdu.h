#ifndef MODBUS_PDU_H
#define MODBUS_PDU_H

#include <stdint.h>

/* Returnerar svarslängd, eller 0 om PDU:n ska släppas. */
int modbus_pdu_handle(const uint8_t *pdu, int len, uint8_t *out);

#endif
