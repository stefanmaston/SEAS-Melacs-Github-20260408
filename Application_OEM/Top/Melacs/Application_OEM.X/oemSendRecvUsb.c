#include "main.h"
#ifdef APPLICATION_OEM

#define _SUPPRESS_PLIB_WARNING

#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "onBoardADC.h"
#include <pthread.h>
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include "math.h"
#include "readConfig.h"
#include "onBoardRTCC.h"
#include "appOEM.h"
#include "mutex.h"

uint8_t sendTCPBuffer[TCP_SEND_BUFFER_SIZE] = {0};
uint8_t recvTCPBuffer[TCP_RECV_BUFFER_SIZE] = {0};

extern float M1CUR;
extern float M2CUR;


void initMelacsSend(melacsSend * sendCollection)
{
    sendCollection->variable_AD7 = 0;
    sendCollection->variable_AD7 = 0;
    sendCollection->variable_AD6 = 0;
    sendCollection->variable_AD6 = 0;
    sendCollection->variable_AD5 = 0;
    sendCollection->variable_AD5 = 0;
    sendCollection->variable_AD4 = 0;
    sendCollection->variable_AD4 = 0;
    sendCollection->variable_AD3 = 0;
    sendCollection->variable_AD3 = 0;
    sendCollection->variable_AD2 = 0;
    sendCollection->variable_AD2 = 0;
    sendCollection->variable_AD1 = 0;
    sendCollection->variable_AD1 = 0;
    sendCollection->variable_AD0 = 0;
    sendCollection->variable_AD0 = 0;    	
    sendCollection->variable_DIO7 = 0;
    sendCollection->variable_DIO7 = 0;
    sendCollection->variable_DIO6 = 0;
    sendCollection->variable_DIO6 = 0;
    sendCollection->variable_DIO5 = 0;
    sendCollection->variable_DIO5 = 0;
    sendCollection->variable_DIO4 = 0;
    sendCollection->variable_DIO4 = 0;  
    sendCollection->variable_DIO3 = 0;
    sendCollection->variable_DIO3 = 0; 
    sendCollection->variable_DIO2 = 0;
    sendCollection->variable_DIO2 = 0;  
    sendCollection->variable_DIO1 = 0;
    sendCollection->variable_DIO1 = 0;     
    sendCollection->variable_DIO0 = 0;
    sendCollection->variable_DIO0 = 0; 
    sendCollection->variable_JP18 = 0; 
    sendCollection->variable_JP19 = 0; 
    sendCollection->variable_JP3 = 0; 
    sendCollection->variable_JP4 = 0; 
    sendCollection->variable_JP5 = 0; 
    sendCollection->variable_JP6 = 0; 
    sendCollection->variable_JP7 = 0; 
    sendCollection->variable_JP8 = 0; 
    sendCollection->variable_JP9 = 0; 
    sendCollection->variable_JP10 = 0; 
    sendCollection->variable_M1CUR = 0;
    sendCollection->variable_M2CUR = 0;
    sendCollection->variable_BoardTemperature = 0; 
    sendCollection->variable_KeyStatus = 0; 
    sendCollection->variable_HeaterTemperature = 0;
    sendCollection->variable_HeaterTemperature = 0; 	
    sendCollection->variable_EngineTemperature = 0; 
    sendCollection->variable_EnginePressure = 0; 
    sendCollection->variable_MaxTopPressure = 0; 
    sendCollection->variable_MinTopPressure = 0; 
    sendCollection->variable_ValvePosition = 0; 
    sendCollection->variable_RadiatorFan = 0; 
    sendCollection->variable_BurnerFan = 0; 
    sendCollection->variable_FeederStatus = 0; 
    sendCollection->variable_IgnitorStatus = 0; 
    sendCollection->variable_InverterStatus = 0; 
    sendCollection->variable_CompressorStatus = 0; 
    sendCollection->variable_SDCardStatus = 0; 
    sendCollection->variable_Error = 0; 
    sendCollection->variable_errorCode = 0; 
    sendCollection->variable_InverterOnCounter = 0;
    sendCollection->variable_InverterOffCounter = 0;
    sendCollection->variable_LogReturn = 0;
    sendCollection->variable_LastLogReturn = 0;
    sendCollection->variable_Stage = 0;  
    sendCollection->variable_SystemStatus = 1;
    sendCollection->variable_PelletFeedKW = 0;
    
  
}

