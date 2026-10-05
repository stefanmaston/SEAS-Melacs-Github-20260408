#include "logger.h"
#include "modbus_tcp.h"
#include "plat_host.h"
#include "plc_runtime.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define LOG_PATH "build/melacs_log.csv"

static int g_fails;
static uint16_t g_mb_port = MELACS_MODBUS_PORT;

static void expect(int cond, const char *what)
{
    if (!cond) {
        fprintf(stderr, "FAIL: %s\n", what);
        g_fails++;
    }
}

static int mb_exchange(const uint8_t *pdu, int pdu_len, uint8_t *resp, int resp_max)
{
    int fd;
    struct sockaddr_in addr;
    struct timeval tv;
    uint8_t hdr[7];
    int length;
    int n;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        return -1;
    }
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(g_mb_port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        close(fd);
        return -1;
    }
    hdr[0] = 0;
    hdr[1] = 1;
    hdr[2] = 0;
    hdr[3] = 0;
    hdr[4] = (uint8_t)((pdu_len + 1) >> 8);
    hdr[5] = (uint8_t)((pdu_len + 1) & 0xff);
    hdr[6] = 1;
    if (send(fd, hdr, 7, 0) != 7 || send(fd, pdu, (size_t)pdu_len, 0) != pdu_len) {
        close(fd);
        return -1;
    }
    n = 0;
    while (n < 7) {
        ssize_t r = recv(fd, hdr + n, (size_t)(7 - n), 0);
        if (r <= 0) {
            close(fd);
            return -1;
        }
        n += (int)r;
    }
    length = ((hdr[4] << 8) | hdr[5]) - 1;
    if (length <= 0 || length > resp_max) {
        close(fd);
        return -1;
    }
    n = 0;
    while (n < length) {
        ssize_t r = recv(fd, resp + n, (size_t)(length - n), 0);
        if (r <= 0) {
            close(fd);
            return -1;
        }
        n += (int)r;
    }
    close(fd);
    return length;
}

static int read_holding(uint16_t addr, uint16_t count, uint16_t *out)
{
    uint8_t pdu[5];
    uint8_t resp[260];
    int n;
    uint16_t i;

    pdu[0] = 3;
    pdu[1] = (uint8_t)(addr >> 8);
    pdu[2] = (uint8_t)(addr & 0xff);
    pdu[3] = (uint8_t)(count >> 8);
    pdu[4] = (uint8_t)(count & 0xff);
    n = mb_exchange(pdu, 5, resp, (int)sizeof(resp));
    if (n < 2 || resp[0] != 3 || resp[1] != count * 2) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        out[i] = (uint16_t)((resp[2 + i * 2] << 8) | resp[3 + i * 2]);
    }
    return 0;
}

static int read_input(uint16_t addr, uint16_t *out)
{
    uint8_t pdu[5];
    uint8_t resp[16];
    int n;

    pdu[0] = 4;
    pdu[1] = (uint8_t)(addr >> 8);
    pdu[2] = (uint8_t)(addr & 0xff);
    pdu[3] = 0;
    pdu[4] = 1;
    n = mb_exchange(pdu, 5, resp, (int)sizeof(resp));
    if (n < 4 || resp[0] != 4) {
        return -1;
    }
    *out = (uint16_t)((resp[2] << 8) | resp[3]);
    return 0;
}

static int write_coil(uint16_t addr, int on)
{
    uint8_t pdu[5];
    uint8_t resp[8];
    int n;

    pdu[0] = 5;
    pdu[1] = (uint8_t)(addr >> 8);
    pdu[2] = (uint8_t)(addr & 0xff);
    pdu[3] = on ? 0xff : 0x00;
    pdu[4] = 0x00;
    n = mb_exchange(pdu, 5, resp, (int)sizeof(resp));
    return (n == 5 && resp[0] == 5) ? 0 : -1;
}

static int write_reg(uint16_t addr, uint16_t value)
{
    uint8_t pdu[5];
    uint8_t resp[8];
    int n;

    pdu[0] = 6;
    pdu[1] = (uint8_t)(addr >> 8);
    pdu[2] = (uint8_t)(addr & 0xff);
    pdu[3] = (uint8_t)(value >> 8);
    pdu[4] = (uint8_t)(value & 0xff);
    n = mb_exchange(pdu, 5, resp, (int)sizeof(resp));
    return (n == 5 && resp[0] == 6) ? 0 : -1;
}

