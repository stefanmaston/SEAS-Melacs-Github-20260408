#include "pic32_board.h"
#include "modbus_pdu.h"

#include <string.h>

#define ETH_IP 0x0800u
#define ETH_ARP 0x0806u
#define TCP_PORT 502u

static const uint8_t g_ip[4] = {192, 168, 1, 160};
static uint8_t g_mac[6];
static int g_ready;

enum { TCP_LISTEN = 0, TCP_SYN = 1, TCP_OPEN = 2, TCP_LAST_ACK = 3 };

static int g_tcp = TCP_LISTEN;
static uint32_t g_syn_ms;
static uint32_t g_ann_ms;
static int g_link_up;
static uint32_t g_link_down_ms;
static uint32_t g_quiet_ms;
static int g_syn_retx;
static uint8_t g_peer_mac[6];
static uint8_t g_peer_ip[4];
static uint16_t g_peer_port;
static uint32_t g_snd;
static uint32_t g_rcv;
static uint8_t g_acc[320];
static int g_acc_len;
static uint8_t g_retx_pkt[560];
static int g_retx_total;
static int g_retx_left;
static int g_retx_on;
static uint32_t g_retx_ms;
static uint32_t g_retx_end;

static uint16_t rd16(const uint8_t *p)
{
    return (uint16_t)((p[0] << 8) | p[1]);
}

static uint32_t rd32(const uint8_t *p)
{
    return ((uint32_t)rd16(p) << 16) | rd16(p + 2);
}

static void wr16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)(v >> 8);
    p[1] = (uint8_t)v;
}

static void wr32(uint8_t *p, uint32_t v)
{
    wr16(p, (uint16_t)(v >> 16));
    wr16(p + 2, (uint16_t)v);
}

static uint16_t checksum(const uint8_t *data, int len, uint32_t sum)
{
    while (len > 1) {
        sum += rd16(data);
        data += 2;
        len -= 2;
    }
    if (len) {
        sum += (uint16_t)data[0] << 8;
    }
    while (sum >> 16) {
        sum = (sum & 0xFFFFu) + (sum >> 16);
    }
    return (uint16_t)~sum;
}

static void eth_send(const uint8_t *dst, uint16_t type, const uint8_t *payload, int len)
{
    uint8_t frame[600];

    if (len < 0 || len + 14 > (int)sizeof(frame)) {
        return;
    }
    memcpy(frame, dst, 6);
    memcpy(frame + 6, g_mac, 6);
    wr16(frame + 12, type);
    memcpy(frame + 14, payload, (size_t)len);
    if (14 + len < 60) {
        memset(frame + 14 + len, 0, (size_t)(60 - (14 + len)));
        len = 46;
    }
    (void)enc_tx(frame, 14 + len);
}

static void arp_announce(void)
{
    uint8_t pkt[28];
    uint8_t bcast[6];

    memset(pkt, 0, sizeof(pkt));
    memset(bcast, 0xFF, sizeof(bcast));
    pkt[1] = 1;
    pkt[2] = 0x08;
    pkt[4] = 6;
    pkt[5] = 4;
    pkt[7] = 2;
    memcpy(pkt + 8, g_mac, 6);
    memcpy(pkt + 14, g_ip, 4);
    memcpy(pkt + 18, g_mac, 6);
    memcpy(pkt + 24, g_ip, 4);
    eth_send(bcast, ETH_ARP, pkt, 28);
}

static void arp_reply(const uint8_t *frame)
{
    uint8_t pkt[28];

    pkt[0] = 0;
    pkt[1] = 1;
    pkt[2] = 0x08;
    pkt[3] = 0;
    pkt[4] = 6;
    pkt[5] = 4;
    pkt[6] = 0;
    pkt[7] = 2;
    memcpy(pkt + 8, g_mac, 6);
    memcpy(pkt + 14, g_ip, 4);
    memcpy(pkt + 18, frame + 6, 6);
    memcpy(pkt + 24, frame + 28, 4);
    eth_send(frame + 6, ETH_ARP, pkt, 28);
}

