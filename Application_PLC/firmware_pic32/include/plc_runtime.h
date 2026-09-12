#ifndef PLC_RUNTIME_H
#define PLC_RUNTIME_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint16_t ad[8];
    bool dio_in[4];
    uint16_t heater_temp;
    uint16_t engine_temp;
    uint16_t engine_pressure;
    uint16_t board_temp;
    uint16_t m1_current;
    uint16_t m2_current;
    bool sd_ok;
    bool logger_ok;
    uint16_t error_code;
} PlcInputs;

typedef struct {
    bool dio_out[4];
    uint16_t burner_fan_sp;
    uint16_t radiator_fan_sp;
    uint16_t valve_pos;
} PlcOutputs;

typedef struct {
    bool plc_loaded;
    bool plc_running;
    bool logger_ok;
    uint16_t safe_mode;
    uint16_t log_period_s;
    uint32_t scan_count;
    uint32_t log_count;
} PlcStatus;

void plc_runtime_init(void);
void plc_runtime_tick(void);

const PlcInputs *plc_inputs(void);
PlcOutputs *plc_outputs(void);
const PlcStatus *plc_status(void);

/* Hooks implemented per target (host-test or PIC32 HAL). */
void plat_read_inputs(PlcInputs *in);
void plat_write_outputs(const PlcOutputs *out);
void plat_logger_tick(const PlcInputs *in, const PlcStatus *st);
bool plat_plc_program_present(void);
void plat_boot_check(void);
void plat_read_rtc(uint16_t *year, uint8_t *month, uint8_t *day,
                   uint8_t *hour, uint8_t *minute, uint8_t *second);

/* OpenPLC/MatIEC scan (plc_scan.c + plc_generated). */
void plc_scan(PlcInputs *in, PlcOutputs *out);

void safe_outputs(PlcOutputs *out);

#endif
