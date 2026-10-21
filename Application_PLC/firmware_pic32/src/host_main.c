#define _DEFAULT_SOURCE
#include "logger.h"
#include "modbus_tcp.h"
#include "plat_host.h"
#include "plc_runtime.h"
#include "protect.h"
#include "register_image.h"

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

static int file_has(const char *path, const char *needle)
{
    FILE *fp;
    char buf[65536];
    size_t n;

    fp = fopen(path, "rb");
    if (fp == NULL) {
        return 0;
    }
    n = fread(buf, 1, sizeof(buf) - 1u, fp);
    fclose(fp);
    buf[n] = '\0';
    return strstr(buf, needle) != NULL;
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

static int write_reg(uint16_t addr, uint16_t value);

static int write_regs(uint16_t addr, uint16_t count, const uint16_t *values)
{
    uint8_t pdu[6 + 246];
    uint8_t resp[8];
    uint16_t i;
    int n;

    if (count == 0 || count > 123) {
        return -1;
    }
    pdu[0] = 16;
    pdu[1] = (uint8_t)(addr >> 8);
    pdu[2] = (uint8_t)(addr & 0xff);
    pdu[3] = (uint8_t)(count >> 8);
    pdu[4] = (uint8_t)(count & 0xff);
    pdu[5] = (uint8_t)(count * 2u);
    for (i = 0; i < count; i++) {
        pdu[6 + i * 2] = (uint8_t)(values[i] >> 8);
        pdu[7 + i * 2] = (uint8_t)(values[i] & 0xff);
    }
    n = mb_exchange(pdu, (int)(6 + count * 2), resp, (int)sizeof(resp));
    return (n == 5 && resp[0] == 16) ? 0 : -1;
}

static int commit_image(const uint8_t *img, uint16_t len)
{
    uint16_t off;

    if (write_reg(PROT_REG_CTRL, 1) != 0 || write_reg(PROT_REG_LEN, len) != 0) {
        return -1;
    }
    for (off = 0; off < len;) {
        uint16_t chunk = (uint16_t)(len - off);
        uint16_t words;
        uint16_t w;
        uint16_t regs[17];

        if (chunk > 32u) {
            chunk = 32u;
        }
        words = (uint16_t)((chunk + 1u) / 2u);
        regs[0] = off;
        for (w = 0; w < words; w++) {
            uint16_t pos = (uint16_t)(off + w * 2u);
            uint8_t hi = img[pos];
            uint8_t lo = (uint16_t)(pos + 1u) < len ? img[pos + 1u] : 0;
            regs[1u + w] = (uint16_t)(((uint16_t)hi << 8) | lo);
        }
        if (write_regs(PROT_REG_OFF, (uint16_t)(1u + words), regs) != 0) {
            return -1;
        }
        off = (uint16_t)(off + chunk);
    }
    return write_reg(PROT_REG_CTRL, 2);
}

static uint16_t end_image(uint8_t *dst)
{
    uint32_t crc;

    dst[0] = 'M';
    dst[1] = 'P';
    dst[2] = 'I';
    dst[3] = '1';
    dst[4] = 1;
    dst[5] = 0;
    dst[6] = 1;
    dst[7] = 0;
    dst[12] = PROT_OP_END;
    crc = protect_crc32(dst + 12, 1);
    dst[8] = (uint8_t)crc;
    dst[9] = (uint8_t)(crc >> 8);
    dst[10] = (uint8_t)(crc >> 16);
    dst[11] = (uint8_t)(crc >> 24);
    return 13;
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
    unlink("build/MELACS.BAK");
    unlink("build/MELACS.SAF");
    unlink("build/README.TXT");
    unlink("build/MELACS.ZIP");
    {
        FILE *torn = fopen(LOG_PATH, "wb");
        if (torn != NULL) {
            fputs("2020-01-01 00:00:00,intact\nTORN-TAIL", torn);
            fclose(torn);
        }
    }
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
    expect(file_has(LOG_PATH, "2020-01-01 00:00:00,intact\n"), "äldre rad ligger kvar");
    expect(!file_has(LOG_PATH, "TORN-TAIL"), "avbruten svans tas bort");
    expect(file_has("build/MELACS.BAK", "2026-09-27 21:00:05,"), "backup får första raden");
    expect(file_has("build/MELACS.SAF", ",1,0\n"), "start hamnar i säkerhetsfilen");
    {
        uint16_t seq = 0;
        uint16_t code = 0;
        uint16_t next = 0;
        expect(read_input(350, &seq) == 0 && seq != 0, "händelsen ligger i bufferten");
        expect(read_input(351, &code) == 0 && code == 1, "buffertens första kod är start");
        expect(write_reg(381, seq) == 0, "kvittera händelsen");
        expect(read_input(350, &next) == 0 && next != 0 && next != seq, "nästa händelse ligger kvar");
    }
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
    expect(plc_status()->plc_loaded && !plc_status()->plc_running,
           "saknad skyddsbild håller safe");
    expect(outputs_are_safe(plc_outputs()), "fysiska utgångar safe utan bild");
    {
        uint8_t image[16];
        expect(commit_image(image, end_image(image)) == 0, "tom skyddsbild");
    }
    plc_runtime_tick();
    expect(plc_status()->plc_loaded && plc_status()->plc_running, "PLC kör efter skyddsbild");
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
    expect(file_has(LOG_PATH, "2026-09-27 21:00:05,"), "csv behåller den äldre timmen");
    expect(file_has("build/MELACS.BAK", "2026-09-27 21:00:05,"), "backup behåller den äldre raden");
    expect(file_has("build/MELACS.BAK", "2026-01-02 03:04:"), "backup utökas efter en timme");

    expect(write_reg(210, 1) == 0, "begär kort signal");
    plc_runtime_tick();
    expect(plat_host_beep_count() == 1, "signalen tas emot även i safe");
    expect(read_holding(210, 1, &year) == 0 && year == 0, "signalregistret läses som 0");

    expect(write_reg(301, 0x8019u) == 0, "skriv förregling via Modbus");
    expect(read_holding(301, 1, &year) == 0 && year == 0x8019u, "förreglingen läses tillbaka");
    expect(write_reg(305, 1) != 0, "lucka i snabbblocket är inte skrivbar");
    expect(read_input(300, &year) == 0 && year == 0, "ingen förregling utlöst på host");

    expect(write_reg(200, 0) == 0, "släpp safe_mode");
    expect(write_coil(16, 1) == 0, "fräscha mastern");
    plc_runtime_tick();
    expect(plc_status()->plc_running, "kör med färsk master");
    for (i = 0; i < (int)MASTER_TIMEOUT_SCANS - 1; i++) {
        plc_runtime_tick();
    }
    expect(plc_status()->plc_running, "master lever inom timeout");
    plc_runtime_tick();
    expect(!plc_status()->plc_running, "utebliven master ger safe");
    expect(outputs_are_safe(plc_outputs()), "timeout lägger safe");

    {
        uint8_t image[16];
        uint16_t bad_len;
        bad_len = end_image(image);
        image[12] ^= 0xFFu;
        expect(write_reg(200, 0) == 0, "safe_mode av inför fel bild");
        expect(write_coil(16, 1) == 0, "master fräsch inför fel bild");
        expect(commit_image(image, bad_len) == 0, "felaktig bild skrivs");
        plc_runtime_tick();
        expect(!plc_status()->plc_running, "fel kontrollsumma håller safe");
        expect(outputs_are_safe(plc_outputs()), "fel bild ger safe_outputs");
    }
    {
        uint8_t body[8];
        uint8_t image[24];
        uint16_t n = 0;
        uint32_t crc;
        body[n++] = PROT_OP_LDC;
        body[n++] = 1;
        body[n++] = 0;
        body[n++] = PROT_OP_INHIBIT;
        body[n++] = (uint8_t)PROT_INH_H1;
        body[n++] = 0;
        body[n++] = PROT_OP_END;
        image[0] = 'M';
        image[1] = 'P';
        image[2] = 'I';
        image[3] = '1';
        image[4] = 1;
        image[5] = 0;
        image[6] = (uint8_t)n;
        image[7] = 0;
        memcpy(image + 12, body, n);
        crc = protect_crc32(body, n);
        image[8] = (uint8_t)crc;
        image[9] = (uint8_t)(crc >> 8);
        image[10] = (uint8_t)(crc >> 16);
        image[11] = (uint8_t)(crc >> 24);
        expect(commit_image(image, (uint16_t)(12u + n)) == 0, "spärrbild");
        expect(write_reg(200, 0) == 0, "safe_mode av för spärrprov");
        expect(write_coil(16, 1) == 0, "DIO4 på under spärr");
        expect(write_coil(40, 0) == 0, "kommando släpper H1");
        plc_runtime_tick();
        expect(plc_status()->plc_running, "styrningen kör under skyddsbilden");
        expect(plc_outputs()->dio_out[0], "omarkerad utgång får vara på");
        expect(plc_outputs()->h1_dis, "skyddsbilden håller H1 av");
        expect(write_reg(301, 0) == 0, "driftförregling nollställs");
        plc_runtime_tick();
        expect(plc_outputs()->h1_dis, "nollställd förregling släpper inte H1");
    }
    expect(file_has("build/MELACS.SAF", ",3,0\n"), "saknad bild loggas");
    expect(file_has("build/MELACS.SAF", ",2,0\n"), "giltig bild loggas");
    expect(file_has("build/MELACS.SAF", ",4,0\n"), "fel bild loggas");
    expect(file_has("build/MELACS.SAF", ",5,0\n"), "tappad master loggas");
    expect(file_has("build/MELACS.SAF", ",9,1\n"), "spärren loggas");

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
