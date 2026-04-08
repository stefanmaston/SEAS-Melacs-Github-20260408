/* 
 * File:   buzzer.h
 * Author: Bala
 *
 * Created on June 29, 2015, 11:47 AM
 */

#ifndef APP_OEM_H
#define	APP_OEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define LOWEST_COOLER_TEMPERATURE 5
#define HIGHEST_COOLER_TEMPERATURE 95
#define LOWEST_HEATER_TEMPERATURE 0
#define HIGHEST_HEATER_TEMPERATURE 1050
#define LOWEST_GAS_PRESSURE 6
#define HIGHEST_GAS_PRESSURE 50


#define AVERAGING_LENGTH_THERMOCOUPLE 20
#define AVERAGING_LENGTH_PRESSURE 20
#define AVERAGING_LENGTH_PRESSURE_BURST 20
#define AVERAGING_LENGTH_KEY 10
#define INV_CTR_THRESHOLD 100

#define AVG_KEY_MAX 8
#define AVG_KEY_MIN 2

#define DEFAULT_BURST_LEN 2000
#define BURST_PERIOD 2

#define DEFAULT_LOWER_HYSTERSIS_THRESHOLD 700
#define DEFAULT_HIGHER_HYSTERSIS_THRESHOLD 900

#define DISPLAY_CHNG_TIME 4
#define AVG_LENGTH 10    

typedef struct
{ 
    
    bool pageChngEn;
    bool circulationPump;
    bool keyStatus;
    bool releaseValve;
    bool fillValve;
    bool enableHeater;
    bool sd_mount;
    bool error;
    bool warning;
    bool inverterStatus;  
    bool is_sdcard_ok;      
    
    int pressureTop;
    int tempSensor;
    int tempThermoC;
    int tcAvg;
    int lastTcAvg;
    int pressAvg;
    int maxTopPressure;
    int minTopPressure;
    int boardTemp;    
    int returnVal;
    
    int inverterOnCounter;
    int inverterOffCounter;        
    
    int displayPage;    
    int displayChange;

    int logReturn;
    int lastLogReturn;
    int errorCode;        
} oemStruct;        
    


typedef struct
{   
    uint16_t variable_AD7; 
    uint16_t variable_AD6; 
    uint16_t variable_AD5; 
    uint16_t variable_AD4; 
    uint16_t variable_AD3; 
    uint16_t variable_AD2; 
    uint16_t variable_AD1; 
    uint16_t variable_AD0; 
    uint16_t variable_DIO7; 
    uint16_t variable_DIO6; 
    uint16_t variable_DIO5; 
    uint16_t variable_DIO4; 
    uint16_t variable_DIO3; 
    uint16_t variable_DIO2; 
    uint16_t variable_DIO1; 
    uint16_t variable_DIO0; 
    uint8_t variable_JP18; 
    uint8_t variable_JP19; 
    uint8_t variable_JP3; 
    uint8_t variable_JP4; 
    uint8_t variable_JP5; 
    uint8_t variable_JP6; 
    uint8_t variable_JP7; 
    uint8_t variable_JP8; 
    uint8_t variable_JP9; 
    uint8_t variable_JP10; 
    float variable_M1CUR; 
    float variable_M2CUR; 
    uint8_t variable_BoardTemperature; 
    bool variable_KeyStatus; 
    uint16_t variable_HeaterTemperature; 
    uint8_t variable_EngineTemperature; 
    uint8_t variable_EnginePressure; 
    uint8_t variable_MaxTopPressure; 
    uint8_t variable_MinTopPressure; 
    uint8_t variable_ValvePosition; 
    float variable_RadiatorFan; 
    float variable_BurnerFan; 
    bool variable_FeederStatus; 
    bool variable_IgnitorStatus; 
    bool variable_InverterStatus; 
    bool variable_CompressorStatus; 
    bool variable_SDCardStatus; 
    uint8_t variable_Error; 
    uint8_t variable_errorCode; 
    uint16_t variable_InverterOnCounter; 
    uint16_t variable_InverterOffCounter; 
    uint16_t variable_LogReturn; 
    uint16_t variable_LastLogReturn; 
    uint8_t variable_Stage;
    bool variable_SystemStatus;     
    float variable_PelletFeedKW;
} melacsSend;

