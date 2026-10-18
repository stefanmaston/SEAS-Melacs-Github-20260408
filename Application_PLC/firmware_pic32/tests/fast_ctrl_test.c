/* Enhetstest för fast_ctrl.c. Körs med: make unit-test */

#include "fast_ctrl.h"
#include "register_image.h"

#include <stdio.h>
#include <string.h>

static int g_fails;
static int g_checks;

static void expect(int cond, const char *what)
{
    g_checks++;
    if (!cond) {
        fprintf(stderr, "FAIL: %s\n", what);
        g_fails++;
    }
}

static void wr(uint16_t addr, uint16_t value)
{
    fast_lock();
    expect(fast_ctrl_write_reg(addr, value), "adressen hör till blocket");
    fast_unlock();
}

static uint16_t rd_in(uint16_t addr)
{
    uint16_t v = 0xDEAD;
    expect(fast_ctrl_read_input(addr, &v), "input i blocket");
    return v;
}

static void run(FastIn *in, FastOut *out, int ticks)
{
    int i;
    for (i = 0; i < ticks; i++) {
        fast_ctrl_step(in, out);
    }
}

static uint16_t pid_reg(int c, int field)
{
    return (uint16_t)(FAST_REG_PID + c * FAST_REG_PID_STRIDE + field);
}

static void test_interlock(void)
{
    FastIn in;
    FastOut out;

    fast_ctrl_init();
    memset(&in, 0, sizeof(in));

    /* Förregling 0: DIO2 hög spärrar H1. */
    wr(FAST_REG_ILK_CFG, FAST_ILK_ENABLE | FAST_ILK_TRIP_HIGH | FAST_ILK_BLOCK_H1 | 2u);
    run(&in, &out, 1);
    expect(!out.block[0] && !out.block[1], "ingen spärr när DIO2 är låg");

    in.dio_in[2] = true;
    run(&in, &out, 1);
    expect(out.block[0] && !out.block[1], "DIO2 hög spärrar bara H1");
    expect(fast_ctrl_blocked(0) && !fast_ctrl_blocked(1), "huvudloopen ser spärren");
    expect(rd_in(300) == (0x01u | 0x100u), "status: förregling 0 och H1 spärrad");

    in.dio_in[2] = false;
    run(&in, &out, 5);
    expect(out.block[0], "spärren är låst efter att ingången gått tillbaka");

    in.dio_in[2] = true;
    wr(FAST_REG_ILK_RESET, 1);
    run(&in, &out, 1);
    expect(out.block[0], "kvittering släpper inte medan ingången är aktiv");

    in.dio_in[2] = false;
    wr(FAST_REG_ILK_RESET, 1);
    run(&in, &out, 1);
    expect(!out.block[0], "kvittering släpper när ingången är tillbaka");
    expect(rd_in(300) == 0, "status nollad efter kvittering");

    /* Aktiv låg: DIO0 låg spärrar båda bryggorna. */
    wr(FAST_REG_ILK_CFG + 1, FAST_ILK_ENABLE | FAST_ILK_BLOCK_H1 | FAST_ILK_BLOCK_H2 | 0u);
    in.dio_in[0] = true;
    run(&in, &out, 1);
    expect(!out.block[0] && !out.block[1], "aktiv låg: hög nivå är normalt");
    in.dio_in[0] = false;
    run(&in, &out, 1);
    expect(out.block[0] && out.block[1], "aktiv låg: låg nivå spärrar båda");

    /* Avaktiverad förregling släpper sin spärr. */
    wr(FAST_REG_ILK_CFG + 1, 0);
    run(&in, &out, 1);
    expect(!out.block[0] && !out.block[1], "avstängd förregling spärrar inte");
}

static void setup_pid(int c, uint16_t fb, uint16_t outp, uint16_t sp,
                      int16_t kp, int16_t ki, int16_t kd, uint16_t period,
                      uint16_t lo, uint16_t hi)
{
    fast_lock();
    fast_ctrl_write_reg(pid_reg(c, 1), fb);
    fast_ctrl_write_reg(pid_reg(c, 2), outp);
    fast_ctrl_write_reg(pid_reg(c, 3), sp);
    fast_ctrl_write_reg(pid_reg(c, 4), (uint16_t)kp);
    fast_ctrl_write_reg(pid_reg(c, 5), (uint16_t)ki);
    fast_ctrl_write_reg(pid_reg(c, 6), (uint16_t)kd);
    fast_ctrl_write_reg(pid_reg(c, 7), period);
    fast_ctrl_write_reg(pid_reg(c, 8), lo);
    fast_ctrl_write_reg(pid_reg(c, 9), hi);
    fast_ctrl_write_reg(pid_reg(c, 0), 1);
    fast_unlock();
}

