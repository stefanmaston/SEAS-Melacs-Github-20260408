#include "log_history.h"
#include "pic32_board.h"
#include "pin_map.h"
#include "sd_pack.h"

#include <string.h>

static int g_sd_ok;
static int g_block;
static uint32_t g_part;
static uint32_t g_fat_lba;
static uint32_t g_fat_sectors;
static uint32_t g_root_lba;
static uint32_t g_root_sectors;
static uint32_t g_data_lba;
static uint32_t g_root_cluster;
static uint32_t g_clusters;
static uint8_t g_spc;
static int g_fat32;
static int g_fats;
static int g_mounted;
static int g_have_file;
static int g_stop_dir;
static uint32_t g_dir_lba;
static int g_dir_off;
static uint32_t g_file_cluster;
static uint32_t g_file_size;
static uint8_t g_sec[512];
static uint8_t g_fat[512];

static uint8_t sd_command(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    int i;
    uint8_t reply;

    spi_xfer(0xFF);
    spi_xfer((uint8_t)(0x40u | cmd));
    spi_xfer((uint8_t)(arg >> 24));
    spi_xfer((uint8_t)(arg >> 16));
    spi_xfer((uint8_t)(arg >> 8));
    spi_xfer((uint8_t)arg);
    spi_xfer(crc);
    for (i = 0; i < 16; i++) {
        reply = spi_xfer(0xFF);
        if ((reply & 0x80u) == 0) {
            return reply;
        }
    }
    return 0xFF;
}

static int sd_wait_token(uint8_t token)
{
    uint32_t start = board_millis();

    while (board_millis() - start < 300u) {
        if (spi_xfer(0xFF) == token) {
            return 1;
        }
    }
    return 0;
}

static void sd_select(int on)
{
    PIN_CS_SD_LAT = on ? 0 : 1;
    spi_xfer(0xFF);
}

bool sd_read(uint32_t lba, uint8_t *dest)
{
    uint32_t addr = g_block ? lba : lba * 512u;
    int i;
    int ok = 0;

    memled_sd(1);
    sd_select(1);
    if (sd_command(17, addr, 0xFF) == 0 && sd_wait_token(0xFE)) {
        for (i = 0; i < 512; i++) {
            dest[i] = spi_xfer(0xFF);
        }
        spi_xfer(0xFF);
        spi_xfer(0xFF);
        ok = 1;
    }
    sd_select(0);
    memled_sd(0);
    return ok ? true : false;
}

static bool sd_write(uint32_t lba, const uint8_t *src)
{
    uint32_t addr = g_block ? lba : lba * 512u;
    uint32_t start;
    int i;
    uint8_t reply;
    int ok = 0;

    memled_sd(1);
    sd_select(1);
    if (sd_command(24, addr, 0xFF) != 0) {
        sd_select(0);
        memled_sd(0);
        return false;
    }
    spi_xfer(0xFF);
    spi_xfer(0xFE);
    for (i = 0; i < 512; i++) {
        spi_xfer(src[i]);
    }
    spi_xfer(0xFF);
    spi_xfer(0xFF);
    reply = spi_xfer(0xFF);
    if ((reply & 0x1Fu) == 0x05u) {
        start = board_millis();
        ok = 1;
        while (spi_xfer(0xFF) != 0xFF) {
            if (board_millis() - start > 500u) {
                ok = 0;
                break;
            }
        }
    }
    sd_select(0);
    memled_sd(0);
    return ok ? true : false;
}

