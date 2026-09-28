#include "pic32_board.h"
#include "plc_runtime.h"
#include "rtc.h"

static uint32_t g_soft_ms;
static int g_soft_ready;

void plat_read_inputs(PlcInputs *in)
{
    io_read(in);
    in->sd_ok = sd_ok();
    in->error_code = 0;
    if (!in->sd_ok) {
        in->error_code |= 1u;
    }
    if (!rtc_chip_ok()) {
        in->error_code |= 2u;
    }
    if (!net_up()) {
        in->error_code |= 4u;
    }
}

void plat_sample_mark(void)
{
    memled_pulse();
}

void plat_write_outputs(const PlcOutputs *out)
{
    io_write(out);
}

void plat_read_rtc(RtcClock *clk)
{
    if (rtc_chip_read(clk)) {
        g_soft_ready = 0;
        return;
    }
    if (!g_soft_ready) {
        g_soft_ms = board_millis();
        g_soft_ready = 1;
        return;
    }
    if (board_millis() - g_soft_ms >= 1000u) {
        g_soft_ms += 1000u;
        rtc_add_second(clk);
    }
}

void plat_write_rtc(const RtcClock *clk)
{
    (void)rtc_chip_write(clk);
}

bool plat_log_append(const char *path, const char *text)
{
    return sd_append_line(path, text);
}