typedef struct
{
    bool newData;
    uint8_t dataType;
    bool variable_Shutdown;
    
    bool variable_SDCardMount;
    bool variable_PageChangeEnable;
    bool variable_ResetErrorAndWarnings;
    uint8_t variable_BurstPeriod;
    uint16_t variable_BurstLength;
    uint8_t variable_AveragingBurstLength;
    uint16_t variable_BurstDelay;    
    
    float variable_MaxRadiatorFanVoltage;
    float variable_MinRadiatorFanVoltage;
    uint8_t variable_MaxRadiatorFanTemp;
    uint8_t variable_MinRadiatorFanTemp;
    uint8_t variable_SwitchOffRadiatorFanTemp;
    uint8_t variable_MaxValvePosTemp;
    uint8_t variable_MinValvePosTemp;
    uint8_t variable_SwitchOffValvePositionTemp;
    
    uint8_t variable_InitialDoseTime;
    uint16_t variable_InitialStartBurnerFanDelay;
    uint16_t variable_InitialStartBurnerTemp;    
    uint16_t variable_CombustionSuccessTemp;
    uint16_t variable_AfterCombustionBuildUpTime;
    float variable_BurnerSpeedStage2;    
    float variable_BurnerSpeedStage3;
    uint16_t variable_FeedOnTimeStage3;     
    
    uint8_t variable_BurnerFanSwitchOffTemperature;
    uint8_t variable_InputPelletPowerKW;
    uint16_t variable_ProcessMinHeaterTemp;
    uint16_t variable_ProcessMaxHeaterTemp;
    uint16_t variable_ErrorProcTempLowThresh;
    uint16_t variable_FinalFeedRampUpTime;    
    float variable_BurnerSpeedStage4;
    uint16_t variable_FeedOnTimeStage4; 
    
    bool variable_SaveParameterFile;    
    uint8_t variable_LogSamplePeriod;
    uint8_t variable_NumOfSampleInEachLog;
    uint16_t variable_TimeToBurstLog;
    uint16_t variable_NumOfSamplesInBurstLog;
    
	bool variable_SynTime;
    uint16_t variable_Year;
    uint8_t variable_Month;
    uint8_t variable_Day;
    uint8_t variable_Hour;
    uint8_t variable_Minute;
    uint8_t variable_Second;
    uint8_t variable_Weekday;   
    
    bool variable_EnableOverrideBurnerFan;
    float variable_OverrideBurnerFan;
    bool variable_EnableOverrideRadiatorFan;
    float variable_OverrideRadiatorFan;
    bool variable_EnableOverrideValvePosition;
    uint8_t variable_OverrideValvePosition;
    bool variable_EnableOverrideCirculationPump;
    bool variable_OverrideCirculationPump;
    bool variable_EnableOverrideFeeder;
    bool variable_OverrideFeeder;
    bool variable_EnableOverrideIgnitor;
    bool variable_OverrideIgnitor;
    bool variable_EnableOverrideInverter;
    bool variable_OverrideInverter;
    bool variable_EnableOverrideKey;
    bool variable_OverrideKey;
    bool variable_EnableOverrideGas;
    bool variable_OverrideGas;

    bool variable_EnableSettingPressure;
    uint8_t variable_SetPressure;
    uint8_t variable_LowestCoolerTemp;
    uint8_t variable_HighestCoolerTemp;
    uint16_t variable_LowestHeaterTemp;
    uint16_t variable_HighestHeaterTemp;
    uint8_t variable_LowestGasPressure;
    uint8_t variable_HighestGasPressure;
    
    uint16_t variable_InverterOnTemperature;
    uint16_t variable_InverterOffTemperature;
    uint16_t variable_InverterDelayCounter;    

    bool variable_EnableGas;
    uint16_t variable_GasThermostatMinTemp;
    uint16_t variable_GasThermostatMaxTemp;   
} melacsReceive;

//void Display(oemStruct * os);

void Gsm(oemStruct * os);
void Log(oemStruct * os);
void OutputControl(oemStruct * os);
void Inputs(oemStruct * os);
void SystemRegulation(oemStruct * os);

int getTcAvgValue(int tcTemperature);
int getPressAvgValue(int pressure);
void getBurstPressureRead(int *maxTopPressure, int * minTopPressure);
bool getKeyStatus(int keyValue);

void getParameters();
int readParametersFromFile(melacsReceive * recvCollection);
int saveParametersToFile(melacsReceive * recvCollection);

void initMelacsSend(melacsSend * sendCollection);
int initMelacsRecv(melacsReceive * recvCollection);
void writeToUsbSendBuffer(melacsSend * sendCollection);
void readFromUsbReceiveBuffer(melacsReceive * recvCollection);
void SendToUsb(oemStruct * os, melacsSend * sendCollection);

void ExecuteReceivedCommands(oemStruct * os, melacsReceive * recvCollection, melacsSend * sendCollection);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_OEM_H */