bool sd_start(void)
{
    int i;
    uint8_t reply;
    uint32_t start;
    uint8_t ocr[4];

    g_sd_ok = 0;
    g_mounted = 0;
    g_have_file = 0;
    memled_sd(1);
    spi_hw_on(1);
    sd_select(0);
    for (i = 0; i < 10; i++) {
        spi_xfer(0xFF);
    }
    sd_select(1);
    reply = sd_command(0, 0, 0x95);
    if (reply != 0x01) {
        sd_select(0);
        spi_hw_on(0);
        memled_sd(0);
        return false;
    }
    reply = sd_command(8, 0x1AAu, 0x87);
    if (reply != 0x01) {
        sd_select(0);
        spi_hw_on(0);
        memled_sd(0);
        return false;
    }
    for (i = 0; i < 4; i++) {
        ocr[i] = spi_xfer(0xFF);
    }
    if (ocr[3] != 0xAA) {
        sd_select(0);
        spi_hw_on(0);
        memled_sd(0);
        return false;
    }
    start = board_millis();
    do {
        if (sd_command(55, 0, 0xFF) > 1) {
            sd_select(0);
            spi_hw_on(0);
            memled_sd(0);
            return false;
        }
        reply = sd_command(41, 0x40000000u, 0xFF);
        if (board_millis() - start > 1000u) {
            sd_select(0);
            spi_hw_on(0);
            memled_sd(0);
            return false;
        }
    } while (reply != 0);
    if (sd_command(58, 0, 0xFF) != 0) {
        sd_select(0);
        spi_hw_on(0);
        memled_sd(0);
        return false;
    }
    for (i = 0; i < 4; i++) {
        ocr[i] = spi_xfer(0xFF);
    }
    g_block = (ocr[0] & 0x40u) ? 1 : 0;
    if (!g_block && sd_command(16, 512, 0xFF) != 0) {
        sd_select(0);
        spi_hw_on(0);
        memled_sd(0);
        return false;
    }
    sd_select(0);
    spi_hw_on(0);
    memled_sd(0);
    g_sd_ok = 1;
    return true;
}

bool sd_ok(void)
{
    return g_mounted ? true : false;
}

static uint16_t ru16(const uint8_t *p)
{
    return (uint16_t)(p[0] | (p[1] << 8));
}

static uint32_t ru32(const uint8_t *p)
{
    return (uint32_t)ru16(p) | ((uint32_t)ru16(p + 2) << 16);
}

static uint32_t fat_eoc(void)
{
    return g_fat32 ? 0x0FFFFFF8u : 0xFFF8u;
}

static uint32_t cluster_lba(uint32_t cluster)
{
    return g_data_lba + (cluster - 2u) * g_spc;
}

static uint32_t fat_read(uint32_t cluster)
{
    uint32_t entries = g_fat32 ? 128u : 256u;
    uint32_t lba = g_fat_lba + cluster / entries;
    uint32_t index = cluster % entries;

    if (!sd_read(lba, g_fat)) {
        return 0xFFFFFFFFu;
    }
    if (g_fat32) {
        return ru32(g_fat + index * 4u) & 0x0FFFFFFFu;
    }
    return ru16(g_fat + index * 2u);
}

static bool fat_write_entry(uint32_t cluster, uint32_t value)
{
    uint32_t entries = g_fat32 ? 128u : 256u;
    uint32_t index_lba = cluster / entries;
    uint32_t index = cluster % entries;
    int copy;

    if (!sd_read(g_fat_lba + index_lba, g_fat)) {
        return false;
    }
    if (g_fat32) {
        uint8_t *p = g_fat + index * 4u;
        uint32_t old = ru32(p);
        value = (old & 0xF0000000u) | (value & 0x0FFFFFFFu);
        p[0] = (uint8_t)value;
        p[1] = (uint8_t)(value >> 8);
        p[2] = (uint8_t)(value >> 16);
        p[3] = (uint8_t)(value >> 24);
    } else {
        g_fat[index * 2u] = (uint8_t)value;
        g_fat[index * 2u + 1u] = (uint8_t)(value >> 8);
    }
    for (copy = 0; copy < g_fats; copy++) {
        if (!sd_write(g_fat_lba + (uint32_t)copy * g_fat_sectors + index_lba, g_fat)) {
            return false;
        }
    }
    return true;
}

static uint32_t fat_alloc(void)
{
    uint32_t entries = g_fat32 ? 128u : 256u;
    uint32_t lba;

    for (lba = 0; lba < g_fat_sectors; lba++) {
        uint32_t i;
        if (!sd_read(g_fat_lba + lba, g_fat)) {
            return 0;
        }
        for (i = 0; i < entries; i++) {
            uint32_t cluster = lba * entries + i;
            uint32_t value;
            if (cluster < 2 || cluster >= g_clusters) {
                continue;
            }
            value = g_fat32 ? (ru32(g_fat + i * 4u) & 0x0FFFFFFFu) : ru16(g_fat + i * 2u);
            if (value == 0) {
                if (!fat_write_entry(cluster, 0x0FFFFFFFu)) {
                    return 0;
                }
                return cluster;
            }
        }
    }
    return 0;
}