static void icmp_reply(const uint8_t *ip, int ip_len)
{
    uint8_t pkt[540];
    int icmp_len;
    uint16_t sum;

    if (ip_len < 20 || ip[9] != 1 || ip[20] != 8) {
        return;
    }
    icmp_len = rd16(ip + 2) - 20;
    if (icmp_len < 8 || icmp_len + 20 > (int)sizeof(pkt)) {
        return;
    }
    memcpy(pkt, ip, (size_t)(20 + icmp_len));
    memcpy(pkt + 12, g_ip, 4);
    memcpy(pkt + 16, ip + 12, 4);
    pkt[8] = 64;
    pkt[10] = 0;
    pkt[11] = 0;
    sum = checksum(pkt, 20, 0);
    wr16(pkt + 10, sum);
    pkt[20] = 0;
    pkt[22] = 0;
    pkt[23] = 0;
    sum = checksum(pkt + 20, icmp_len, 0);
    wr16(pkt + 22, sum);
    eth_send(g_peer_mac, ETH_IP, pkt, 20 + icmp_len);
}

static void remember_peer(const uint8_t *frame, const uint8_t *ip)
{
    memcpy(g_peer_mac, frame + 6, 6);
    memcpy(g_peer_ip, ip + 12, 4);
}

static void tcp_send(uint8_t flags, const uint8_t *payload, int plen)
{
    uint8_t pkt[560];
    int hdr = (flags & 0x02u) ? 24 : 20;
    int total = 20 + hdr + plen;
    uint32_t sum;

    if (plen < 0 || total > (int)sizeof(pkt)) {
        return;
    }
    memset(pkt, 0, (size_t)total);
    pkt[0] = 0x45;
    wr16(pkt + 2, (uint16_t)total);
    pkt[8] = 64;
    pkt[9] = 6;
    memcpy(pkt + 12, g_ip, 4);
    memcpy(pkt + 16, g_peer_ip, 4);
    wr16(pkt + 10, checksum(pkt, 20, 0));
    wr16(pkt + 20, TCP_PORT);
    wr16(pkt + 22, g_peer_port);
    wr32(pkt + 24, g_snd);
    wr32(pkt + 28, g_rcv);
    pkt[32] = (uint8_t)((hdr / 4) << 4);
    pkt[33] = flags;
    wr16(pkt + 34, 1024);
    if (flags & 0x02u) {
        pkt[40] = 2;
        pkt[41] = 4;
        wr16(pkt + 42, 536);
    }
    if (plen > 0) {
        memcpy(pkt + 20 + hdr, payload, (size_t)plen);
    }
    sum = rd16(g_ip) + rd16(g_ip + 2);
    sum += rd16(g_peer_ip) + rd16(g_peer_ip + 2);
    sum += 6u + (uint32_t)(hdr + plen);
    wr16(pkt + 36, checksum(pkt + 20, hdr + plen, sum));
    eth_send(g_peer_mac, ETH_IP, pkt, total);
    if (flags & 0x02u) {
        g_snd++;
    }
    if (flags & 0x01u) {
        g_snd++;
    }
    g_snd += (uint32_t)plen;
    if ((plen > 0 || (flags & 0x01u)) && (flags & 0x02u) == 0 && total <= (int)sizeof(g_retx_pkt)) {
        memcpy(g_retx_pkt, pkt, (size_t)total);
        g_retx_total = total;
        g_retx_end = g_snd;
        g_retx_ms = board_millis();
        g_retx_left = 3;
        g_retx_on = 1;
    }
}

static void tcp_reset(void)
{
    g_tcp = TCP_LISTEN;
    g_acc_len = 0;
    g_retx_on = 0;
    g_syn_retx = 0;
}

static int same_session(const uint8_t *ip, uint16_t port)
{
    return memcmp(g_peer_ip, ip + 12, 4) == 0 && g_peer_port == port;
}

static int ack_covers(uint32_t ack)
{
    return (ack - g_retx_end) < 0x80000000u;
}

/* RST till en annan part, utan att rubba den session som är igång. */
static void tcp_rst_stranger(const uint8_t *frame, const uint8_t *ip, uint16_t port,
                             uint32_t seq, uint32_t ack_no, int seglen)
{
    uint8_t mac[6];
    uint8_t pip[4];
    uint16_t pport;
    uint32_t snd;
    uint32_t rcv;

    memcpy(mac, g_peer_mac, 6);
    memcpy(pip, g_peer_ip, 4);
    pport = g_peer_port;
    snd = g_snd;
    rcv = g_rcv;
    memcpy(g_peer_mac, frame + 6, 6);
    memcpy(g_peer_ip, ip + 12, 4);
    g_peer_port = port;
    g_snd = ack_no;
    g_rcv = seq + (uint32_t)seglen;
    tcp_send(0x14, 0, 0);
    memcpy(g_peer_mac, mac, 6);
    memcpy(g_peer_ip, pip, 4);
    g_peer_port = pport;
    g_snd = snd;
    g_rcv = rcv;
}

