#include "plc_runtime.h"

static PlcInputs g_in;
static PlcOutputs g_out;
static PlcStatus g_st;

void safe_outputs(PlcOutputs *out)
{
    out->dio_out[0] = false;
    out->dio_out[1] = false;
    out->dio_out[2] = false;
    out->dio_out[3] = false;
    out->burner_fan_sp = 0;
    out->radiator_fan_sp = 0;
    out->valve_pos = 0;
}

void plc_runtime_init(void)
{
    g_st.safe_mode = 0;
    g_st.log_period_s = 1;
    g_st.scan_count = 0;
    g_st.log_count = 0;
    g_st.plc_loaded = plat_plc_program_present();
    g_st.plc_running = false;
    plat_boot_check();
    safe_outputs(&g_out);
}

void plc_runtime_tick(void)
{
    plat_read_inputs(&g_in);

    plat_logger_tick(&g_in, &g_st);
    g_st.log_count++;
    g_st.logger_ok = g_in.sd_ok;
    g_in.logger_ok = g_in.sd_ok;

    g_st.plc_loaded = plat_plc_program_present();
    if (g_st.plc_loaded && g_st.safe_mode == 0) {
        plc_scan(&g_in, &g_out);
        g_st.plc_running = true;
    } else {
        safe_outputs(&g_out);
        g_st.plc_running = false;
    }

    plat_write_outputs(&g_out);
    g_st.scan_count++;
}

const PlcInputs *plc_inputs(void) { return &g_in; }
PlcOutputs *plc_outputs(void) { return &g_out; }
const PlcStatus *plc_status(void) { return &g_st; }