static void name_83(const char *path, uint8_t out[11])
{
    const char *base = path;
    const char *scan;
    int i = 0;

    for (scan = path; *scan; scan++) {
        if (*scan == '/' || *scan == '\\') {
            base = scan + 1;
        }
    }
    memset(out, ' ', 11);
    while (*base && *base != '.' && i < 8) {
        char c = *base++;
        if (c >= 'a' && c <= 'z') {
            c = (char)(c - 32);
        }
        out[i++] = (uint8_t)c;
    }
    if (*base == '.') {
        base++;
    }
    i = 8;
    while (*base && i < 11) {
        char c = *base++;
        if (c >= 'a' && c <= 'z') {
            c = (char)(c - 32);
        }
        out[i++] = (uint8_t)c;
    }
}

static bool dir_store(uint32_t lba, int off, const uint8_t name[11], uint32_t cluster, uint32_t size)
{
    uint8_t *ent;

    if (!sd_read(lba, g_sec)) {
        return false;
    }
    ent = g_sec + off;
    memset(ent, 0, 32);
    memcpy(ent, name, 11);
    ent[11] = 0x20;
    ent[20] = (uint8_t)(cluster >> 16);
    ent[21] = (uint8_t)(cluster >> 24);
    ent[26] = (uint8_t)cluster;
    ent[27] = (uint8_t)(cluster >> 8);
    ent[28] = (uint8_t)size;
    ent[29] = (uint8_t)(size >> 8);
    ent[30] = (uint8_t)(size >> 16);
    ent[31] = (uint8_t)(size >> 24);
    return sd_write(lba, g_sec);
}

static int entry_is_name(const uint8_t *ent, const uint8_t name[11])
{
    if (ent[0] == 0x00 || ent[0] == 0xE5 || ent[11] == 0x0F) {
        return 0;
    }
    if (ent[11] & 0x08u) {
        return 0;
    }
    return memcmp(ent, name, 11) == 0;
}

static bool consider_sector(uint32_t lba, const uint8_t name[11], int create, uint32_t *free_lba, int *free_off)
{
    int off;

    if (!sd_read(lba, g_sec)) {
        return false;
    }
    for (off = 0; off < 512; off += 32) {
        uint8_t *ent = g_sec + off;
        if (entry_is_name(ent, name)) {
            g_dir_lba = lba;
            g_dir_off = off;
            g_file_cluster = (uint32_t)ent[26] | ((uint32_t)ent[27] << 8) |
                             ((uint32_t)ent[20] << 16) | ((uint32_t)ent[21] << 24);
            g_file_size = ru32(ent + 28);
            g_have_file = 1;
            return true;
        }
        if (create && *free_off < 0 && (ent[0] == 0x00 || ent[0] == 0xE5)) {
            *free_lba = lba;
            *free_off = off;
        }
        if (ent[0] == 0x00) {
            g_stop_dir = 1;
            return true;
        }
    }
    return true;
}

static bool open_file(const char *path)
{
    uint8_t name[11];
    uint32_t free_lba = 0;
    int free_off = -1;
    uint32_t cluster;
    uint32_t guard;

    name_83(path, name);
    g_stop_dir = 0;
    if (!g_fat32) {
        uint32_t s;
        for (s = 0; s < g_root_sectors && !g_stop_dir; s++) {
            if (!consider_sector(g_root_lba + s, name, 1, &free_lba, &free_off)) {
                return false;
            }
            if (g_have_file) {
                return true;
            }
        }
    } else {
        cluster = g_root_cluster;
        for (guard = 0; guard < 64 && !g_stop_dir && cluster >= 2 && cluster < fat_eoc(); guard++) {
            uint32_t s;
            uint32_t next;
            for (s = 0; s < g_spc && !g_stop_dir; s++) {
                if (!consider_sector(cluster_lba(cluster) + s, name, 1, &free_lba, &free_off)) {
                    return false;
                }
                if (g_have_file) {
                    return true;
                }
            }
            next = fat_read(cluster);
            if (next >= fat_eoc()) {
                break;
            }
            cluster = next;
        }
    }
    if (free_off < 0) {
        return false;
    }
    if (!dir_store(free_lba, free_off, name, 0, 0)) {
        return false;
    }
    g_dir_lba = free_lba;
    g_dir_off = free_off;
    g_file_cluster = 0;
    g_file_size = 0;
    g_have_file = 1;
    return true;
}