static void tcp_consume(void)
{
    while (g_acc_len >= 7) {
        int mb_len = (g_acc[4] << 8) | g_acc[5];
        int need;
        uint8_t pdu_out[260];
        uint8_t reply[280];
        int out_len;

        if (mb_len < 2 || mb_len > 254) {
            tcp_send(0x04, 0, 0);
            tcp_reset();
            return;
        }
        need = 6 + mb_len;
        if (g_acc_len < need) {
            return;
        }
        out_len = modbus_pdu_handle(g_acc + 7, mb_len - 1, pdu_out);
        if (out_len > 0) {
            reply[0] = g_acc[0];
            reply[1] = g_acc[1];
            reply[2] = 0;
            reply[3] = 0;
            reply[4] = (uint8_t)((out_len + 1) >> 8);
            reply[5] = (uint8_t)((out_len + 1) & 0xFF);
            reply[6] = g_acc[6];
            memcpy(reply + 7, pdu_out, (size_t)out_len);
            tcp_send(0x18, reply, 7 + out_len);
        } else {
            tcp_send(0x10, 0, 0);
        }
        memmove(g_acc, g_acc + need, (size_t)(g_acc_len - need));
        g_acc_len -= need;
    }
}

static void tcp_on_packet(const uint8_t *frame, const uint8_t *ip, int ip_len)
{
    const uint8_t *tcp;
    int tcp_off;
    int tcp_len;
    int hdr;
    int plen;
    uint16_t dest;
    uint16_t sport;
    uint8_t flags;
    uint32_t seq;
    uint32_t ack;
    int seglen;

    tcp_off = (ip[0] & 0x0Fu) * 4;
    if (tcp_off < 20 || ip_len < tcp_off + 20) {
        return;
    }
    tcp = ip + tcp_off;
    tcp_len = ip_len - tcp_off;
    dest = rd16(tcp + 2);
    if (dest != TCP_PORT) {
        return;
    }
    hdr = ((tcp[12] >> 4) & 0x0Fu) * 4;
    if (hdr < 20 || tcp_len < hdr) {
        return;
    }
    plen = tcp_len - hdr;
    flags = tcp[13];
    seq = rd32(tcp + 4);
    ack = rd32(tcp + 8);
    sport = rd16(tcp);
    seglen = plen;
    if (flags & 0x02u) {
        seglen++;
    }
    if (flags & 0x01u) {
        seglen++;
    }

    if (g_tcp != TCP_LISTEN && same_session(ip, sport)) {
        memcpy(g_peer_mac, frame + 6, 6);
    } else if (flags & 0x02u) {
        if (g_tcp != TCP_LISTEN) {
            tcp_send(0x04, 0, 0);
            tcp_reset();
        }
        remember_peer(frame, ip);
        g_peer_port = sport;
        g_snd = board_millis() * 1000u + 1u;
        g_rcv = seq + 1u;
        g_acc_len = 0;
        g_tcp = TCP_SYN;
        g_syn_ms = board_millis();
        g_syn_retx = 0;
        tcp_send(0x12, 0, 0);
        return;
    } else {
        if ((flags & 0x04u) == 0 && (seglen > 0 || (flags & 0x10u))) {
            tcp_rst_stranger(frame, ip, sport, seq, (flags & 0x10u) ? ack : 0, seglen);
        }
        return;
    }

    if (flags & 0x04u) {
        tcp_reset();
        return;
    }
    if (g_tcp == TCP_SYN && (flags & 0x10u) && ack == g_snd) {
        g_tcp = TCP_OPEN;
        g_rcv = seq;
    }
    if ((flags & 0x10u) && g_retx_on && ack_covers(ack)) {
        g_retx_on = 0;
    }
    if (g_tcp == TCP_LAST_ACK) {
        if (!g_retx_on) {
            tcp_reset();
        }
        return;
    }
    if (g_tcp != TCP_OPEN) {
        return;
    }
    if (plen > 0) {
        if (seq != g_rcv) {
            tcp_send(0x10, 0, 0);
            return;
        }
        if (g_acc_len + plen > (int)sizeof(g_acc)) {
            tcp_send(0x04, 0, 0);
            tcp_reset();
            return;
        }
        memcpy(g_acc + g_acc_len, tcp + hdr, (size_t)plen);
        g_acc_len += plen;
        g_rcv += (uint32_t)plen;
        tcp_consume();
        if (g_tcp == TCP_OPEN && g_acc_len > 0 && g_acc_len < 7) {
            tcp_send(0x10, 0, 0);
        }
    }
    if ((flags & 0x01u) && g_tcp == TCP_OPEN) {
        g_rcv += 1u;
        tcp_send(0x11, 0, 0);
        g_tcp = TCP_LAST_ACK;
    }
}