int initMelacsRecv(melacsReceive * recvCollection)
{
    int ret = 0;
    ret = readParametersFromFile(recvCollection);
    if(1 == ret)
    {
        return 1;
    }
    
    recvCollection->newData = 0;    
    recvCollection->dataType = 0;     
    recvCollection->variable_Shutdown = 0;
   
    recvCollection->variable_SDCardMount = 1;  //Mount the SD card during the start
    recvCollection->variable_PageChangeEnable = 0;  //Disable page change enable
    recvCollection->variable_ResetErrorAndWarnings = 0;
    recvCollection->variable_BurstPeriod = 0; 
    recvCollection->variable_BurstLength = 0;
    recvCollection->variable_AveragingBurstLength = 0;  //TODO
    recvCollection->variable_BurstDelay = 0;

    recvCollection->variable_MaxRadiatorFanVoltage = 0;
    recvCollection->variable_MinRadiatorFanVoltage = 0;
    recvCollection->variable_MaxRadiatorFanTemp = 0; 
    recvCollection->variable_MinRadiatorFanTemp = 0; 
    recvCollection->variable_SwitchOffRadiatorFanTemp = 0; 
    recvCollection->variable_MaxValvePosTemp = 0; 
    recvCollection->variable_MinValvePosTemp = 0; 
    recvCollection->variable_SwitchOffValvePositionTemp = 0; 

    recvCollection->variable_InitialDoseTime = 0; 
    recvCollection->variable_InitialStartBurnerFanDelay = 0;
    recvCollection->variable_InitialStartBurnerTemp = 0;
    recvCollection->variable_CombustionSuccessTemp = 0;
    recvCollection->variable_AfterCombustionBuildUpTime = 0;
    recvCollection->variable_BurnerSpeedStage2 = 0;    
    recvCollection->variable_BurnerSpeedStage3 = 0;    
    recvCollection->variable_FeedOnTimeStage3 = 0;  
    
    recvCollection->variable_BurnerFanSwitchOffTemperature = 0; 
    recvCollection->variable_InputPelletPowerKW = 0; 
    recvCollection->variable_ProcessMinHeaterTemp = 0;
    recvCollection->variable_ProcessMaxHeaterTemp = 0;
	recvCollection->variable_ErrorProcTempLowThresh = 0;
    recvCollection->variable_FinalFeedRampUpTime = 0;
    recvCollection->variable_BurnerSpeedStage4 = 0;
    recvCollection->variable_FeedOnTimeStage4 = 0;  

    recvCollection->variable_SaveParameterFile = 0;   
#ifdef LOGGING
    recvCollection->variable_LogSamplePeriod = SAMPLE_PERIOD; 
    recvCollection->variable_NumOfSampleInEachLog = TOTAL_SAMPLES_IN_EACH_LOG; 
    recvCollection->variable_TimeToBurstLog = LOGBURST_PERIOD*LOGBURST_COUNTER;
    recvCollection->variable_NumOfSamplesInBurstLog = NUM_BURST_READS;
#endif
    recvCollection->variable_SynTime = 0; 
    recvCollection->variable_Year = YEAR;
    recvCollection->variable_Month = MONTH; 
    recvCollection->variable_Day = DAY; 
    recvCollection->variable_Hour = HOUR; 
    recvCollection->variable_Minute = MINUTE; 
    recvCollection->variable_Second = SECOND; 
    recvCollection->variable_Weekday = WEEKDAY; 
    
    recvCollection->variable_EnableOverrideBurnerFan = 0;
    recvCollection->variable_OverrideBurnerFan = 0;
    recvCollection->variable_EnableOverrideRadiatorFan = 0;
    recvCollection->variable_OverrideRadiatorFan = 0;
    recvCollection->variable_EnableOverrideValvePosition = 0;
    recvCollection->variable_OverrideValvePosition = 0;
    recvCollection->variable_EnableOverrideCirculationPump = 0;
    recvCollection->variable_OverrideCirculationPump = 0;
    recvCollection->variable_EnableOverrideFeeder = 0;
    recvCollection->variable_OverrideFeeder = 0;
    recvCollection->variable_EnableOverrideIgnitor = 0;
    recvCollection->variable_OverrideIgnitor = 0;
    recvCollection->variable_EnableOverrideInverter = 0;
    recvCollection->variable_OverrideInverter = 0;
    recvCollection->variable_EnableOverrideKey = 0;
    recvCollection->variable_OverrideKey = 0;
    recvCollection->variable_EnableOverrideGas = 0;
    recvCollection->variable_OverrideGas = 0;

    recvCollection->variable_EnableSettingPressure = 0;
    recvCollection->variable_SetPressure = 0;        
    recvCollection->variable_LowestCoolerTemp = LOWEST_COOLER_TEMPERATURE;
    recvCollection->variable_HighestCoolerTemp = HIGHEST_COOLER_TEMPERATURE;
    recvCollection->variable_LowestHeaterTemp = LOWEST_HEATER_TEMPERATURE;
    recvCollection->variable_HighestHeaterTemp = HIGHEST_HEATER_TEMPERATURE;
    recvCollection->variable_LowestGasPressure = LOWEST_GAS_PRESSURE;
    recvCollection->variable_HighestGasPressure = HIGHEST_GAS_PRESSURE;    
    
    recvCollection->variable_EnableGas = 0;
    recvCollection->variable_GasThermostatMinTemp = 0;
    recvCollection->variable_GasThermostatMaxTemp = 0;    
    
    recvCollection->variable_InverterOnTemperature = 0;
    recvCollection->variable_InverterOffTemperature = 0;
    recvCollection->variable_InverterDelayCounter = 0;    
    return ret;
}


