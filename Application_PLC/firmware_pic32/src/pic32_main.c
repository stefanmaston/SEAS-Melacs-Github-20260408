#include "pic32_board.h"
#include "plc_runtime.h"

int main(void)
{
    board_init();
    plc_runtime_init("MELACS.CSV");
    for (;;) {
        net_poll();
        plc_runtime_tick();
        memled_poll();
        delay_ms(10);
    }
    return 0;
}