static void on_ip(const uint8_t *frame, int frame_len)
{
    const uint8_t *ip;
    int total;
    int ip_len;

    if (frame_len < 34) {
        return;
    }
    ip = frame + 14;
    if ((ip[0] >> 4) != 4) {
        return;
    }
    ip_len = (ip[0] & 0x0Fu) * 4;
    total = rd16(ip + 2);
    if (ip_len < 20 || total < ip_len || 14 + total > frame_len) {
        return;
    }
    if (memcmp(ip + 16, g_ip, 4) != 0) {
        return;
    }
    if (ip[9] == 1) {
        remember_peer(frame, ip);
        icmp_reply(ip, total);
        return;
    }
    if (ip[9] == 6) {
        tcp_on_packet(frame, ip, total);
    }
}

static void on_frame(const uint8_t *frame, int len)
{
    uint16_t type;

    if (len < 14) {
        return;
    }
    type = rd16(frame + 12);
    if (type == ETH_ARP && len >= 42 && rd16(frame + 20) == 1 && memcmp(frame + 38, g_ip, 4) == 0) {
        arp_reply(frame);
        return;
    }
    if (type == ETH_IP) {
        on_ip(frame, len);
    }
}

void net_init(const uint8_t mac[6])
{
    g_ready = 0;
    g_tcp = TCP_LISTEN;
    g_acc_len = 0;
    g_retx_on = 0;
    g_link_up = 0;
    g_link_down_ms = 0;
    g_quiet_ms = board_millis();
    if (mac == 0) {
        return;
    }
    memcpy(g_mac, mac, 6);
    g_ready = enc_ok();
}

/* Länk borta i 3 s, eller inga mottagna ramar på 10 s, startar om kretsen. */
static void heal_link(void)
{
    uint32_t now = board_millis();
    int link;

    if (!enc_ok()) {
        g_ready = 0;
        return;
    }
    link = enc_link() ? 1 : 0;
    if (link) {
        if (!g_link_up) {
            g_ann_ms = now - 1000u;
            g_quiet_ms = now;
        }
        g_link_up = 1;
        g_link_down_ms = 0;
        if ((now - g_quiet_ms) >= 10000u) {
            g_ready = 0;
            g_quiet_ms = now;
        }
        return;
    }
    g_quiet_ms = now;
    g_link_up = 0;
    if (g_link_down_ms == 0) {
        g_link_down_ms = now;
    } else if ((now - g_link_down_ms) >= 3000u) {
        g_ready = 0;
        g_link_down_ms = now;
    }
}

void net_poll(void)
{
    uint8_t frame[576];
    int len;
    int guard;

    if (g_ready && !enc_ok()) {
        g_ready = 0;
    }
    if (!g_ready) {
        static uint32_t last;
        uint8_t mac[6];

        if (board_millis() - last < 500u) {
            return;
        }
        last = board_millis();
        if (enc_start(mac)) {
            net_init(mac);
        }
        return;
    }
    spi_hw_on(0);
    enc_apply_duplex();
    for (guard = 0; guard < 4; guard++) {
        if (!enc_rx(frame, &len, (int)sizeof(frame))) {
            break;
        }
        on_frame(frame, len);
    }
    if (enc_take_rx()) {
        g_quiet_ms = board_millis();
        if ((board_millis() - g_ann_ms) >= 200u) {
            g_ann_ms = board_millis();
            arp_announce();
        }
    }
    if (g_retx_on && (uint32_t)(board_millis() - g_retx_ms) >= 200u) {
        if (g_retx_left <= 0) {
            g_retx_on = 0;
            tcp_send(0x04, 0, 0);
            tcp_reset();
        } else {
            eth_send(g_peer_mac, ETH_IP, g_retx_pkt, g_retx_total);
            g_retx_left--;
            g_retx_ms = board_millis();
        }
    }
    if (g_tcp == TCP_SYN && (board_millis() - g_syn_ms) > 250u) {
        if (g_syn_retx == 0) {
            g_snd--;
            tcp_send(0x12, 0, 0);
            g_syn_retx = 1;
            g_syn_ms = board_millis();
        } else if ((board_millis() - g_syn_ms) > 1000u) {
            tcp_reset();
        }
    }
    heal_link();
    if (g_ready && enc_link() && (board_millis() - g_ann_ms) >= 1000u) {
        g_ann_ms = board_millis();
        arp_announce();
    }
}

bool net_up(void)
{
    return g_ready && enc_link();
}
