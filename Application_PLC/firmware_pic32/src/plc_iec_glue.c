#include "plc_iec.h"

IEC_BOOL *__IX0_0;
IEC_BOOL *__IX0_1;
IEC_BOOL *__IX0_2;
IEC_BOOL *__IX0_3;
IEC_BOOL *__QX0_0;
IEC_BOOL *__QX0_1;
IEC_BOOL *__QX0_2;
IEC_BOOL *__QX0_3;
IEC_UINT *__IW0;
IEC_UINT *__IW1;
IEC_UINT *__IW10;
IEC_UINT *__QW0;
IEC_UINT *__QW1;
IEC_UINT *__QW2;

static IEC_BOOL ix0, ix1, ix2, ix3;
static IEC_BOOL qx0, qx1, qx2, qx3;
static IEC_UINT iw0, iw1, iw10;
static IEC_UINT qw0, qw1, qw2;

void plc_iec_bind(PlcInputs *in, PlcOutputs *out)
{
    ix0 = in->dio_in[0];
    ix1 = in->dio_in[1];
    ix2 = in->dio_in[2];
    ix3 = in->dio_in[3];
    iw0 = in->ad[0];
    iw1 = in->ad[1];
    iw10 = in->heater_temp;
    qx0 = out->dio_out[0];
    qx1 = out->dio_out[1];
    qx2 = out->dio_out[2];
    qx3 = out->dio_out[3];
    qw0 = out->burner_fan_sp;
    qw1 = out->radiator_fan_sp;
    qw2 = out->valve_pos;

    __IX0_0 = &ix0;
    __IX0_1 = &ix1;
    __IX0_2 = &ix2;
    __IX0_3 = &ix3;
    __QX0_0 = &qx0;
    __QX0_1 = &qx1;
    __QX0_2 = &qx2;
    __QX0_3 = &qx3;
    __IW0 = &iw0;
    __IW1 = &iw1;
    __IW10 = &iw10;
    __QW0 = &qw0;
    __QW1 = &qw1;
    __QW2 = &qw2;
}

void plc_iec_commit(PlcOutputs *out)
{
    out->dio_out[0] = qx0;
    out->dio_out[1] = qx1;
    out->dio_out[2] = qx2;
    out->dio_out[3] = qx3;
    out->burner_fan_sp = qw0;
    out->radiator_fan_sp = qw1;
    out->valve_pos = qw2;
}