static bool mount_fat(void)
{
    uint32_t total;
    uint16_t reserved;
    uint16_t root_entries;
    uint32_t data_sectors;

    if (!sd_read(0, g_sec)) {
        return false;
    }
    if (g_sec[510] != 0x55 || g_sec[511] != 0xAA) {
        return false;
    }
    if (g_sec[0] == 0xEB || g_sec[0] == 0xE9) {
        g_part = 0;
    } else {
        if (g_sec[450] == 0) {
            return false;
        }
        g_part = ru32(g_sec + 454);
    }
    if (!sd_read(g_part, g_sec)) {
        return false;
    }
    if (ru16(g_sec + 11) != 512 || g_sec[13] == 0) {
        return false;
    }
    g_spc = g_sec[13];
    reserved = ru16(g_sec + 14);
    g_fats = g_sec[16];
    if (g_fats < 1) {
        g_fats = 1;
    }
    root_entries = ru16(g_sec + 17);
    total = ru16(g_sec + 19);
    if (total == 0) {
        total = ru32(g_sec + 32);
    }
    g_fat_sectors = ru16(g_sec + 22);
    g_fat32 = 0;
    g_root_cluster = 0;
    if (g_fat_sectors == 0) {
        g_fat_sectors = ru32(g_sec + 36);
        g_root_cluster = ru32(g_sec + 44);
        g_fat32 = 1;
    }
    g_fat_lba = g_part + reserved;
    g_root_sectors = (uint32_t)((root_entries * 32u + 511u) / 512u);
    g_root_lba = g_fat_lba + (uint32_t)g_fats * g_fat_sectors;
    g_data_lba = g_root_lba + g_root_sectors;
    if (g_data_lba <= g_part || total <= (g_data_lba - g_part)) {
        return false;
    }
    data_sectors = total - (g_data_lba - g_part);
    g_clusters = data_sectors / g_spc;
    g_mounted = 1;
    g_have_file = 0;
    return true;
}

static uint32_t cluster_at(uint32_t pos, int alloc_end)
{
    uint32_t cluster = g_file_cluster;
    uint32_t step = pos / ((uint32_t)g_spc * 512u);
    uint32_t i;

    if (cluster < 2) {
        cluster = fat_alloc();
        if (cluster == 0) {
            return 0;
        }
        g_file_cluster = cluster;
        return cluster;
    }
    for (i = 0; i < step; i++) {
        uint32_t next = fat_read(cluster);
        if (next == 0xFFFFFFFFu) {
            return 0;
        }
        if (next < 2 || next >= fat_eoc()) {
            if (!alloc_end) {
                return 0;
            }
            next = fat_alloc();
            if (next == 0 || !fat_write_entry(cluster, next)) {
                return 0;
            }
        }
        cluster = next;
    }
    return cluster;
}

static bool update_size(void)
{
    uint8_t *ent;

    if (!sd_read(g_dir_lba, g_sec)) {
        return false;
    }
    ent = g_sec + g_dir_off;
    ent[20] = (uint8_t)(g_file_cluster >> 16);
    ent[21] = (uint8_t)(g_file_cluster >> 24);
    ent[26] = (uint8_t)g_file_cluster;
    ent[27] = (uint8_t)(g_file_cluster >> 8);
    ent[28] = (uint8_t)g_file_size;
    ent[29] = (uint8_t)(g_file_size >> 8);
    ent[30] = (uint8_t)(g_file_size >> 16);
    ent[31] = (uint8_t)(g_file_size >> 24);
    return sd_write(g_dir_lba, g_sec);
}

