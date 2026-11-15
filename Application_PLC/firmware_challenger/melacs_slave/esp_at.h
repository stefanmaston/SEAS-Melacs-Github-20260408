#pragma once

#include <Arduino.h>

#include "modbus_slave.h"

class EspAt {
public:
    using OnRequest = void (*)();

    bool bringUp(const char *ssid, const char *pass);
    void service(MelacsImage *img, bool *request_handled);
    void setOnRequest(OnRequest fn) { onRequest_ = fn; }
    bool up() const { return up_; }
    bool apMode() const { return ap_; }
    const char *ip() const { return ip_; }
    const char *lastError() const { return err_; }

private:
    struct Link {
        uint8_t rx[260];
        uint16_t rxLen;
        uint16_t pending;
        uint32_t lastByteMs;
        bool overflow;
    };

    bool cmd(const char *text, uint32_t timeoutMs);
    bool sendLink(int id, const uint8_t *data, uint16_t len);
    bool pull(int id);
    void feedByte(uint8_t b);
    void handleLine(char *line);
    void takeBin(uint8_t b);
    bool frameReady(int id, uint16_t *frameLen);
    void noteIp(const char *line);

    Link links_[5];
    char line_[160];
    uint8_t lineLen_;
    char ip_[16];
    char err_[80];
    int binLink_;
    int binLeft_;
    int binGot_;
    int expectLink_;
    bool passivePull_;
    bool waitPrompt_;
    bool promptSeen_;
    bool okFlag_;
    bool errFlag_;
    bool sendOk_;
    bool sendFail_;
    bool up_;
    bool ap_;
    bool passive_;
    OnRequest onRequest_ = nullptr;
};
