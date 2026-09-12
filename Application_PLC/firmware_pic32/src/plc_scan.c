#include "plc_iec.h"

static int s_inited;
static unsigned long s_tick;

void plc_scan(PlcInputs *in, PlcOutputs *out)
{
    plc_iec_bind(in, out);
    if (!s_inited) {
        config_init__();
        s_inited = 1;
    }
    config_run__(s_tick++);
    plc_iec_commit(out);
}
