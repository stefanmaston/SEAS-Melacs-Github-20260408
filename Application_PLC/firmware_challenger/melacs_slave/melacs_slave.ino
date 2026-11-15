#include <Arduino.h>
#include <EEPROM.h>

#include "esp_at.h"
#include "modbus_slave.h"
#include "wifi_config.h"

static const uint8_t kInPin[4] = {D5, D6, D9, D10};
static const uint8_t kOutPin[4] = {D11, D12, D13, A4};
static const uint8_t kAiPin[4] = {A0, A1, A2, A3};
static const uint8_t kAoPin[3] = {D0, D1, A5};

static EspAt esp;
static MelacsImage img;
static bool masterSeen = false;
static uint32_t lastMaster = 0;
static uint32_t lastLog = 0;
static uint32_t lastWifiTry = 0;
static bool useSta = false;
static char staSsid[33];
static char staPass[65];
static char usbLine[96];
static uint8_t usbLen = 0;
static bool applied = false;
static bool lastSafe = true;
static uint8_t lastDo[4];
static uint16_t lastAo[3];

static bool masterFresh() {
    return masterSeen && (uint32_t)(millis() - lastMaster) <= MELACS_MASTER_TIMEOUT_MS;
}

static bool outputsSafe() {
    return !esp.up() || img.holding[MELACS_HOLD_SAFE] != 0 || !masterFresh();
}

static void loadWifi() {
    useSta = false;
    staSsid[0] = 0;
    staPass[0] = 0;
    if (EEPROM.read(0) == 'M' && EEPROM.read(1) == 'W') {
        for (int i = 0; i < 32; i++) {
            staSsid[i] = (char)EEPROM.read(2 + i);
        }
        staSsid[32] = 0;
        for (int i = 0; i < 64; i++) {
            staPass[i] = (char)EEPROM.read(35 + i);
        }
        staPass[64] = 0;
        if (staSsid[0] != 0) {
            useSta = true;
            return;
        }
    }
    if (MELACS_WIFI_SSID[0] != 0) {
        strncpy(staSsid, MELACS_WIFI_SSID, sizeof staSsid - 1);
        strncpy(staPass, MELACS_WIFI_PASS, sizeof staPass - 1);
        useSta = true;
    }
}

static void saveWifi(const char *ssid, const char *pass) {
    EEPROM.write(0, 'M');
    EEPROM.write(1, 'W');
    for (int i = 0; i < 33; i++) {
        char c = (i < 32) ? ssid[i] : 0;
        EEPROM.write(2 + i, (uint8_t)c);
        if (c == 0) {
            for (int j = i + 1; j < 33; j++) {
                EEPROM.write(2 + j, 0);
            }
            break;
        }
    }
    for (int i = 0; i < 65; i++) {
        char c = (i < 64 && pass != nullptr) ? pass[i] : 0;
        EEPROM.write(35 + i, (uint8_t)c);
        if (c == 0) {
            for (int j = i + 1; j < 65; j++) {
                EEPROM.write(35 + j, 0);
            }
            break;
        }
    }
    EEPROM.commit();
}

static void clearWifi() {
    EEPROM.write(0, 0);
    EEPROM.write(1, 0);
    EEPROM.commit();
    useSta = false;
    staSsid[0] = 0;
    staPass[0] = 0;
}

static bool credentialsOk(const char *text) {
    return text != nullptr && strchr(text, '"') == nullptr && strchr(text, ',') == nullptr &&
           strchr(text, '\\') == nullptr;
}

static void publishStatus() {
    bool safe = outputsSafe();
    img.discrete[MELACS_DI_SD_OK] = 0;
    img.discrete[MELACS_DI_LOGGER_OK] = 0;
    img.discrete[MELACS_DI_PLC_LOADED] = esp.up() ? 1 : 0;
    img.discrete[MELACS_DI_PLC_RUNNING] = safe ? 0 : 1;
    if (!esp.up()) {
        img.input_reg[MELACS_IR_ERROR] = MELACS_ERR_WIFI;
    } else if (img.holding[MELACS_HOLD_SAFE] != 0) {
        img.input_reg[MELACS_IR_ERROR] = MELACS_ERR_SAFE;
    } else if (!masterFresh()) {
        img.input_reg[MELACS_IR_ERROR] = MELACS_ERR_TIMEOUT;
    } else {
        img.input_reg[MELACS_IR_ERROR] = MELACS_ERR_OK;
    }
}

static void noteMaster() {
    masterSeen = true;
    lastMaster = millis();
    publishStatus();
}

static void sampleInputs() {
    for (int i = 0; i < 4; i++) {
        uint16_t raw = (uint16_t)analogRead(kAiPin[i]);
        img.input_reg[i] = raw;
        img.input_reg[10 + i] = (uint16_t)((uint32_t)raw * 3300u / 4095u);
        img.discrete[i] = digitalRead(kInPin[i]) ? 1 : 0;
    }
    float temp = analogReadTemp();
    if (temp < 0) {
        temp = 0;
    }
    if (temp > 200) {
        temp = 200;
    }
    img.input_reg[MELACS_IR_TBOARD] = (uint16_t)(temp + 0.5f);
    publishStatus();
}

