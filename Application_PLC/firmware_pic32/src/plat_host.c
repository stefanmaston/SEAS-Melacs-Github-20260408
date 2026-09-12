#include "plc_runtime.h"

#include <stdio.h>
#include <string.h>

static PlcInputs sim;
static int ticks;

void plat_read_inputs(PlcInputs *in)
{
    ticks++;
    sim.sd_ok = true;
    sim.board_temp = 24;
    sim.heater_temp = 20 + (uint16_t)(ticks % 5);
    sim.dio_in[0] = (ticks / 4) % 2;
    memcpy(in, &sim, sizeof(sim));
}

void plat_write_outputs(const PlcOutputs *out)
{
    (void)out;
}

void plat_logger_tick(const PlcInputs *in, const PlcStatus *st)
{
    printf("log #%u heater=%u dio0=%d plc=%d running=%d\n",
           (unsigned)st->log_count,
           (unsigned)in->heater_temp,
           in->dio_in[0] ? 1 : 0,
           st->plc_loaded ? 1 : 0,
           st->plc_running ? 1 : 0);
}

bool plat_plc_program_present(void)
{
    return true;
}
