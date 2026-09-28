#include "plat_host.h"
#include "plc_runtime.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

static PlcInputs sim;
static int ticks;
static bool step_mode;
static RtcClock step_clk;
static bool wall_override;
static RtcClock wall_clk;
static time_t wall_base;

void plat_host_clock_step(const RtcClock *start)
{
    step_mode = true;
    wall_override = false;
    step_clk = *start;
}

void plat_host_clock_wall(void)
{
    step_mode = false;
    wall_override = false;
}

void plat_read_rtc(RtcClock *clk)
{
    if (step_mode) {
        *clk = step_clk;
        rtc_add_second(&step_clk);
        return;
    }
    if (wall_override) {
        time_t now = time(NULL);
        time_t elapsed = now - wall_base;
        RtcClock advanced = wall_clk;

        while (elapsed > 0) {
            rtc_add_second(&advanced);
            elapsed--;
        }
        *clk = advanced;
        return;
    }

    {
        time_t now = time(NULL);
        struct tm tm_now;

        localtime_r(&now, &tm_now);
        clk->year = (uint16_t)(tm_now.tm_year + 1900);
        clk->month = (uint8_t)(tm_now.tm_mon + 1);
        clk->day = (uint8_t)tm_now.tm_mday;
        clk->hour = (uint8_t)tm_now.tm_hour;
        clk->minute = (uint8_t)tm_now.tm_min;
        clk->second = (uint8_t)tm_now.tm_sec;
        clk->weekday = (uint8_t)tm_now.tm_wday;
    }
}

void plat_write_rtc(const RtcClock *clk)
{
    if (step_mode) {
        step_clk = *clk;
        return;
    }
    wall_clk = *clk;
    wall_base = time(NULL);
    wall_override = true;
}

void plat_read_inputs(PlcInputs *in)
{
    ticks++;
    sim.sd_ok = true;
    sim.ai[3] = 24;
    sim.ai[0] = (uint16_t)(20 + (ticks % 5));
    sim.dio_in[0] = (ticks / 4) % 2;
    memcpy(in, &sim, sizeof(sim));
}

void plat_sample_mark(void)
{
}

void plat_write_outputs(const PlcOutputs *out)
{
    (void)out;
}

bool plat_log_append(const char *path, const char *text)
{
    FILE *fp = fopen(path, "a");

    if (fp == NULL) {
        return false;
    }
    if (fputs(text, fp) < 0) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}
