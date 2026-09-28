#include "modbus_tcp.h"

#include "modbus_pdu.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

static volatile int g_run;
static int g_listen = -1;
static pthread_t g_thread;
static int g_started;

static int read_full(int fd, uint8_t *buf, int n)
{
    int got = 0;

    while (got < n) {
        ssize_t r = recv(fd, buf + got, (size_t)(n - got), 0);
        if (r <= 0) {
            return -1;
        }
        got += (int)r;
    }
    return 0;
}

static int write_full(int fd, const uint8_t *buf, int n)
{
    int sent = 0;

    while (sent < n) {
        ssize_t r = send(fd, buf + sent, (size_t)(n - sent), 0);
        if (r <= 0) {
            return -1;
        }
        sent += (int)r;
    }
    return 0;
}

static void serve_client(int fd)
{
    uint8_t mbap[7];
    uint8_t pdu[260];
    uint8_t out_pdu[260];
    uint8_t frame[280];

    while (g_run) {
        int pdu_len;
        int out_len;
        int length;

        if (read_full(fd, mbap, 7) != 0) {
            return;
        }
        length = (mbap[4] << 8) | mbap[5];
        if (length < 2 || length > 254) {
            return;
        }
        pdu_len = length - 1;
        if (read_full(fd, pdu, pdu_len) != 0) {
            return;
        }
        out_len = modbus_pdu_handle(pdu, pdu_len, out_pdu);
        if (out_len <= 0) {
            return;
        }
        frame[0] = mbap[0];
        frame[1] = mbap[1];
        frame[2] = 0;
        frame[3] = 0;
        frame[4] = (uint8_t)((out_len + 1) >> 8);
        frame[5] = (uint8_t)((out_len + 1) & 0xff);
        frame[6] = mbap[6];
        memcpy(frame + 7, out_pdu, (size_t)out_len);
        if (write_full(fd, frame, 7 + out_len) != 0) {
            return;
        }
    }
}

static void *thread_main(void *arg)
{
    (void)arg;
    while (g_run) {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int fd = accept(g_listen, (struct sockaddr *)&peer, &len);

        if (fd < 0) {
            if (!g_run) {
                break;
            }
            continue;
        }
        serve_client(fd);
        close(fd);
    }
    return NULL;
}

bool modbus_tcp_start(uint16_t port)
{
    struct sockaddr_in addr;
    int on = 1;
    struct timeval tv;

    g_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (g_listen < 0) {
        return false;
    }
    setsockopt(g_listen, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(g_listen, (struct sockaddr *)&addr, sizeof(addr)) != 0
        || listen(g_listen, 2) != 0) {
        close(g_listen);
        g_listen = -1;
        return false;
    }
    tv.tv_sec = 0;
    tv.tv_usec = 200000;
    setsockopt(g_listen, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    g_run = 1;
    if (pthread_create(&g_thread, NULL, thread_main, NULL) != 0) {
        close(g_listen);
        g_listen = -1;
        g_run = 0;
        return false;
    }
    g_started = 1;
    return true;
}

void modbus_tcp_stop(void)
{
    g_run = 0;
    if (g_listen >= 0) {
        shutdown(g_listen, SHUT_RDWR);
        close(g_listen);
        g_listen = -1;
    }
    if (g_started) {
        pthread_join(g_thread, NULL);
        g_started = 0;
    }
}