void writeToUsbSendBuffer(melacsSend * sendCollection)
{
    int i = 0;
    bufWriteLockMutex();
    sendTCPBuffer[i++] = 0xFF;
    sendTCPBuffer[i++] = 1;    
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD7 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD7&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD6 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD6&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD5 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD5&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD4 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD4&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD3 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD3&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD2 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD2&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD1 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD1&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD0 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_AD0&0x00FF);    	
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_DIO7 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_DIO7&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_DIO6 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_DIO6&0x00FF);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_DIO5 >> 8);
    sendTCPBuffer[i++] = (uint8_t)(sendCollection->variable_DIO5&0x00FF);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO4 >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO4&0x00FF);  
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO3 >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO3&0x00FF); 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO2 >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO2&0x00FF);  
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO1 >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO1&0x00FF);     
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO0 >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_DIO0&0x00FF); 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_JP18*10); 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_JP19*10); 
    sendTCPBuffer[i++] =  sendCollection->variable_JP3; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP4; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP5; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP6; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP7; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP8; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP9; 
    sendTCPBuffer[i++] =  sendCollection->variable_JP10; 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_M1CUR*10);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_M2CUR*10);
    sendTCPBuffer[i++] =  sendCollection->variable_BoardTemperature; 
    sendTCPBuffer[i++] =  sendCollection->variable_KeyStatus; 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_HeaterTemperature >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_HeaterTemperature&0x00FF); 	
    sendTCPBuffer[i++] =  sendCollection->variable_EngineTemperature; 
    sendTCPBuffer[i++] =  sendCollection->variable_EnginePressure; 
    sendTCPBuffer[i++] =  sendCollection->variable_MaxTopPressure; 
    sendTCPBuffer[i++] =  sendCollection->variable_MinTopPressure; 
    sendTCPBuffer[i++] =  sendCollection->variable_ValvePosition; 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_RadiatorFan*10); 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_BurnerFan*10); 
    sendTCPBuffer[i++] =  sendCollection->variable_FeederStatus; 
    sendTCPBuffer[i++] =  sendCollection->variable_IgnitorStatus; 
    sendTCPBuffer[i++] =  sendCollection->variable_InverterStatus; 
    sendTCPBuffer[i++] =  sendCollection->variable_CompressorStatus; 
    sendTCPBuffer[i++] =  sendCollection->variable_SDCardStatus; 
    sendTCPBuffer[i++] =  sendCollection->variable_Error; 
    sendTCPBuffer[i++] =  sendCollection->variable_errorCode; 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_InverterOnCounter >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_InverterOnCounter&0x00FF); 	
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_InverterOffCounter >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_InverterOffCounter&0x00FF); 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_LogReturn >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_LogReturn&0x00FF); 
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_LastLogReturn >> 8);
    sendTCPBuffer[i++] =  (uint8_t)(sendCollection->variable_LastLogReturn&0x00FF);    
    sendTCPBuffer[i++] =  sendCollection->variable_Stage;   
    sendTCPBuffer[i++] =  sendCollection->variable_SystemStatus;  
    sendTCPBuffer[i++] =  sendCollection->variable_PelletFeedKW*10;
    
    bufWriteUnlockMutex();
}

