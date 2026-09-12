#if defined(__PIC32MX__)

#include "oem_reuse.h"
#include "plc_runtime.h"

#include "log.h"
#include "onBoardRTCC.h"

extern LOGDATA logData;
extern void bootloader_recovery_second_step(void);
extern void logInit(void);
extern int logRunAvg(int samplePeriod, int numOfSamplesInEachLog);

void plat_boot_check(void)
{
    bootloader_recovery_second_step();
}

void plat_read_rtc(uint16_t *year, uint8_t *month, uint8_t *day,
                   uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    RTC_Read_Clock();
    if (year) {
        *year = (uint16_t)(2000u + RTCclk.year);
    }
    if (month) {
        *month = RTCclk.month;
    }
    if (day) {
        *day = RTCclk.mday;
    }
    if (hour) {
        *hour = RTCclk.hour;
    }
    if (minute) {
        *minute = RTCclk.minute;
    }
    if (second) {
        *second = RTCclk.second;
    }
}

void plat_read_inputs(PlcInputs *in)
{
    /* Fylls från OEM Inputs()/sendCollection när MPLAB-projektet länkar HAL. */
    (void)in;
    plat_read_rtc(0, 0, 0, 0, 0, 0);
}

void plat_write_outputs(const PlcOutputs *out)
{
    (void)out;
}

void plat_logger_tick(const PlcInputs *in, const PlcStatus *st)
{
    logData.AD0 = in->ad[0];
    logData.AD1 = in->ad[1];
    logData.AD2 = in->ad[2];
    logData.AD3 = in->ad[3];
    logData.AD4 = in->ad[4];
    logData.AD5 = in->ad[5];
    logData.AD6 = in->ad[6];
    logData.AD7 = in->ad[7];
    logData.boardTemp = (uint8_t)in->board_temp;
    logData.heaterTemperature = in->heater_temp;
    logData.engineTemperature = (uint8_t)in->engine_temp;
    logData.pressureNow = (uint8_t)in->engine_pressure;
    logData.ErrorCode = in->error_code;
    logData.error = in->error_code != 0;
    (void)st;
    logRunAvg(1, 1);
}

bool plat_plc_program_present(void)
{
    return plc_loader_program_present();
}

#endif