static int write_clock(const uint16_t values[8])
{
    uint8_t pdu[6 + 16];
    uint8_t resp[8];
    int i;
    int n;

    pdu[0] = 16;
    pdu[1] = (uint8_t)(202 >> 8);
    pdu[2] = (uint8_t)(202 & 0xff);
    pdu[3] = 0;
    pdu[4] = 8;
    pdu[5] = 16;
    for (i = 0; i < 8; i++) {
        pdu[6 + i * 2] = (uint8_t)(values[i] >> 8);
        pdu[7 + i * 2] = (uint8_t)(values[i] & 0xff);
    }
    n = mb_exchange(pdu, (int)sizeof(pdu), resp, (int)sizeof(resp));
    return (n == 5 && resp[0] == 16) ? 0 : -1;
}

static int read_coil_on(uint16_t addr)
{
    uint8_t pdu[5];
    uint8_t resp[8];
    int n;

    pdu[0] = 1;
    pdu[1] = (uint8_t)(addr >> 8);
    pdu[2] = (uint8_t)(addr & 0xff);
    pdu[3] = 0;
    pdu[4] = 1;
    n = mb_exchange(pdu, 5, resp, (int)sizeof(resp));
    if (n < 3 || resp[0] != 1) {
        return -1;
    }
    return (resp[2] & 1) ? 1 : 0;
}

static const char *csv_field(const char *line, int index, char *buf, size_t n)
{
    int i = 0;

    while (*line && i < index) {
        if (*line == ',') {
            i++;
        }
        line++;
    }
    i = 0;
    while (*line && *line != ',' && *line != '\n' && (size_t)i + 1 < n) {
        buf[i++] = *line++;
    }
    buf[i] = '\0';
    return buf;
}

static int contains(const char *buf, size_t n, const char *needle)
{
    size_t m = strlen(needle);
    size_t i;

    if (m == 0 || n < m) {
        return 0;
    }
    for (i = 0; i + m <= n; i++) {
        if (memcmp(buf + i, needle, m) == 0) {
            return 1;
        }
    }
    return 0;
}

static int pack_ready(void)
{
    FILE *fp;
    char buf[65536];
    size_t n;

    fp = fopen("build/MELACS.ZIP", "rb");
    if (fp == NULL) {
        return 0;
    }
    n = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
    if (n < 2 || buf[0] != 'P' || buf[1] != 'K' || !contains(buf, n, "project.json")) {
        return 0;
    }
    fp = fopen("build/README.TXT", "rb");
    if (fp == NULL) {
        return 0;
    }
    n = fread(buf, 1, sizeof(buf) - 1, fp);
    fclose(fp);
    buf[n] = '\0';
    return strstr(buf, "OpenPLC") != NULL;
}

static int outputs_are_safe(const PlcOutputs *out)
{
    PlcOutputs safe;

    safe_outputs(&safe);
    return memcmp(out, &safe, sizeof(safe)) == 0;
}