static void applyOutputs() {
    bool safe = outputsSafe();
    bool changed = !applied || safe != lastSafe;
    uint8_t dout[4];
    uint16_t aout[3];
    for (int i = 0; i < 4; i++) {
        dout[i] = safe ? 0 : img.coils[MELACS_COIL_DIO4 + i];
        if (dout[i] != lastDo[i]) {
            changed = true;
        }
    }
    for (int i = 0; i < 3; i++) {
        aout[i] = safe ? 0 : img.holding[MELACS_HOLD_AO0 + i];
        if (aout[i] != lastAo[i]) {
            changed = true;
        }
    }
    if (!changed) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        digitalWrite(kOutPin[i], dout[i] ? HIGH : LOW);
        lastDo[i] = dout[i];
    }
    for (int i = 0; i < 3; i++) {
        analogWrite(kAoPin[i], aout[i]);
        lastAo[i] = aout[i];
    }
    lastSafe = safe;
    applied = true;
}

static void printStatus() {
    bool safe = outputsSafe();
    Serial.print(esp.apMode() ? "AP " : "STA ");
    Serial.print(esp.up() ? esp.ip() : "ner");
    Serial.print(":");
    Serial.print(MELACS_MODBUS_PORT);
    Serial.print(" slav ");
    Serial.print(MELACS_SLAVE_ID);
    Serial.print(safe ? " safe=1" : " safe=0");
    Serial.print(" fel=");
    Serial.print(img.input_reg[MELACS_IR_ERROR]);
    Serial.print(" AD=");
    for (int i = 0; i < 4; i++) {
        Serial.print(img.input_reg[i]);
        if (i < 3) {
            Serial.print(",");
        }
    }
    Serial.print(" DIO=");
    for (int i = 0; i < 4; i++) {
        Serial.print(img.discrete[i]);
    }
    Serial.print(" ut=");
    for (int i = 0; i < 4; i++) {
        Serial.print(lastDo[i]);
    }
    if (!esp.up() && esp.lastError()[0]) {
        Serial.print(" (");
        Serial.print(esp.lastError());
        Serial.print(")");
    }
    Serial.println();
}

static void startRadio() {
    Serial.println(useSta ? "ansluter WiFi" : "startar eget WiFi");
    bool ok = esp.bringUp(useSta ? staSsid : "", useSta ? staPass : "");
    applied = false;
    if (!ok) {
        Serial.println(esp.lastError());
        return;
    }
    printStatus();
    if (esp.apMode()) {
        Serial.print("nat ");
        Serial.print(MELACS_AP_SSID);
        Serial.print(" losen ");
        Serial.println(MELACS_AP_PASS);
    }
}

static void handleUsb() {
    while (Serial.available()) {
        char c = (char)Serial.read();
        if (c == '\r') {
            continue;
        }
        if (c != '\n') {
            if (usbLen < sizeof usbLine - 1) {
                usbLine[usbLen++] = c;
            }
            continue;
        }
        usbLine[usbLen] = 0;
        usbLen = 0;
        if (strcmp(usbLine, "status") == 0) {
            printStatus();
        } else if (strcmp(usbLine, "ap") == 0) {
            clearWifi();
            startRadio();
        } else if (strncmp(usbLine, "wifi ", 5) == 0) {
            char *ssid = usbLine + 5;
            char *pass = strchr(ssid, ' ');
            if (pass == nullptr || pass == ssid) {
                Serial.println("wifi <ssid> <losen>");
                continue;
            }
            *pass = 0;
            pass++;
            if (!credentialsOk(ssid) || !credentialsOk(pass) || strlen(ssid) > 32 || strlen(pass) > 63) {
                Serial.println("ogiltigt namn eller losen");
                continue;
            }
            strncpy(staSsid, ssid, sizeof staSsid - 1);
            staSsid[sizeof staSsid - 1] = 0;
            strncpy(staPass, pass, sizeof staPass - 1);
            staPass[sizeof staPass - 1] = 0;
            useSta = true;
            saveWifi(staSsid, staPass);
            startRadio();
        }
    }
}

void setup() {
    analogReadResolution(12);
    analogWriteResolution(16);
    analogWriteFreq(1000);
    for (int i = 0; i < 4; i++) {
        pinMode(kOutPin[i], OUTPUT);
        digitalWrite(kOutPin[i], LOW);
        pinMode(kInPin[i], INPUT_PULLUP);
    }
    for (int i = 0; i < 3; i++) {
        pinMode(kAoPin[i], OUTPUT);
        analogWrite(kAoPin[i], 0);
    }
    for (int i = 0; i < 3; i++) {
        digitalWrite(D13, HIGH);
        delay(80);
        digitalWrite(D13, LOW);
        delay(80);
    }

    Serial.begin(115200);
    uint32_t wait = millis();
    while (!Serial && (uint32_t)(millis() - wait) < 2000) {
        delay(10);
    }
    EEPROM.begin(128);
    memset(&img, 0, sizeof img);
    loadWifi();
    Serial.println("Melacs Challenger RP2350, Modbus TCP slav");
    esp.setOnRequest(noteMaster);
    startRadio();
    lastWifiTry = millis();
    lastLog = millis();
}

void loop() {
    sampleInputs();
    bool got = false;
    esp.service(&img, &got);
    if (got) {
        masterSeen = true;
        lastMaster = millis();
    }
    applyOutputs();
    handleUsb();
    if (!esp.up() && (uint32_t)(millis() - lastWifiTry) > 10000) {
        lastWifiTry = millis();
        startRadio();
    }
    if ((uint32_t)(millis() - lastLog) > 2000) {
        lastLog = millis();
        printStatus();
    }
}
