#include "pic32_board.h"

#include <xc.h>

void delay_us(uint32_t us)
{
    uint32_t start = _CP0_GET_COUNT();
    uint32_t ticks = us * 36u;

    while ((_CP0_GET_COUNT() - start) < ticks) {
    }
}

void delay_ms(uint32_t ms)
{
    while (ms > 0) {
        delay_us(1000);
        ms--;
    }
}

static void (*g_yield_hook)(void);
static int g_in_yield;

void board_set_yield(void (*hook)(void))
{
    g_yield_hook = hook;
}

void board_yield(void)
{
    if (g_yield_hook == 0 || g_in_yield) {
        return;
    }
    g_in_yield = 1;
    g_yield_hook();
    g_in_yield = 0;
}

/* Före tick_init räknas tiden från kärntimern, därefter från Timer1. */
uint32_t board_millis(void)
{
    static uint32_t last;
    static uint32_t ms;
    uint32_t now;
    uint32_t step;

    if (tick_running()) {
        return tick_millis();
    }
    now = _CP0_GET_COUNT();
    step = (now - last) / 36000u;

    if (step > 0) {
        ms += step;
        last += step * 36000u;
    }
    return ms;
}

void board_init(void)
{
    uint8_t mac[6];

    io_init();
    spi_bus_init();
    tick_init();
    (void)sd_start();
    if (enc_start(mac)) {
        net_init(mac);
    } else {
        net_init(0);
    }
}
