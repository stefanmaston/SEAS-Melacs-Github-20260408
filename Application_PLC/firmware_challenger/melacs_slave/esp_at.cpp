#include "esp_at.h"

#include <ChallengerWiFi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wifi_config.h"

static bool blank(const char *s) {
    while (*s == ' ' || *s == '\t') {
        s++;
    }
    return *s == 0;
}

void EspAt::noteIp(const char *line) {
    const char *q = strchr(line, '"');
    if (!q) {
        return;
    }
    q++;
    const char *end = strchr(q, '"');
    if (!end || end == q || (size_t)(end - q) > 15) {
        return;
    }
    memcpy(ip_, q, (size_t)(end - q));
    ip_[end - q] = 0;
}

void EspAt::takeBin(uint8_t b) {
    if (binLink_ < 0 || binLink_ > 4) {
        binLeft_--;
        return;
    }
    Link &link = links_[binLink_];
    if (link.rxLen < sizeof link.rx) {
        link.rx[link.rxLen++] = b;
        link.lastByteMs = millis();
    } else {
        link.overflow = true;
    }
    binLeft_--;
    if (binLeft_ == 0) {
        if (link.overflow) {
            link.rxLen = 0;
            link.pending = 0;
            link.overflow = false;
        } else if (passivePull_) {
            if (link.pending >= (uint16_t)binGot_) {
                link.pending = (uint16_t)(link.pending - binGot_);
            } else {
                link.pending = 0;
            }
        }
        passivePull_ = false;
    }
}

void EspAt::handleLine(char *line) {
    if (blank(line)) {
        return;
    }
    if (strcmp(line, "OK") == 0) {
        okFlag_ = true;
        return;
    }
    if (strcmp(line, "ERROR") == 0 || strncmp(line, "ERROR", 5) == 0) {
        errFlag_ = true;
        if (err_[0] == 0) {
            snprintf(err_, sizeof err_, "%s", line);
        }
        return;
    }
    if (strcmp(line, "SEND OK") == 0) {
        sendOk_ = true;
        return;
    }
    if (strcmp(line, "SEND FAIL") == 0) {
        sendFail_ = true;
        return;
    }
    if (strstr(line, ":ip:") != nullptr) {
        noteIp(line);
        return;
    }
    if (strcmp(line, "WIFI DISCONNECT") == 0) {
        up_ = false;
        snprintf(err_, sizeof err_, "WIFI DISCONNECT");
        return;
    }
    int id = 0;
    int len = 0;
    if (sscanf(line, "+IPD,%d,%d", &id, &len) == 2 && id >= 0 && id <= 4 && len > 0) {
        uint32_t sum = (uint32_t)links_[id].pending + (uint32_t)len;
        links_[id].pending = sum > 60000 ? 60000 : (uint16_t)sum;
        return;
    }
    char word[16];
    if (sscanf(line, "%d,%15s", &id, word) == 2 && id >= 0 && id <= 4) {
        if (strcmp(word, "CLOSED") == 0) {
            links_[id].rxLen = 0;
            links_[id].pending = 0;
        }
        return;
    }
    if (strncmp(line, "+CWJAP:", 7) == 0 || strncmp(line, "busy", 4) == 0) {
        snprintf(err_, sizeof err_, "%s", line);
    }
}

void EspAt::feedByte(uint8_t b) {
    if (binLeft_ > 0) {
        takeBin(b);
        return;
    }
    if (waitPrompt_ && b == '>') {
        promptSeen_ = true;
        lineLen_ = 0;
        return;
    }
    if (b == '\r') {
        return;
    }
    if (b == '\n') {
        line_[lineLen_] = 0;
        handleLine(line_);
        lineLen_ = 0;
        return;
    }
    if (lineLen_ >= sizeof line_ - 1) {
        lineLen_ = 0;
        return;
    }
    line_[lineLen_++] = (char)b;
    line_[lineLen_] = 0;

    if (strncmp(line_, "+IPD,", 5) == 0 && strchr(line_, ':') != nullptr) {
        int id = 0;
        int len = 0;
        if (sscanf(line_, "+IPD,%d,%d:", &id, &len) == 2 && id >= 0 && id <= 4 && len > 0) {
            binLink_ = id;
            binLeft_ = len;
            binGot_ = len;
            passivePull_ = false;
        }
        lineLen_ = 0;
        return;
    }
    if (strncmp(line_, "+CIPRECVDATA:", 13) == 0 && strchr(line_, ',') != nullptr) {
        int got = atoi(line_ + 13);
        binLink_ = expectLink_;
        binGot_ = got;
        binLeft_ = got;
        passivePull_ = true;
        if (got == 0) {
            passivePull_ = false;
            if (expectLink_ >= 0 && expectLink_ <= 4) {
                links_[expectLink_].pending = 0;
            }
        }
        lineLen_ = 0;
    }
}

