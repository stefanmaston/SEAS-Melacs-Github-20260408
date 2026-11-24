#ifndef NODE_LOGIC_H
#define NODE_LOGIC_H

#include <stdint.h>

#define NODE_SLAVE_ID 1
#define NODE_TEMP_FAULT ((int16_t)0x8000)
#define NODE_WATCH_MS 3000u

enum {
    NODE_IR_TC = 0,
    NODE_IR_PT = 1,
    NODE_IR_LM35 = 2,
    NODE_IR_V0 = 3,
    NODE_IR_MA = 4,
    NODE_IR_V1 = 5,
    NODE_IR_DI = 6,
    NODE_IR_OW = 7,
    NODE_IR_FAULT = 8,
    NODE_IR_COUNT = 9
};

enum {
    NODE_HR_MODE = 0,
    NODE_HR_AO_MV = 1,
    NODE_HR_AO_CA = 2,
    NODE_HR_DO = 3,
    NODE_HR_WATCH = 4,
    NODE_HR_COUNT = 5
};

enum {
    NODE_FAULT_TC = 1,
    NODE_FAULT_PT = 2,
    NODE_FAULT_OW = 4
};

/* Råvärden från kretsarna. Fältnoden fyller den här före varje svep. */
typedef struct {
    int32_t tc_raw19;
    int tc_fault;
    uint16_t rtd_code;
    int rtd_fault;
    uint16_t adc_lm35;
    uint16_t adc_v0;
    uint16_t adc_ma;
    uint16_t adc_v1;
    uint8_t di;
    int16_t ow_c10;
    int ow_ok;
} NodeSample;

typedef struct {
    int16_t tc_c10;
    int16_t pt_c10;
    int16_t lm35_c10;
    uint16_t v0_mv;
    uint16_t ma_c100;
    uint16_t v1_mv;
    uint8_t di;
    int16_t ow_c10;
    uint16_t faults;
    uint16_t mode;
    uint16_t ao_mv;
    uint16_t ao_ca;
    uint8_t dout;
    uint16_t watch_ms;
    uint32_t last_master_ms;
    int master_seen;
} NodeImage;

typedef struct {
    uint16_t ao_mv;
    uint16_t ao_ca;
    uint8_t dout;
} NodeOutputs;

void node_init(NodeImage *node);
void node_on_sample(NodeImage *node, const NodeSample *sample);
void node_outputs(const NodeImage *node, uint32_t now_ms, NodeOutputs *out);

/* Visningstalet är LM35, även när utgångarna ligger i säkert läge. */
int16_t node_display_c10(const NodeImage *node);

int node_modbus(NodeImage *node, const uint8_t *frame, int len, uint8_t *rsp,
                int rsp_cap, uint32_t now_ms);

int16_t scale_lm35_c10(uint16_t counts);
uint16_t scale_div_mv(uint16_t counts);
uint16_t scale_ma_c100(uint16_t counts);
int16_t scale_tc_c10(int32_t raw19, int fault);
int16_t scale_pt1000_c10(uint16_t code15, int fault);
uint16_t scale_dac_mv(uint16_t mv);
uint16_t scale_dac_ca(uint16_t centi_ma);

#endif