static void test_pid_p(void)
{
    FastIn in;
    FastOut out;

    fast_ctrl_init();
    memset(&in, 0, sizeof(in));
    /* AI10 som återkoppling, H1_AHI som utgång, kp = 10,0. */
    setup_pid(0, 0, 0, 500, 10 * 256, 0, 0, 1, 0, 65535);
    in.ai[0] = 400;

    fast_ctrl_set_run(false);
    run(&in, &out, 3);
    expect(out.pwm_owned == 0x01u, "PID äger H1_AHI även i vila");
    expect(out.pwm[0] == 0, "utsignal 0 när PLC inte kör");

    fast_ctrl_set_run(true);
    run(&in, &out, 1);
    expect(out.pwm[0] == 1000, "P: 10 x (500 - 400) = 1000");
    expect(rd_in(310) == 1000 && rd_in(311) == 400 && (int16_t)rd_in(312) == 100,
           "status: utsignal, återkoppling, fel");

    in.ai[0] = 600;
    run(&in, &out, 1);
    expect(out.pwm[0] == 0, "negativ utsignal kläms till out_min");
}

static void test_pid_i_and_windup(void)
{
    FastIn in;
    FastOut out;
    uint16_t first;
    int i;

    fast_ctrl_init();
    memset(&in, 0, sizeof(in));
    fast_ctrl_set_run(true);
    /* Bara I: ki = 100,0 per sekund, period 10 ms, tak 2000. */
    setup_pid(1, 3, 3, 100, 0, 100 * 256, 0, 10, 0, 2000);
    in.ai[3] = 90; /* fel 10 */

    run(&in, &out, 1);
    first = out.pwm[3];
    expect(first == 10, "första I-steg: 100 x 10 x 0,01 s = 10");
    run(&in, &out, 10 * 9);
    expect(out.pwm[3] == 100, "efter 100 ms: 100");

    /* Kör långt in i mättnad och kontrollera att integralen inte rusar. */
    for (i = 0; i < 100; i++) {
        run(&in, &out, 1000);
    }
    expect(out.pwm[3] == 2000, "mättad på out_max");
    in.ai[3] = 110; /* fel -10 */
    run(&in, &out, 10);
    expect(out.pwm[3] < 2000, "lämnar mättnad direkt när felet byter tecken");

    /* Liten ki ska inte avrundas bort. ki = 0,1/s, fel 10, 10 s -> 10. */
    fast_ctrl_init();
    fast_ctrl_set_run(true);
    setup_pid(0, 0, 1, 100, 0, 26, 0, 10, 0, 65535);
    in.ai[0] = 90;
    run(&in, &out, 10000);
    expect(out.pwm[1] >= 9 && out.pwm[1] <= 11, "liten ki integreras korrekt");
}

static void test_pid_gating(void)
{
    FastIn in;
    FastOut out;

    fast_ctrl_init();
    memset(&in, 0, sizeof(in));
    fast_ctrl_set_run(true);
    setup_pid(0, 0, 2, 500, 256, 0, 0, 1, 0, 65535); /* H2_AHI */
    in.ai[0] = 0;
    run(&in, &out, 1);
    expect(out.pwm[2] == 500, "PID driver H2_AHI");

    /* Förregling på H2 stoppar PID:en. */
    wr(FAST_REG_ILK_CFG, FAST_ILK_ENABLE | FAST_ILK_TRIP_HIGH | FAST_ILK_BLOCK_H2 | 1u);
    in.dio_in[1] = true;
    run(&in, &out, 1);
    expect(out.block[1] && out.pwm[2] == 0, "spärrad brygga ger utsignal 0");

    /* Två kanaler på samma utgång: den andra är ogiltig. */
    fast_ctrl_init();
    fast_ctrl_set_run(true);
    setup_pid(0, 0, 1, 500, 256, 0, 0, 1, 0, 65535);
    setup_pid(1, 1, 1, 500, 256, 0, 0, 1, 0, 65535);
    run(&in, &out, 1);
    expect(rd_in(303) == 0x02u, "pid1 markeras felkonfigurerad");
    expect(out.pwm_owned == 0x02u, "bara pid0 äger kanalen");

    /* Ogiltigt AI-index. */
    fast_ctrl_init();
    setup_pid(0, 9, 0, 0, 0, 0, 0, 1, 0, 65535);
    run(&in, &out, 1);
    expect(rd_in(303) == 0x01u && out.pwm_owned == 0, "ogiltig återkoppling äger inget");
}

static void test_modbus_map(void)
{
    uint16_t v;
    uint16_t cfg[3] = { 0x8009u, 0, 0 };

    fast_ctrl_init();
    register_image_init();
    expect(register_image_write_regs(301, 3, cfg) == 0, "FC16 till förreglingar");
    expect(register_image_read_regs(true, 301, 1, &v) == 0 && v == 0x8009u, "läs tillbaka ilk_cfg");
    expect(register_image_write_regs(305, 1, cfg) == 2, "305 är inte skrivbar");
    expect(register_image_write_regs(330, 1, cfg) == 2, "330 är inte skrivbar");
    v = 0;
    expect(register_image_write_regs(300, 1, (uint16_t[]){ 1 }) == 0, "kvittering skrivbar");
    expect(register_image_read_regs(true, 300, 1, &v) == 0 && v == 0, "kvittering läses som 0");
    expect(register_image_read_regs(false, 301, 1, &v) == 0, "tickräknare läsbar");
}

int main(void)
{
    test_interlock();
    test_pid_p();
    test_pid_i_and_windup();
    test_pid_gating();
    test_modbus_map();
    if (g_fails) {
        fprintf(stderr, "%d av %d kontroller fel\n", g_fails, g_checks);
        return 1;
    }
    printf("unit-test ok (%d kontroller)\n", g_checks);
    return 0;
}