void readFromUsbReceiveBuffer(melacsReceive * recvCollection)
{
    int i = 0;
    bufReadLockMutex();
    recvCollection->newData = 0;    
    if(0xFF == recvTCPBuffer[i])
    {
        i++;
    }
        
    recvCollection->newData = recvTCPBuffer[i++]; 
    
    if(1 == recvCollection->newData)
    {
        recvCollection->dataType = recvTCPBuffer[i++];     
        switch(recvCollection->dataType)
        {
            case 0:       
                recvCollection->variable_Shutdown = recvTCPBuffer[i++]; 
                break;
                
            case 1:                   
                recvCollection->variable_SDCardMount = recvTCPBuffer[i++]; 
                recvCollection->variable_PageChangeEnable = recvTCPBuffer[i++]; 
                recvCollection->variable_ResetErrorAndWarnings = recvTCPBuffer[i++]; 
                recvCollection->variable_BurstPeriod = recvTCPBuffer[i++]; 
                recvCollection->variable_BurstLength = recvTCPBuffer[i++]*100; 
                recvCollection->variable_AveragingBurstLength = recvTCPBuffer[i++]; 
                recvCollection->variable_BurstDelay = (recvTCPBuffer[i] << 8) | recvTCPBuffer[i+1]; i += 2;
                break;

            case 2:               
                recvCollection->variable_MaxRadiatorFanVoltage = recvTCPBuffer[i++]/10.0; 
                recvCollection->variable_MinRadiatorFanVoltage = recvTCPBuffer[i++]/10.0; 
                recvCollection->variable_MaxRadiatorFanTemp = recvTCPBuffer[i++]; 
                recvCollection->variable_MinRadiatorFanTemp = recvTCPBuffer[i++]; 
                recvCollection->variable_SwitchOffRadiatorFanTemp = recvTCPBuffer[i++]; 
                recvCollection->variable_MaxValvePosTemp = recvTCPBuffer[i++]; 
                recvCollection->variable_MinValvePosTemp = recvTCPBuffer[i++]; 
                recvCollection->variable_SwitchOffValvePositionTemp = recvTCPBuffer[i++]; 
                break;

            case 3:              
                recvCollection->variable_InitialDoseTime = recvTCPBuffer[i++]; 
                recvCollection->variable_InitialStartBurnerFanDelay = recvTCPBuffer[i++]*10;    
                recvCollection->variable_InitialStartBurnerTemp = recvTCPBuffer[i++]*5;                
                recvCollection->variable_CombustionSuccessTemp = recvTCPBuffer[i++]*10; 
                recvCollection->variable_AfterCombustionBuildUpTime = recvTCPBuffer[i++]*10; 
                recvCollection->variable_BurnerSpeedStage2 = recvTCPBuffer[i++]/10.0;                 
                recvCollection->variable_BurnerSpeedStage3 = recvTCPBuffer[i++]/10.0; 
                recvCollection->variable_FeedOnTimeStage3 = (recvTCPBuffer[i] << 8) | recvTCPBuffer[i+1]; i += 2;;                  
                break;

            case 4:             
                recvCollection->variable_BurnerFanSwitchOffTemperature = recvTCPBuffer[i++]; 
                //recvCollection->variable_InputPelletPowerKW = recvTCPBuffer[i++];                 
                recvCollection->variable_ProcessMinHeaterTemp = recvTCPBuffer[i++]*10; 
                recvCollection->variable_ProcessMaxHeaterTemp = recvTCPBuffer[i++]*10; 
                recvCollection->variable_ErrorProcTempLowThresh = recvTCPBuffer[i++]*10;   
                recvCollection->variable_FinalFeedRampUpTime = (recvTCPBuffer[i] << 8) | recvTCPBuffer[i+1]; i += 2;                
                recvCollection->variable_BurnerSpeedStage4 = recvTCPBuffer[i++]/10.0; 
                recvCollection->variable_FeedOnTimeStage4  = (recvTCPBuffer[i] << 8) | recvTCPBuffer[i+1]; i += 2;;    
                break;

            case 5: 
                recvCollection->variable_SaveParameterFile = recvTCPBuffer[i++];                  
                recvCollection->variable_LogSamplePeriod = recvTCPBuffer[i++]; 
                recvCollection->variable_NumOfSampleInEachLog = recvTCPBuffer[i++]; 
                recvCollection->variable_TimeToBurstLog = recvTCPBuffer[i++]*10; 
                recvCollection->variable_NumOfSamplesInBurstLog = recvTCPBuffer[i++]*100; 
                break;

            case 6:                
                recvCollection->variable_SynTime = recvTCPBuffer[i++]; 
                recvCollection->variable_Year = recvTCPBuffer[i++]; 
                recvCollection->variable_Month = recvTCPBuffer[i++]; 
                recvCollection->variable_Day = recvTCPBuffer[i++]; 
                recvCollection->variable_Hour = recvTCPBuffer[i++]; 
                recvCollection->variable_Minute = recvTCPBuffer[i++]; 
                recvCollection->variable_Second = recvTCPBuffer[i++]; 
                recvCollection->variable_Weekday = recvTCPBuffer[i++]; 
                break;
                
            case 7:                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideBurnerFan = 0;
                    recvCollection->variable_OverrideBurnerFan = 0;
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideBurnerFan = 1;                    
                    recvCollection->variable_OverrideBurnerFan = recvTCPBuffer[i++]/10.0; 
                }
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideRadiatorFan = 0;
                    recvCollection->variable_OverrideRadiatorFan = 0;                    
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideRadiatorFan = 1;                    
                    recvCollection->variable_OverrideRadiatorFan = recvTCPBuffer[i++]/10.0; 
                }       
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideValvePosition = 0;
                    recvCollection->variable_EnableOverrideValvePosition = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideValvePosition = 1;                    
                    recvCollection->variable_OverrideValvePosition = recvTCPBuffer[i++]; 
                }       
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideCirculationPump = 0;
                    recvCollection->variable_OverrideCirculationPump = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideCirculationPump = 1;                    
                    recvCollection->variable_OverrideCirculationPump = recvTCPBuffer[i++]; 
                }                   
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideFeeder = 0;
                    recvCollection->variable_OverrideFeeder = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideFeeder = 1;                    
                    recvCollection->variable_OverrideFeeder = recvTCPBuffer[i++]; 
                }  
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideIgnitor = 0;
                    recvCollection->variable_OverrideIgnitor = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideIgnitor = 1;                    
                    recvCollection->variable_OverrideIgnitor = recvTCPBuffer[i++]; 
                }                         
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideInverter = 0;
                    recvCollection->variable_OverrideInverter = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideInverter = 1;                    
                    recvCollection->variable_OverrideInverter = recvTCPBuffer[i++]; 
                }             
                
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideKey = 0;
                    recvCollection->variable_OverrideKey = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideKey = 1;                    
                    recvCollection->variable_OverrideKey = recvTCPBuffer[i++]; 
                }     

                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableOverrideGas = 0;
                    recvCollection->variable_OverrideGas = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableOverrideGas = 1;                    
                    recvCollection->variable_OverrideGas = recvTCPBuffer[i++]; 
                }             
                break;      
                
            case 8:             
                if(0xFF == recvTCPBuffer[i])
                {
                    recvCollection->variable_EnableSettingPressure = 0;
                    recvCollection->variable_SetPressure = 0;                     
                    i++;
                }
                else
                {
                    recvCollection->variable_EnableSettingPressure = 1;                    
                    recvCollection->variable_SetPressure = recvTCPBuffer[i++]; 
                }        
                
                recvCollection->variable_LowestCoolerTemp = recvTCPBuffer[i++]; 
                recvCollection->variable_HighestCoolerTemp = recvTCPBuffer[i++];                 
                recvCollection->variable_LowestHeaterTemp = recvTCPBuffer[i++]*10; 
                recvCollection->variable_HighestHeaterTemp = recvTCPBuffer[i++]*10; 
                recvCollection->variable_LowestGasPressure = recvTCPBuffer[i++]; 
                recvCollection->variable_HighestGasPressure = recvTCPBuffer[i++];   
                break;    
                
            case 9:             
                recvCollection->variable_EnableGas = recvTCPBuffer[i++]; 
                recvCollection->variable_GasThermostatMinTemp = recvTCPBuffer[i++]*10; 
                recvCollection->variable_GasThermostatMaxTemp = recvTCPBuffer[i++]*10; 
                break;  
                
            case 10:             
                recvCollection->variable_InverterOnTemperature = recvTCPBuffer[i++]*10; 
                recvCollection->variable_InverterOffTemperature = recvTCPBuffer[i++]*10; 
                recvCollection->variable_InverterDelayCounter = recvTCPBuffer[i++]*10; 
                break;                
            
            default:  
                break;
        }
    }
    
    bufReadUnlockMutex();
}

