#include <stdio.h>
#include <string.h>

#include "melacs_slave/modbus_slave.h"

static int fails;

static void expect(int cond, const char *name) {
    if (!cond) {
        printf("FAIL %s\n", name);
        fails++;
    }
}

static void test_discrete(void) {
    MelacsImage img;
    memset(&img, 0, sizeof img);
    img.discrete[0] = 1;
    img.discrete[2] = 1;
    img.discrete[3] = 1;
    uint8_t req[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x02, 0x00, 0x00, 0x00, 0x04};
    uint8_t rsp[32];
    size_t n = melacs_modbus_tcp(&img, req, sizeof req, rsp, sizeof rsp);
    expect(n == 10, "fc2 length");
    expect(rsp[7] == 0x02 && rsp[8] == 1 && rsp[9] == 0x0D, "fc2 bits");
}

static void test_input_reg(void) {
    MelacsImage img;
    memset(&img, 0, sizeof img);
    img.input_reg[0] = 0x1234;
    uint8_t req[] = {0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x01, 0x04, 0x00, 0x00, 0x00, 0x01};
    uint8_t rsp[32];
    size_t n = melacs_modbus_tcp(&img, req, sizeof req, rsp, sizeof rsp);
    expect(n == 11, "fc4 length");
    expect(rsp[0] == 0x00 && rsp[1] == 0x07, "fc4 trans");
    expect(rsp[9] == 0x12 && rsp[10] == 0x34, "fc4 value");
}

static void test_coils_and_holding(void) {
    MelacsImage img;
    memset(&img, 0, sizeof img);
    uint8_t write[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x01, 0x0F, 0x00, 0x10, 0x00, 0x04, 0x01, 0x0F};
    uint8_t rsp[32];
    size_t n = melacs_modbus_tcp(&img, write, sizeof write, rsp, sizeof rsp);
    expect(n == 12, "fc15 length");
    expect(img.coils[16] && img.coils[17] && img.coils[18] && img.coils[19], "fc15 coils");

    uint8_t read[] = {0x00, 0x02, 0x00, 0x00, 0x00, 0x06, 0x01, 0x01, 0x00, 0x10, 0x00, 0x04};
    n = melacs_modbus_tcp(&img, read, sizeof read, rsp, sizeof rsp);
    expect(n == 10 && rsp[9] == 0x0F, "fc1 readback");

    uint8_t hold[] = {0x00, 0x03, 0x00, 0x00, 0x00, 0x09, 0x01, 0x10, 0x00, 0xC8, 0x00, 0x01, 0x02, 0x00, 0x01};
    n = melacs_modbus_tcp(&img, hold, sizeof hold, rsp, sizeof rsp);
    expect(n == 12 && img.holding[200] == 1, "fc16 safe");

    uint8_t one[] = {0x00, 0x04, 0x00, 0x00, 0x00, 0x06, 0x01, 0x06, 0x00, 0x64, 0xAB, 0xCD};
    n = melacs_modbus_tcp(&img, one, sizeof one, rsp, sizeof rsp);
    expect(n == 12 && img.holding[100] == 0xABCD, "fc6 ao0");
}

static void test_reject(void) {
    MelacsImage img;
    memset(&img, 0, sizeof img);
    uint8_t badfc[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x63, 0x00, 0x00, 0x00, 0x01};
    uint8_t rsp[32];
    size_t n = melacs_modbus_tcp(&img, badfc, sizeof badfc, rsp, sizeof rsp);
    expect(n == 9 && rsp[7] == (0x63 | 0x80) && rsp[8] == 1, "illegal function");

    uint8_t shortf[] = {0x00, 0x01, 0x00, 0x00};
    n = melacs_modbus_tcp(&img, shortf, sizeof shortf, rsp, sizeof rsp);
    expect(n == 0, "short frame");

    uint8_t zero[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x00, 0xC8, 0x00, 0x00};
    n = melacs_modbus_tcp(&img, zero, sizeof zero, rsp, sizeof rsp);
    expect(n == 9 && rsp[8] == 3, "qty zero");
}

int main(void) {
    test_discrete();
    test_input_reg();
    test_coils_and_holding();
    test_reject();
    if (fails) {
        printf("%d failed\n", fails);
        return 1;
    }
    printf("modbus ok\n");
    return 0;
}