bool EspAt::cmd(const char *text, uint32_t timeoutMs) {
    while (ESP_SERIAL_PORT.available()) {
        feedByte((uint8_t)ESP_SERIAL_PORT.read());
    }
    okFlag_ = false;
    errFlag_ = false;
    ESP_SERIAL_PORT.print(text);
    ESP_SERIAL_PORT.print("\r\n");
    uint32_t start = millis();
    while ((uint32_t)(millis() - start) < timeoutMs) {
        while (ESP_SERIAL_PORT.available()) {
            feedByte((uint8_t)ESP_SERIAL_PORT.read());
        }
        if (okFlag_) {
            return true;
        }
        if (errFlag_) {
            return false;
        }
        delay(1);
    }
    snprintf(err_, sizeof err_, "timeout");
    return false;
}

bool EspAt::sendLink(int id, const uint8_t *data, uint16_t len) {
    char text[32];
    snprintf(text, sizeof text, "AT+CIPSEND=%d,%u", id, len);
    promptSeen_ = false;
    waitPrompt_ = true;
    sendOk_ = false;
    sendFail_ = false;
    ESP_SERIAL_PORT.print(text);
    ESP_SERIAL_PORT.print("\r\n");
    uint32_t start = millis();
    while (!promptSeen_ && (uint32_t)(millis() - start) < 1500) {
        while (ESP_SERIAL_PORT.available()) {
            feedByte((uint8_t)ESP_SERIAL_PORT.read());
        }
        delay(1);
    }
    waitPrompt_ = false;
    if (!promptSeen_) {
        snprintf(err_, sizeof err_, "CIPSEND inget prompt");
        return false;
    }
    ESP_SERIAL_PORT.write(data, len);
    start = millis();
    while (!sendOk_ && !sendFail_ && (uint32_t)(millis() - start) < 1500) {
        while (ESP_SERIAL_PORT.available()) {
            feedByte((uint8_t)ESP_SERIAL_PORT.read());
        }
        delay(1);
    }
    return sendOk_;
}

bool EspAt::pull(int id) {
    uint16_t n = links_[id].pending;
    if (n > 200) {
        n = 200;
    }
    if (n == 0 || links_[id].rxLen > 200) {
        return false;
    }
    char text[40];
    snprintf(text, sizeof text, "AT+CIPRECVDATA=%d,%u", id, n);
    expectLink_ = id;
    return cmd(text, 1000);
}

bool EspAt::frameReady(int id, uint16_t *frameLen) {
    Link &link = links_[id];
    if (link.rxLen >= 6) {
        uint32_t age = (uint32_t)(millis() - link.lastByteMs);
        uint16_t mbap = (uint16_t)((link.rx[4] << 8) | link.rx[5]);
        if (mbap < 2 || mbap > 254) {
            link.rxLen = 0;
            return false;
        }
        uint16_t total = (uint16_t)(6 + mbap);
        if (link.rxLen >= total) {
            *frameLen = total;
            return true;
        }
        if (age > 500) {
            link.rxLen = 0;
        }
    } else if (link.rxLen > 0 && (uint32_t)(millis() - link.lastByteMs) > 500) {
        link.rxLen = 0;
    }
    return false;
}

