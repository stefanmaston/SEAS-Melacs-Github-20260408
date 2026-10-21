#ifndef FAST_CTRL_H
#define FAST_CTRL_H

/*
 * Snabbfunktioner som körs i 1 kHz-avbrottet på PIC32.
 *
 * Bara källor utan SPI: DIO0–DIO3 och den inbyggda ADC:n (AI10–AI15).
 * Bara utgångar utan läs-ändra-skriv-risk: PWM via OCxRS. Förreglingen
 * spärrar dessutom H-bryggorna via DIS-benet, som avbrottet sätter varje tick.
 *
 * Konfiguration och status ligger i Modbus-blocket 300–339.
 *
 * Holding:
 *   300        ilk_reset. Skriv 1 för att kvittera utlösta förreglingar. Läses som 0.
 *   301–304    ilk_cfg[i]: bit0–1 DIO-ingång 0–3, bit2 1=löser på hög nivå,
 *              bit3 spärrar H1, bit4 spärrar H2, bit15 aktiv.
 *   310+10c    pid[c].enable (0/1), c = 0 eller 1
 *   311+10c    pid[c].feedback: AI-index 0–5 (AI10–AI15)
 *   312+10c    pid[c].output: PWM 0=H1_AHI 1=H1_BHI 2=H2_AHI 3=H2_BHI
 *   313+10c    pid[c].setpoint i ADC-steg
 *   314+10c    pid[c].kp, int16 Q8.8 (256 = 1,0)
 *   315+10c    pid[c].ki, int16 Q8.8 per sekund
 *   316+10c    pid[c].kd, int16 Q8.8 sekunder
 *   317+10c    pid[c].period_ms 1–1000 (0 betyder 10)
 *   318+10c    pid[c].out_min
 *   319+10c    pid[c].out_max
 *
 * Input:
 *   300        bit0–3 utlösta förreglingar, bit8 H1 spärrad, bit9 H2 spärrad
 *   301        tickräknare, låga 16 bitar
 *   302        längsta avbrottstid i µs
 *   303        konfigurationsfel: bit c = pid[c] har ogiltig konfiguration
 *   310+10c    pid[c] utsignal
 *   311+10c    pid[c] senaste återkoppling
 *   312+10c    pid[c] reglerfel, int16
 */

#include <stdbool.h>
#include <stdint.h>

#define FAST_TICK_HZ 1000u
#define FAST_N_ILK 4
#define FAST_N_PID 2
#define FAST_N_PWM 4

#define FAST_REG_FIRST 300u
#define FAST_REG_LAST 339u

#define FAST_REG_ILK_RESET 300u
#define FAST_REG_ILK_CFG 301u
#define FAST_REG_PID 310u
#define FAST_REG_PID_STRIDE 10u

#define FAST_ILK_INPUT_MASK 0x0003u
#define FAST_ILK_TRIP_HIGH 0x0004u
#define FAST_ILK_BLOCK_H1 0x0008u
#define FAST_ILK_BLOCK_H2 0x0010u
#define FAST_ILK_ENABLE 0x8000u

typedef struct {
    bool dio_in[4];
    uint16_t ai[6];
} FastIn;

typedef struct {
    uint16_t pwm[FAST_N_PWM];
    uint8_t pwm_owned;   /* bit n: PWM-kanal n styrs av avbrottet */
    bool block[2];       /* H1, H2 spärrade av förregling */
} FastOut;

void fast_ctrl_init(void);

/* Huvudloopen talar om ifall PLC-utgångarna är släppta (master finns, safe_mode 0). */
void fast_ctrl_set_run(bool running);

/* Spärr från skyddsbilden. Modbus kan inte nollställa den. */
void fast_ctrl_set_guard(bool h1, bool h2);

/*
 * 1 kHz-avbrottet anropar note_time. Huvudloopen anropar sweep_kick varje svep.
 * Dröjer svepet mer än FAST_SWEEP_LATE_MS spärras båda bryggorna.
 */
#define FAST_SWEEP_LATE_MS 100u
void fast_ctrl_note_time(uint32_t now_ms);
void fast_ctrl_sweep_kick(uint32_t now_ms);

/* Anropas med FAST_TICK_HZ. Får inte använda SPI. */
void fast_ctrl_step(const FastIn *in, FastOut *out);

/* Senaste utsignal, för huvudloopens io_write. */
uint8_t fast_ctrl_owned_pwm(void);
bool fast_ctrl_blocked(int bridge);

/* Modbus. Returnerar true om adressen hör till blocket. */
bool fast_ctrl_is_reg(uint16_t addr);
bool fast_ctrl_writable(uint16_t addr);
bool fast_ctrl_write_reg(uint16_t addr, uint16_t value);
bool fast_ctrl_read_holding(uint16_t addr, uint16_t *value);
bool fast_ctrl_read_input(uint16_t addr, uint16_t *value);

/* Plattformen rapporterar tidsmätning från avbrottet. */
void fast_ctrl_note_isr_us(uint16_t us);

/* Skyddar konfiguration mot avbrottet. På PIC32 maskas Timer1, på host en mutex. */
void fast_lock(void);
void fast_unlock(void);

#endif
