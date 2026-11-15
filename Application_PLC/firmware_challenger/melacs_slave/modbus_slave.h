#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MELACS_HOLDING_COUNT 221
#define MELACS_INPUT_REG_COUNT 35
#define MELACS_COIL_COUNT 46
#define MELACS_DISCRETE_COUNT 14

#define MELACS_COIL_DIO4 16
#define MELACS_HOLD_AO0 100
#define MELACS_HOLD_SAFE 200

#define MELACS_DI_SD_OK 8
#define MELACS_DI_LOGGER_OK 9
#define MELACS_DI_PLC_LOADED 10
#define MELACS_DI_PLC_RUNNING 11

#define MELACS_IR_ERROR 20
#define MELACS_IR_TBOARD 30

#define MELACS_ERR_OK 0
#define MELACS_ERR_WIFI 1
#define MELACS_ERR_TIMEOUT 2
#define MELACS_ERR_SAFE 3

typedef struct {
    uint16_t holding[MELACS_HOLDING_COUNT];
    uint8_t coils[MELACS_COIL_COUNT];
    uint16_t input_reg[MELACS_INPUT_REG_COUNT];
    uint8_t discrete[MELACS_DISCRETE_COUNT];
} MelacsImage;

/* Bygger ett Modbus TCP-svar. 0 betyder att ramen inte gick att tyda. */
size_t melacs_modbus_tcp(MelacsImage *img, const uint8_t *req, size_t req_len,
                         uint8_t *rsp, size_t rsp_max);

#ifdef __cplusplus
}
#endif
