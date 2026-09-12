#include "oem_reuse.h"
#include "plc_runtime.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

static PlcInputs sim;
static int ticks;

void plat_boot_check(void)
{
    printf("boot: host (OEM bootloader_recovery_second_step körs bara på PIC32)\n");
}

void plat_read_rtc(uint16_t *year, uint8_t *month, uint8_t *day,
                   uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (!t) {
        return;
    }
    if (year) {
        *year = (uint16_t)(t->tm_year + 1900);
    }
    if (month) {
        *month = (uint8_t)(t->tm_mon + 1);
    }
    if (day) {
        *day = (uint8_t)t->tm_mday;
    }
    if (hour) {
        *hour = (uint8_t)t->tm_hour;
    }
    if (minute) {
        *minute = (uint8_t)t->tm_min;
    }
    if (second) {
        *second = (uint8_t)t->tm_sec;
    }
}

void plat_read_inputs(PlcInputs *in)
{
    uint16_t y;
    uint8_t mo, d, h, mi, s;

    ticks++;
    sim.sd_ok = true;
    sim.board_temp = 24;
    sim.heater_temp = 20 + (uint16_t)(ticks % 5);
    sim.dio_in[0] = (ticks / 4) % 2;
    plat_read_rtc(&y, &mo, &d, &h, &mi, &s);
    (void)y;
    (void)mo;
    (void)d;
    (void)h;
    (void)mi;
    (void)s;
    memcpy(in, &sim, sizeof(sim));
}

void plat_write_outputs(const PlcOutputs *out)
{
    printf("out dio4=%d (OpenPLC %%QX0.0)\n", out->dio_out[0] ? 1 : 0);
}

void plat_logger_tick(const PlcInputs *in, const PlcStatus *st)
{
    printf("log #%u heater=%u dio0=%d plc=%d running=%d (OEM logRunAvg på PIC32)\n",
           (unsigned)st->log_count,
           (unsigned)in->heater_temp,
           in->dio_in[0] ? 1 : 0,
           st->plc_loaded ? 1 : 0,
           st->plc_running ? 1 : 0);
}

bool plat_plc_program_present(void)
{
    return plc_loader_program_present();
}