bool sd_append_line(const char *path, const char *text)
{
    uint32_t pos;
    const uint8_t *src;
    uint32_t left;

    if (!g_sd_ok) {
        return false;
    }
    spi_hw_on(0);
    if (!g_mounted && !mount_fat()) {
        spi_hw_on(0);
        g_sd_ok = 0;
        return false;
    }
    if (!g_have_file && !open_file(path != 0 ? path : "MELACS.CSV")) {
        spi_hw_on(0);
        return false;
    }
    pos = g_file_size;
    src = (const uint8_t *)text;
    left = (uint32_t)strlen(text);
    while (left > 0) {
        uint32_t cluster_bytes = (uint32_t)g_spc * 512u;
        uint32_t into = pos % cluster_bytes;
        uint32_t lba;
        uint32_t off;
        uint32_t chunk;
        uint32_t cluster = cluster_at(pos, 1);
        if (cluster < 2) {
            spi_hw_on(0);
            return false;
        }
        lba = cluster_lba(cluster) + into / 512u;
        off = into % 512u;
        chunk = 512u - off;
        if (chunk > left) {
            chunk = left;
        }
        if (!sd_read(lba, g_sec)) {
            spi_hw_on(0);
            return false;
        }
        memcpy(g_sec + off, src, chunk);
        if (!sd_write(lba, g_sec)) {
            spi_hw_on(0);
            return false;
        }
        src += chunk;
        left -= chunk;
        pos += chunk;
    }
    g_file_size = pos;
    if (!update_size()) {
        spi_hw_on(0);
        return false;
    }
    spi_hw_on(0);
    return true;
}

static void restore_file(int have, uint32_t cluster, uint32_t size, uint32_t lba, int off)
{
    g_have_file = have;
    g_file_cluster = cluster;
    g_file_size = size;
    g_dir_lba = lba;
    g_dir_off = off;
}

static bool sd_write_if_absent(const char *path, const void *data, uint32_t len)
{
    int saved_have;
    uint32_t saved_cluster;
    uint32_t saved_size;
    uint32_t saved_lba;
    int saved_off;
    const uint8_t *src;
    uint32_t left;
    uint32_t pos;
    int ok = 0;

    if (!g_sd_ok || path == 0 || data == 0) {
        return false;
    }
    spi_hw_on(0);
    if (!g_mounted && !mount_fat()) {
        spi_hw_on(0);
        g_sd_ok = 0;
        return false;
    }
    saved_have = g_have_file;
    saved_cluster = g_file_cluster;
    saved_size = g_file_size;
    saved_lba = g_dir_lba;
    saved_off = g_dir_off;
    g_have_file = 0;
    if (!open_file(path)) {
        restore_file(saved_have, saved_cluster, saved_size, saved_lba, saved_off);
        spi_hw_on(0);
        return false;
    }
    if (g_file_size > 0) {
        restore_file(saved_have, saved_cluster, saved_size, saved_lba, saved_off);
        spi_hw_on(0);
        return true;
    }
    pos = 0;
    src = (const uint8_t *)data;
    left = len;
    while (left > 0) {
        uint32_t cluster_bytes = (uint32_t)g_spc * 512u;
        uint32_t into = pos % cluster_bytes;
        uint32_t chunk;
        uint32_t cluster = cluster_at(pos, 1);
        uint32_t lba;
        uint32_t off;

        if (cluster < 2) {
            break;
        }
        lba = cluster_lba(cluster) + into / 512u;
        off = into % 512u;
        chunk = 512u - off;
        if (chunk > left) {
            chunk = left;
        }
        if (!sd_read(lba, g_sec)) {
            break;
        }
        memcpy(g_sec + off, src, chunk);
        if (!sd_write(lba, g_sec)) {
            break;
        }
        src += chunk;
        left -= chunk;
        pos += chunk;
    }
    if (left == 0) {
        g_file_size = pos;
        ok = update_size() ? 1 : 0;
    }
    restore_file(saved_have, saved_cluster, saved_size, saved_lba, saved_off);
    spi_hw_on(0);
    return ok == 1;
}

bool sd_seed_pack(void)
{
    if (!sd_write_if_absent("README.TXT", g_sd_pack_readme, g_sd_pack_readme_len)) {
        return false;
    }
    return sd_write_if_absent("MELACS.ZIP", g_sd_pack_zip, g_sd_pack_zip_len);
}

enum {
    HIST_SEEK = 1,
    HIST_READ = 2
};

static int g_hist_state;
static uint32_t g_hist_budget;
static uint32_t g_hist_off;
static uint32_t g_hist_end;
static uint32_t g_hist_cluster;
static uint32_t g_hist_base;
static int g_hist_skip;
static char g_hist_line[480];
static unsigned g_hist_len;
static int g_hist_drop;

