#include "pic32_board.h"
#include "plc_runtime.h"

/*
 * Schemaläggning med Timer1 som tidbas (pic32_tick.c):
 *
 *   varje varv   Ethernet/Modbus. Ingen fördröjning, så en fråga besvaras
 *                normalt inom bråkdelen av en millisekund.
 *   var 10 ms    PLC-svep: I/O, logger, SD, klocka och registerbild.
 *                Samma takt som tidigare, så logger och historik beter sig lika.
 *   1 kHz        Snabbfunktioner i Timer1-avbrottet (fast_ctrl.c).
 *
 * Under SD-kortets programmeringstid släpps bussen och Ethernet betjänas
 * via board_yield(), så loggningen inte stoppar Modbus.
 */

#define SCAN_PERIOD_MS 10u

static void net_service(void)
{
    net_poll();
}

int main(void)
{
    uint32_t next_scan;

    board_init();
    board_set_yield(net_service);
    plc_runtime_init("MELACS.CSV");
    next_scan = board_millis();

    for (;;) {
        uint32_t now;

        net_poll();

        now = board_millis();
        if ((int32_t)(now - next_scan) >= 0) {
            plc_runtime_tick();
            memled_poll();
            buzzer_poll();
            next_scan += SCAN_PERIOD_MS;
            /* Efter ett långt svep tas inte förlorade svep igen i en rusning. */
            if ((int32_t)(now - next_scan) > (int32_t)SCAN_PERIOD_MS) {
                next_scan = now + SCAN_PERIOD_MS;
            }
        }
    }
    return 0;
}