static int run_tests(void)
{
    RtcClock start;
    uint16_t board = 0;
    uint16_t year = 0;
    uint16_t second = 0;
    uint16_t hour = 0;
    uint16_t clock_words[8];
    char field[64];
    const char *line;
    int i;

    memset(&start, 0, sizeof(start));
    start.year = 2026;
    start.month = 9;
    start.day = 27;
    start.hour = 21;
    start.minute = 0;
    start.second = 0;
    start.weekday = 0;

    unlink(LOG_PATH);
    unlink("build/README.TXT");
    unlink("build/MELACS.ZIP");
    plat_host_clock_step(&start);
    plc_runtime_init(LOG_PATH);
    g_mb_port = 1512;
    if (!modbus_tcp_start(g_mb_port)) {
        fprintf(stderr, "Kunde inte öppna Modbus-port %d\n", g_mb_port);
        return 1;
    }

    for (i = 0; i < 5; i++) {
        plc_runtime_tick();
    }
    expect(plc_status()->log_count == 0, "ingen rad före sex sampel");
    plc_runtime_tick();

    expect(pack_ready(), "hjälppaket bredvid loggen");
    expect(plc_status()->log_count == 1, "logger skriver medelvärde efter 6 s");
    expect(plc_status()->logger_ok, "logger_ok efter CSV");
    expect(!plc_status()->plc_loaded && !plc_status()->plc_running, "inget PLC-program");
    expect(outputs_are_safe(plc_outputs()), "utgångar i safe utan PLC");
    line = logger_last_line();
    expect(strncmp(line, "2026-09-27 21:00:05,", 20) == 0, "tidsstämpel i loggrad");
    expect(write_reg(220, 10) == 0, "be om tio minuter från SD-loggen");
    expect(read_input(500, &board) == 0 && board == 2, "SD-fönstret är klart");
    expect(read_input(501, &board) == 0 && board >= 1, "SD-fönstret innehåller raden");
    expect(read_input(510, &year) == 0 && year == 2026, "SD-radens år");
    expect(read_input(513, &hour) == 0 && hour == 21, "SD-radens timme");
    expect(strcmp(csv_field(line, 24, field, sizeof(field)), "0") == 0, "DIO4 är 0 i loggen");

    expect(read_input(13, &board) == 0 && board == 24, "ingångsregister AI13");
    expect(read_holding(202, 1, &year) == 0 && year == 2026, "holding visar år");

    expect(write_coil(16, 1) == 0, "skriv coil DIO4");
    plc_runtime_tick();
    expect(plc_status()->plc_loaded && plc_status()->plc_running, "PLC kör efter Modbus-skrivning");
    expect(plc_outputs()->dio_out[0] && !plc_outputs()->dio_out[1], "DIO4 följer coil");
    expect(plc_outputs()->ao[0] == 0 && plc_outputs()->ao[2] == 0, "övriga utgångar orörda");
    for (i = 0; i < 5; i++) {
        plc_runtime_tick();
    }
    line = logger_last_line();
    expect(strcmp(csv_field(line, 24, field, sizeof(field)), "1") == 0, "loggen visar DIO4 till");

    expect(write_reg(200, 1) == 0, "safe_mode");
    plc_runtime_tick();
    expect(plc_status()->plc_loaded && !plc_status()->plc_running, "safe_mode stoppar körning");
    expect(outputs_are_safe(plc_outputs()), "fysiska utgångar safe");
    expect(read_coil_on(16) == 1, "kommandot till DIO4 ligger kvar");

    clock_words[0] = 2026;
    clock_words[1] = 1;
    clock_words[2] = 2;
    clock_words[3] = 3;
    clock_words[4] = 4;
    clock_words[5] = 5;
    clock_words[6] = 6;
    clock_words[7] = 1;
    expect(write_clock(clock_words) == 0, "skriv klocka");
    plc_runtime_tick();
    expect(read_holding(205, 1, &hour) == 0 && hour == 3, "holding visar ny timme");
    expect(read_holding(207, 1, &second) == 0 && second == 5, "holding visar ny sekund");
    expect(read_holding(209, 1, &year) == 0 && year == 0, "rtc_set läses som 0");
    for (i = 0; i < 8 && strncmp(logger_last_line(), "2026-01-02 ", 11) != 0; i++) {
        plc_runtime_tick();
    }
    line = logger_last_line();
    expect(strncmp(line, "2026-01-02 03:04:", 17) == 0, "rtc_set uppdaterar klockan");

    expect(write_reg(210, 1) == 0, "begär kort signal");
    plc_runtime_tick();
    expect(plat_host_beep_count() == 1, "signalen tas emot även i safe");
    expect(read_holding(210, 1, &year) == 0 && year == 0, "signalregistret läses som 0");

    modbus_tcp_stop();
    if (g_fails != 0) {
        fprintf(stderr, "%d test fel\n", g_fails);
        return 1;
    }
    printf("host-test ok\n");
    return 0;
}

static int serve(void)
{
    plat_host_clock_wall();
    plc_runtime_init(LOG_PATH);
    if (!modbus_tcp_start(MELACS_MODBUS_PORT)) {
        fprintf(stderr, "Kunde inte öppna Modbus-port %d\n", MELACS_MODBUS_PORT);
        return 1;
    }
    printf("Modbus TCP port %d, slav 1. Logg: %s\n", MELACS_MODBUS_PORT, LOG_PATH);
    for (;;) {
        plc_runtime_tick();
        usleep(100000);
    }
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--serve") == 0) {
        return serve();
    }
    return run_tests();
}
