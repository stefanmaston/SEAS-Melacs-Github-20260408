#include "logger.h"
#include "plat_host.h"
#include "plc_runtime.h"
#include "sd_pack.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

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

static int g_beeps;

void plat_write_outputs(const PlcOutputs *out)
{
    (void)out;
}

uint32_t plat_millis(void)
{
    return 0;
}

void plat_beep(void)
{
    g_beeps++;
}

int plat_host_beep_count(void)
{
    return g_beeps;
}

bool plat_log_append(const char *path, const char *text)
{
    FILE *fp = fopen(path, "a");

    if (fp == NULL || text == NULL) {
        if (fp != NULL) {
            fclose(fp);
        }
        return false;
    }
    if (fputs(text, fp) < 0 || fflush(fp) != 0 || fsync(fileno(fp)) != 0) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

bool plat_log_size(const char *path, uint32_t *size)
{
    struct stat st;

    if (size == NULL) {
        return false;
    }
    if (path == NULL || stat(path, &st) != 0) {
        *size = 0;
        return true;
    }
    *size = (uint32_t)st.st_size;
    return true;
}

bool plat_log_repair(const char *path)
{
    FILE *fp;
    long size;
    long window;
    long found = -1;
    unsigned char buf[512];
    size_t n;
    size_t i;

    if (path == NULL) {
        return false;
    }
    fp = fopen(path, "rb+");
    if (fp == NULL) {
        return true;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return false;
    }
    size = ftell(fp);
    if (size <= 0) {
        fclose(fp);
        return true;
    }
    if (fseek(fp, -1, SEEK_END) != 0) {
        fclose(fp);
        return false;
    }
    if (fgetc(fp) == '\n') {
        fclose(fp);
        return true;
    }
    window = size > 512 ? size - 512 : 0;
    if (fseek(fp, window, SEEK_SET) != 0) {
        fclose(fp);
        return false;
    }
    n = fread(buf, 1, sizeof(buf), fp);
    for (i = 0; i < n; i++) {
        if (buf[i] == '\n') {
            found = window + (long)i;
        }
    }
    if (found >= 0 && ftruncate(fileno(fp), found + 1) != 0) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

static void sibling_path(const char *log_path, const char *name, char *out, size_t n)
{
    const char *slash = strrchr(log_path, '/');

    if (slash == NULL) {
        snprintf(out, n, "%s", name);
        return;
    }
    snprintf(out, n, "%.*s/%s", (int)(slash - log_path), log_path, name);
}

static bool write_if_absent(const char *path, const void *data, uint32_t len)
{
    FILE *fp;

    if (access(path, F_OK) == 0) {
        return true;
    }
    fp = fopen(path, "wb");
    if (fp == NULL) {
        return false;
    }
    if (fwrite(data, 1, len, fp) != len) {
        fclose(fp);
        remove(path);
        return false;
    }
    fclose(fp);
    return true;
}

void plat_seed_pack(void)
{
    static int done;
    char readme[320];
    char zip[320];
    const char *log_path = logger_path();

    if (done || log_path == NULL || log_path[0] == '\0') {
        return;
    }
    sibling_path(log_path, "README.TXT", readme, sizeof(readme));
    sibling_path(log_path, "MELACS.ZIP", zip, sizeof(zip));
    if (!write_if_absent(readme, g_sd_pack_readme, g_sd_pack_readme_len)) {
        return;
    }
    if (!write_if_absent(zip, g_sd_pack_zip, g_sd_pack_zip_len)) {
        return;
    }
    done = 1;
}