bool EspAt::bringUp(const char *ssid, const char *pass) {
    up_ = false;
    ap_ = false;
    ip_[0] = 0;
    err_[0] = 0;
    lineLen_ = 0;
    binLeft_ = 0;
    passivePull_ = false;
    waitPrompt_ = false;
    memset(links_, 0, sizeof links_);

    ESP_SERIAL_PORT.end();
    ESP_SERIAL_PORT.setFIFOSize(1024);
    ESP_SERIAL_PORT.begin(115200);
    delay(50);
    while (ESP_SERIAL_PORT.available()) {
        ESP_SERIAL_PORT.read();
    }

    bool alive = false;
    for (int i = 0; i < 3 && !alive; i++) {
        alive = cmd("AT", 400);
    }
    if (!alive) {
        Challenger2040WiFi.runReset();
        uint32_t start = millis();
        while ((uint32_t)(millis() - start) < 2000) {
            while (ESP_SERIAL_PORT.available()) {
                feedByte((uint8_t)ESP_SERIAL_PORT.read());
            }
            delay(10);
        }
        alive = cmd("AT", 1000);
    }
    if (!alive) {
        snprintf(err_, sizeof err_, "ESP-AT svarar inte");
        return false;
    }

    cmd("ATE0", 500);
    bool station = ssid != nullptr && ssid[0] != 0;
    if (!cmd(station ? "AT+CWMODE=1" : "AT+CWMODE=2", 2000)) {
        return false;
    }
    if (station) {
        char join[120];
        snprintf(join, sizeof join, "AT+CWJAP=\"%s\",\"%s\"", ssid, pass != nullptr ? pass : "");
        if (!cmd(join, 20000)) {
            return false;
        }
        for (int i = 0; i < 10 && ip_[0] == 0; i++) {
            cmd("AT+CIPSTA?", 800);
            delay(100);
        }
    } else {
        ap_ = true;
        char sap[80];
        snprintf(sap, sizeof sap, "AT+CWSAP=\"%s\",\"%s\",6,3", MELACS_AP_SSID, MELACS_AP_PASS);
        if (!cmd(sap, 5000)) {
            return false;
        }
        cmd("AT+CIPAP?", 800);
        if (ip_[0] == 0) {
            snprintf(ip_, sizeof ip_, "192.168.4.1");
        }
    }
    if (ip_[0] == 0) {
        snprintf(err_, sizeof err_, "ingen IP");
        return false;
    }
    if (!cmd("AT+CIPMUX=1", 1000)) {
        return false;
    }
    passive_ = cmd("AT+CIPRECVMODE=1", 1000);
    cmd("AT+CIPSERVER=0,1", 500);
    char server[32];
    snprintf(server, sizeof server, "AT+CIPSERVER=1,%d", MELACS_MODBUS_PORT);
    if (!cmd(server, 2000)) {
        snprintf(err_, sizeof err_, "CIPSERVER fel");
        return false;
    }
    up_ = true;
    return true;
}

void EspAt::service(MelacsImage *img, bool *request_handled) {
    while (ESP_SERIAL_PORT.available()) {
        feedByte((uint8_t)ESP_SERIAL_PORT.read());
    }
    if (!up_ || binLeft_ > 0 || waitPrompt_) {
        return;
    }
    for (int id = 0; id < 5; id++) {
        uint16_t frameLen = 0;
        if (frameReady(id, &frameLen)) {
            if (onRequest_ != nullptr) {
                onRequest_();
            }
            uint8_t rsp[260];
            size_t n = melacs_modbus_tcp(img, links_[id].rx, frameLen, rsp, sizeof rsp);
            if (n > 0) {
                *request_handled = true;
                if (!sendLink(id, rsp, (uint16_t)n)) {
                    char closeCmd[24];
                    snprintf(closeCmd, sizeof closeCmd, "AT+CIPCLOSE=%d", id);
                    cmd(closeCmd, 500);
                    links_[id].rxLen = 0;
                    links_[id].pending = 0;
                    return;
                }
            }
            uint16_t rest = (uint16_t)(links_[id].rxLen - frameLen);
            memmove(links_[id].rx, links_[id].rx + frameLen, rest);
            links_[id].rxLen = rest;
            return;
        }
    }
    if (!passive_) {
        return;
    }
    for (int id = 0; id < 5; id++) {
        if (links_[id].pending > 0 && links_[id].rxLen < 200) {
            pull(id);
            return;
        }
    }
}
