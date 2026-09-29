#ifndef PLC_RUNTIME_H
#define PLC_RUNTIME_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint16_t ad[8];
    bool dio_in[4];
    uint16_t ai[6];
    uint16_t t_board;
    uint16_t p;
    uint16_t t1;
    uint16_t t2;
    uint16_t value;
    bool sd_ok;
    bool logger_ok;
    uint16_t error_code;
} PlcInputs;

typedef struct {
    bool dio_out[4];
    bool sip[8];
    bool h1_dis;
    bool h1_ali;
    bool h1_bli;
    bool h2_dis;
    bool h2_ali;
    bool h2_bli;
    uint16_t ao[3];
    uint16_t h1_ahi;
    uint16_t h1_bhi;
    uint16_t h2_ahi;
    uint16_t h2_bhi;
    uint16_t note;
} PlcOutputs;

typedef struct {
    bool plc_loaded;
    bool plc_running;
    bool logger_ok;
    uint16_t safe_mode;
    uint16_t log_period_s; /* Sekunder mellan CSV-rader. Sampel tas varje sekund. */
    uint32_t scan_count;
    uint32_t log_count;
} PlcStatus;

void plc_runtime_init(const char *log_path);
void plc_runtime_tick(void);

const PlcInputs *plc_inputs(void);
PlcOutputs *plc_outputs(void);
const PlcStatus *plc_status(void);

void plat_read_inputs(PlcInputs *in);
void plat_write_outputs(const PlcOutputs *out);
void plat_seed_pack(void);

void safe_outputs(PlcOutputs *out);

#endif
