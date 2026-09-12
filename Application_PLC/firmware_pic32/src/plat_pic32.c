#if defined(__PIC32MX__)
#include "plc_runtime.h"

/*
 * Kopplas senare mot Application_OEM HAL (ADC, DIO, oemLog)
 * utan att ändra OEM-projektet. Den här filen byggs bara med XC32.
 */

void plat_read_inputs(PlcInputs *in)
{
    (void)in;
}

void plat_write_outputs(const PlcOutputs *out)
{
    (void)out;
}

void plat_logger_tick(const PlcInputs *in, const PlcStatus *st)
{
    (void)in;
    (void)st;
    /* Anropa befintlig Log()/logRunAvg från OEM när HAL-bryggan finns. */
}

bool plat_plc_program_present(void)
{
    return false;
}

#endif
