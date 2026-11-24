#include "node_logic.h"

#include "board_pins.h"
#include "modbus_rtu.h"

#include <stddef.h>

void node_init(NodeImage *node)
{
    node->tc_c10 = NODE_TEMP_FAULT;
    node->pt_c10 = NODE_TEMP_FAULT;
    node->lm35_c10 = 0;
    node->v0_mv = 0;
    node->ma_c100 = 0;
    node->v1_mv = 0;
    node->di = 0;
    node->ow_c10 = NODE_TEMP_FAULT;
    node->faults = NODE_FAULT_OW;
    node->mode = 0;
    node->ao_mv = 0;
    node->ao_ca = 0;
    node->dout = 0;
    node->watch_ms = NODE_WATCH_MS;
    node->last_master_ms = 0;
    node->master_seen = 0;
}

int16_t scale_lm35_c10(uint16_t counts)
{
    uint32_t mv = (uint32_t)counts * BOARD_ADC_MV / BOARD_ADC_FULL;

    if (mv > 1500u) {
        mv = 1500u;
    }
    return (int16_t)mv;
}

uint16_t scale_div_mv(uint16_t counts)
{
    uint32_t pin = (uint32_t)counts * BOARD_ADC_MV / BOARD_ADC_FULL;
    uint32_t field = pin * (BOARD_DIV_TOP + BOARD_DIV_BOT) / BOARD_DIV_BOT;

    if (field > 11000u) {
        field = 11000u;
    }
    return (uint16_t)field;
}

uint16_t scale_ma_c100(uint16_t counts)
{
    uint32_t mv = (uint32_t)counts * BOARD_ADC_MV / BOARD_ADC_FULL;
    uint32_t centi = mv * 100u / BOARD_BURDEN_OHM;

    if (centi > 2400u) {
        centi = 2400u;
    }
    return (uint16_t)centi;
}

int16_t scale_tc_c10(int32_t raw19, int fault)
{
    if (fault) {
        return NODE_TEMP_FAULT;
    }
    if (raw19 & 0x40000) {
        raw19 |= ~0x7FFFF;
    }
    return (int16_t)(raw19 * 10 / 128);
}

int16_t scale_pt1000_c10(uint16_t code15, int fault)
{
    uint32_t ohms;
    int32_t c10;

    if (fault || code15 == 0) {
        return NODE_TEMP_FAULT;
    }
    ohms = (uint32_t)code15 * BOARD_PT_RREF_OHM / 32768u;
    c10 = ((int32_t)ohms - 1000) * 1000 / 385;
    return (int16_t)c10;
}

uint16_t scale_dac_mv(uint16_t mv)
{
    if (mv > 10000u) {
        mv = 10000u;
    }
    return (uint16_t)((uint32_t)mv * 4095u / 10000u);
}

uint16_t scale_dac_ca(uint16_t centi_ma)
{
    if (centi_ma > 2000u) {
        centi_ma = 2000u;
    }
    return (uint16_t)((uint32_t)centi_ma * 4095u / 2000u);
}

void node_on_sample(NodeImage *node, const NodeSample *sample)
{
    node->tc_c10 = scale_tc_c10(sample->tc_raw19, sample->tc_fault);
    node->pt_c10 = scale_pt1000_c10(sample->rtd_code, sample->rtd_fault);
    node->lm35_c10 = scale_lm35_c10(sample->adc_lm35);
    node->v0_mv = scale_div_mv(sample->adc_v0);
    node->ma_c100 = scale_ma_c100(sample->adc_ma);
    node->v1_mv = scale_div_mv(sample->adc_v1);
    node->di = (uint8_t)(sample->di & 0x0Fu);
    if (sample->ow_ok) {
        node->ow_c10 = sample->ow_c10;
    } else {
        node->ow_c10 = NODE_TEMP_FAULT;
    }
    node->faults = 0;
    if (node->tc_c10 == NODE_TEMP_FAULT) {
        node->faults |= NODE_FAULT_TC;
    }
    if (node->pt_c10 == NODE_TEMP_FAULT) {
        node->faults |= NODE_FAULT_PT;
    }
    if (!sample->ow_ok) {
        node->faults |= NODE_FAULT_OW;
    }
}

void node_outputs(const NodeImage *node, uint32_t now_ms, NodeOutputs *out)
{
    int silent = !node->master_seen || node->mode != 0 ||
                 (now_ms - node->last_master_ms) > node->watch_ms;

    if (silent) {
        out->ao_mv = 0;
        out->ao_ca = 0;
        out->dout = 0;
        return;
    }
    out->ao_mv = node->ao_mv;
    out->ao_ca = node->ao_ca;
    out->dout = node->dout;
}

int16_t node_display_c10(const NodeImage *node)
{
    return node->lm35_c10;
}

static uint16_t read_reg(void *ctx, int holding, uint16_t addr, int *ok)
{
    NodeImage *node = ctx;

    *ok = 1;
    if (!holding) {
        switch (addr) {
        case NODE_IR_TC: return (uint16_t)node->tc_c10;
        case NODE_IR_PT: return (uint16_t)node->pt_c10;
        case NODE_IR_LM35: return (uint16_t)node->lm35_c10;
        case NODE_IR_V0: return node->v0_mv;
        case NODE_IR_MA: return node->ma_c100;
        case NODE_IR_V1: return node->v1_mv;
        case NODE_IR_DI: return node->di;
        case NODE_IR_OW: return (uint16_t)node->ow_c10;
        case NODE_IR_FAULT: return node->faults;
        default: *ok = 0; return 0;
        }
    }
    switch (addr) {
    case NODE_HR_MODE: return node->mode;
    case NODE_HR_AO_MV: return node->ao_mv;
    case NODE_HR_AO_CA: return node->ao_ca;
    case NODE_HR_DO: return node->dout;
    case NODE_HR_WATCH: return node->watch_ms;
    default: *ok = 0; return 0;
    }
}

static int write_reg(void *ctx, uint16_t addr, uint16_t value)
{
    NodeImage *node = ctx;

    switch (addr) {
    case NODE_HR_MODE:
        if (value > 1u) {
            return 3;
        }
        node->mode = value;
        return 0;
    case NODE_HR_AO_MV:
        if (value > 10000u) {
            return 3;
        }
        node->ao_mv = value;
        return 0;
    case NODE_HR_AO_CA:
        if (value > 2000u) {
            return 3;
        }
        node->ao_ca = value;
        return 0;
    case NODE_HR_DO:
        node->dout = (uint8_t)(value & 0x0Fu);
        return 0;
    case NODE_HR_WATCH:
        if (value < 200u || value > 60000u) {
            return 3;
        }
        node->watch_ms = value;
        return 0;
    default:
        return 2;
    }
}

int node_modbus(NodeImage *node, const uint8_t *frame, int len, uint8_t *rsp,
                int rsp_cap, uint32_t now_ms)
{
    int n = modbus_rtu_slave(frame, len, NODE_SLAVE_ID, read_reg, write_reg, node,
                             rsp, rsp_cap);

    if (n > 0) {
        node->master_seen = 1;
        node->last_master_ms = now_ms;
    }
    return n;
}
