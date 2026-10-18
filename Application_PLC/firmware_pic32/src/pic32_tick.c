#include "fast_ctrl.h"
#include "pic32_board.h"

#include <sys/attribs.h>
#include <xc.h>

/*
 * Timer1 ger tidbasen: 1 kHz, prioritet 4.
 * PBCLK 36 MHz, förskalare 1:8 -> 4,5 MHz, PR1 = 4499.
 *
 * Avbrottet räknar millisekunder och kör snabbfunktionerna.
 * Det rör aldrig SPI-bussen, så det krockar inte med SD, RTC, AD eller Ethernet.
 */

#define TICK_PR1 (36000000u / 8u / FAST_TICK_HZ - 1u)
#define CORE_TICKS_PER_US 36u

static volatile uint32_t g_ms;
static volatile int g_started;

void tick_init(void)
{
    T1CON = 0;
    TMR1 = 0;
    PR1 = TICK_PR1;
    T1CONbits.TCKPS = 1; /* 1:8 */

    IPC1bits.T1IP = 4;
    IPC1bits.T1IS = 0;
    IFS0CLR = _IFS0_T1IF_MASK;
    IEC0SET = _IEC0_T1IE_MASK;

    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
    T1CONbits.ON = 1;
    g_started = 1;
}

uint32_t tick_millis(void)
{
    return g_ms;
}

int tick_running(void)
{
    return g_started;
}

/* Anropas bara från huvudloopen. Räknaren gör att låsen kan nästlas. */
static unsigned g_lock_depth;

void fast_lock(void)
{
    IEC0CLR = _IEC0_T1IE_MASK;
    g_lock_depth++;
}

void fast_unlock(void)
{
    if (g_lock_depth > 0 && --g_lock_depth == 0) {
        IEC0SET = _IEC0_T1IE_MASK;
    }
}

void __ISR(_TIMER_1_VECTOR, IPL4SOFT) tick_isr(void)
{
    uint32_t start = _CP0_GET_COUNT();
    FastIn in;
    FastOut out;
    uint32_t spent;

    IFS0CLR = _IFS0_T1IF_MASK;
    g_ms++;

    io_fast_read(&in);
    fast_ctrl_step(&in, &out);
    io_fast_apply(&out);

    spent = (_CP0_GET_COUNT() - start) / CORE_TICKS_PER_US;
    fast_ctrl_note_isr_us(spent > 0xFFFFu ? 0xFFFFu : (uint16_t)spent);
}
