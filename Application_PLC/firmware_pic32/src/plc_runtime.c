#include "plc_runtime.h"

#include "fast_ctrl.h"
#include "log_history.h"
#include "logger.h"
#include "protect.h"
#include "register_image.h"
#include "rtc.h"

#include <string.h>

static PlcInputs g_in;
static PlcOutputs g_out;
static PlcStatus g_st;

void safe_outputs(PlcOutputs *out)
{
    memset(out, 0, sizeof(*out));
    /* Spärr hög = bryggan av. Låg spärr släpper på drivningen. */
    out->h1_dis = true;
    out->h2_dis = true;
}

void plc_runtime_init(const char *log_path)
{
    rtc_init();
    logger_init(log_path);
    register_image_init();
    fast_ctrl_init();
    g_st.safe_mode = 0;
    g_st.log_period_s = MELACS_LOG_PERIOD_S;
    g_st.scan_count = 0;
    g_st.log_count = 0;
    g_st.plc_loaded = false;
    g_st.plc_running = false;
    g_st.logger_ok = false;
    safe_outputs(&g_out);
}

void plc_runtime_tick(void)
{
    RtcClock clk;

    plat_seed_pack();
    RtcClock set_clk;
    PlcOutputs cmd;
    uint16_t safe_mode;
    uint16_t period;
    bool master;

    rtc_poll();
    rtc_get(&clk);
    plat_read_inputs(&g_in);
    register_image_sweep();
    fast_ctrl_sweep_kick(plat_millis());

    register_image_commands(&cmd, &safe_mode, &period, &master);
    g_st.safe_mode = safe_mode;
    g_st.log_period_s = period;

    if (register_image_take_clock(&set_clk) && rtc_set(&set_clk)) {
        rtc_get(&clk);
    }
    if (register_image_take_beep()) {
        plat_beep();
    }

    {
        ProtectIn pin;
        ProtectOut pout;
        int i;

        for (i = 0; i < 4; i++) {
            pin.dio[i] = g_in.dio_in[i];
        }
        for (i = 0; i < 6; i++) {
            pin.ai[i] = g_in.ai[i];
        }
        protect_step(&pin, &pout);

        g_st.plc_loaded = master;
        if (master && g_st.safe_mode == 0 && protect_ok()) {
            g_out = cmd;
            protect_apply(pout.mask, &g_out);
            g_st.plc_running = true;
        } else {
            safe_outputs(&g_out);
            g_st.plc_running = false;
        }
        /* Snabba PID-kanaler får bara driva när PLC-utgångarna är släppta. */
        fast_ctrl_set_run(g_st.plc_running);
        fast_ctrl_set_guard(
            !protect_ok() || (pout.mask & PROT_INH_H1) != 0,
            !protect_ok() || (pout.mask & PROT_INH_H2) != 0);
        {
            uint16_t trip = 0;
            (void)fast_ctrl_read_input(300u, &trip);
            logger_watch(&clk, protect_ok(), protect_fault(), master ? 1 : 0,
                         g_st.safe_mode, pout.mask, trip);
        }
    }

    if (logger_tick(&clk, g_st.log_period_s, &g_in, &g_out, &g_st)) {
        g_st.log_count++;
        g_st.logger_ok = g_in.sd_ok;
    } else if (logger_failed() || !g_in.sd_ok) {
        g_st.logger_ok = false;
    }
    g_in.logger_ok = g_st.logger_ok;

    plat_write_outputs(&g_out);
    register_image_publish(&g_in, &g_out, &g_st, &clk);
    log_history_poll(&clk);
    g_st.scan_count++;
}

const PlcInputs *plc_inputs(void) { return &g_in; }
PlcOutputs *plc_outputs(void) { return &g_out; }
const PlcStatus *plc_status(void) { return &g_st; }