static void hist_feed(const uint8_t *bytes, uint32_t count)
{
    uint32_t i;

    for (i = 0; i < count; i++) {
        char ch = (char)bytes[i];

        if (ch == '\r') {
            continue;
        }
        if (ch == '\n') {
            g_hist_line[g_hist_len] = '\0';
            if (!g_hist_skip && !g_hist_drop) {
                log_history_accept(g_hist_line);
            }
            g_hist_skip = 0;
            g_hist_drop = 0;
            g_hist_len = 0;
            continue;
        }
        if (g_hist_drop) {
            continue;
        }
        if (g_hist_len + 1u >= sizeof(g_hist_line)) {
            g_hist_drop = 1;
            g_hist_len = 0;
            continue;
        }
        g_hist_line[g_hist_len++] = ch;
    }
}

static void hist_place(uint32_t size)
{
    g_hist_end = size;
    g_hist_off = size > g_hist_budget ? size - g_hist_budget : 0;
    g_hist_skip = g_hist_off != 0;
    g_hist_base = 0;
    g_hist_cluster = g_file_cluster;
}

void sd_hist_start(uint32_t budget_bytes)
{
    g_hist_state = HIST_SEEK;
    g_hist_budget = budget_bytes;
    g_hist_len = 0;
    g_hist_drop = 0;
    g_hist_skip = 0;
    g_hist_cluster = 0;
    g_hist_base = 0;
    g_hist_off = 0;
    g_hist_end = 0;
    if (!g_mounted && !g_sd_ok) {
        log_history_fail();
        g_hist_state = 0;
        return;
    }
    if (g_have_file) {
        hist_place(g_file_size);
    }
}

void sd_hist_step(void)
{
    uint32_t cluster_bytes;
    uint32_t next;

    if (g_hist_state == 0) {
        return;
    }
    spi_hw_on(0);
    if (!g_mounted) {
        if (!g_sd_ok || !mount_fat()) {
            spi_hw_on(0);
            log_history_fail();
            g_hist_state = 0;
            return;
        }
    }
    if (!g_have_file) {
        if (!open_file("MELACS.CSV")) {
            spi_hw_on(0);
            log_history_fail();
            g_hist_state = 0;
            return;
        }
        hist_place(g_file_size);
    }
    if (g_file_cluster < 2 || g_hist_end == 0) {
        spi_hw_on(0);
        log_history_ready();
        g_hist_state = 0;
        return;
    }
    if (g_hist_cluster < 2) {
        g_hist_cluster = g_file_cluster;
        g_hist_base = 0;
    }
    cluster_bytes = (uint32_t)g_spc * 512u;
    if (cluster_bytes == 0) {
        spi_hw_on(0);
        log_history_fail();
        g_hist_state = 0;
        return;
    }
    if (g_hist_state == HIST_SEEK) {
        int steps = 0;

        while (steps < 8 && g_hist_off >= g_hist_base + cluster_bytes) {
            next = fat_read(g_hist_cluster);
            if (next < 2 || next >= fat_eoc()) {
                spi_hw_on(0);
                log_history_fail();
                g_hist_state = 0;
                return;
            }
            g_hist_cluster = next;
            g_hist_base += cluster_bytes;
            steps++;
        }
        if (g_hist_off < g_hist_base + cluster_bytes) {
            g_hist_state = HIST_READ;
        } else {
            spi_hw_on(0);
            return;
        }
    }
    if (g_hist_state == HIST_READ) {
        int sectors = 0;

        while (sectors < 4 && g_hist_off < g_hist_end) {
            uint32_t into = g_hist_off - g_hist_base;
            uint32_t skip = into % 512u;
            uint32_t count = 512u - skip;

            if (g_hist_off + count > g_hist_end) {
                count = g_hist_end - g_hist_off;
            }
            if (!sd_read(cluster_lba(g_hist_cluster) + into / 512u, g_sec)) {
                spi_hw_on(0);
                log_history_fail();
                g_hist_state = 0;
                return;
            }
            hist_feed(g_sec + skip, count);
            g_hist_off += count;
            sectors++;
            if (g_hist_off >= g_hist_base + cluster_bytes && g_hist_off < g_hist_end) {
                next = fat_read(g_hist_cluster);
                if (next < 2 || next >= fat_eoc()) {
                    spi_hw_on(0);
                    log_history_fail();
                    g_hist_state = 0;
                    return;
                }
                g_hist_cluster = next;
                g_hist_base += cluster_bytes;
            }
        }
    }
    if (g_hist_off >= g_hist_end) {
        log_history_ready();
        g_hist_state = 0;
    }
    spi_hw_on(0);
}
