#include "plc_iec.h"

/*
 * Handskriven ekvivalent av plc/blink_dio.st (MatIEC-anropskonvention).
 * Ersätt den här filen med iec2c-output från OpenPLC Editor:
 *   POUS.c Config0.c + samma located-pekare.
 */

void config_init__(void)
{
}

void config_run__(unsigned long tick)
{
    (void)tick;
    if (__QX0_0 && __IX0_0) {
        *__QX0_0 = *__IX0_0;
    }
}