void SendToUsb(oemStruct * os, melacsSend * sendCollection)        
{
#ifdef _ONBOARD_ADC_FUNC_
    sendCollection->variable_AD7 = adcresult[7]; 
    sendCollection->variable_AD6 = adcresult[6]; 
    sendCollection->variable_AD5 = adcresult[5]; 
    sendCollection->variable_AD4 = adcresult[4]; 
    sendCollection->variable_AD3 = adcresult[3];  
    sendCollection->variable_AD2 = adcresult[2];  
    sendCollection->variable_AD1 = adcresult[1];
    sendCollection->variable_AD0 = adcresult[0]; 
#endif
    sendCollection->variable_DIO7 = DIO7_IN; 
    sendCollection->variable_DIO6 = DIO6_IN; 
    sendCollection->variable_DIO5 = DIO5_IN;  
    sendCollection->variable_DIO4 = DIO4_IN;   
    sendCollection->variable_DIO3 = DIO3_IN;   
    sendCollection->variable_DIO2 = DIO2_IN;   
    sendCollection->variable_DIO1 = DIO1_IN;  
    sendCollection->variable_DIO0 = DIO0_IN;   
    sendCollection->variable_JP18 = 0; 
    sendCollection->variable_JP19 = 0; 
//    sendCollection->variable_JP3 = LAT_SIP1; 
//    sendCollection->variable_JP4 = LAT_SIP0; 
//    sendCollection->variable_JP5 = LAT_SIP3;  
////    sendCollection->variable_JP6 = LAT_SIP2; 
//    sendCollection->variable_JP7 = LAT_SIP4; 
    sendCollection->variable_JP8 = LAT_SIP5; 
    sendCollection->variable_JP9 = LAT_SIP6;
    sendCollection->variable_JP10 = LAT_SIP7; 
    sendCollection->variable_M1CUR = 0; 
    sendCollection->variable_M2CUR = 0; 
    sendCollection->variable_BoardTemperature = os->boardTemp; 
    sendCollection->variable_KeyStatus = os->keyStatus; 
    sendCollection->variable_HeaterTemperature = os->tcAvg; 
    sendCollection->variable_EngineTemperature = os->tempSensor; 
    sendCollection->variable_EnginePressure = os->pressAvg; 
    sendCollection->variable_MaxTopPressure = os->maxTopPressure; 
    sendCollection->variable_MinTopPressure = os->minTopPressure; 
    sendCollection->variable_ValvePosition = 0; 
    sendCollection->variable_RadiatorFan = 0; 
    sendCollection->variable_BurnerFan = 0; 
    sendCollection->variable_FeederStatus = 0; 
    sendCollection->variable_IgnitorStatus = 0; 
    sendCollection->variable_InverterStatus = 0; 
    sendCollection->variable_CompressorStatus = 0; 
    sendCollection->variable_SDCardStatus = os->is_sdcard_ok; 
    sendCollection->variable_Error = os->error; 
    sendCollection->variable_errorCode = os->errorCode; 
    sendCollection->variable_InverterOnCounter = 0; 
    sendCollection->variable_InverterOffCounter = 0; 
    sendCollection->variable_LogReturn = os->logReturn; 
    sendCollection->variable_LastLogReturn = os->lastLogReturn;  
    sendCollection->variable_Stage = 0;   
    sendCollection->variable_SystemStatus = 1;
    sendCollection->variable_PelletFeedKW = 0;        

    writeToUsbSendBuffer(sendCollection);     
}

#endif