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

uint32_t board_millis(void)
{
    static uint32_t last;
    static uint32_t ms;
    uint32_t now = _CP0_GET_COUNT();
    uint32_t step = (now - last) / 36000u;

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
    (void)sd_start();
    if (enc_start(mac)) {
        net_init(mac);
    } else {
        net_init(0);
    }
}
