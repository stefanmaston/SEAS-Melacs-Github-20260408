/* 
 * File:   appPortableAutomation.h
 * Author: Bala
 *
 * Created on June 29, 2015, 11:47 AM
 */

#ifndef APP_PORTABLE_AUTOMATION_H
#define	APP_PORTABLE_AUTOMATION_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define AVERAGING_LENGTH_THERMOCOUPLE 6
#define AVERAGING_LENGTH_PRESSURE 6

#define AVERAGING_LENGTH_KEY 6
#define AVG_KEY_MAX 4
#define AVG_KEY_MIN 3

#define DISPLAY_CHNG_TIME 4
#define AVG_LENGTH 10

/*
 * For sine wave on burner fan
#define BURNER_MAX_LEVEL 7
#define BURNER_MIN_LEVEL 2
#define BURNER_TIME_PERIOD 16 //Start with a time period of 6 seconds
*/

#define BURST_PERIOD 5
#define DEFAULT_BURST_LEN 700
#define AVERAGING_LENGTH_PRESSURE_BURST 100  //Nisse Used a valve of 100 in his excel sheet
#define BURST_DELAY 100

#define MAXIMUM_RADIATOR_FAN_VOLTAGE 8
#define MINIMUM_RADIATOR_FAN_VOLTAGE 2.4
#define MAX_RADIATOR_FAN_TEMPERATURE 85
#define MIN_RADIATOR_FAN_TEMPERATURE 75
#define SWITCH_OFF_RADIATOR_FAN_TEMP 50
#define MAX_VALVE_POSITION_TEMPERATURE 85
#define MIN_VALVE_POSITION_TEMPERATURE 75
#define SWITCHOFF_VALVE_POSITION_TEMP 65
#define MAX_VALVE_POSITION 10
#define MIN_VALVE_POSITION 0

#define INITIAL_DOSE_TIME 15
#define INITIAL_START_BURNER_FAN_DELAY 180
#define INITIAL_START_BURNER_FAN_TEMP 50
#define COMBUSTION_SUCCESSFUL_TEMP 100
#define AFTER_COMBUSTION_BUILDUP_TIME 120
#define BURNER_FAN_VOLTAGE_STAGE2 4.2
#define BURNER_FAN_VOLTAGE_STAGE3 6.0
#define FEED_ON_TIME_STAGE3 5    

#define BURNER_FAN_SWITCHOFF_TEMPERATURE 50
#define INPUT_PELLET_POWERKW 3.423
#define INVERTER_ON_TEMPERATURE 600
#define INVERTER_OFF_TEMPERATURE 500
#define INVERTER_CTR_THRESHOLD 100
#define DEFAULT_LOWER_HYSTERSIS_THRESHOLD 300
#define DEFAULT_HIGHER_HYSTERSIS_THRESHOLD 1100
#define ERROR_PROCESS_TEMP_LOWER_THRESHOLD 200
#define DEFAULT_FINAL_FEED_RAMP_UP_TIME 1200
#define BURNER_FAN_VOLTAGE_STAGE4 11.0
#define FEED_ON_TIME_STAGE4 10    

#define LOWEST_COOLER_TEMPERATURE 5
#define HIGHEST_COOLER_TEMPERATURE 95
#define LOWEST_HEATER_TEMPERATURE 0
#define HIGHEST_HEATER_TEMPERATURE 1050
#define LOWEST_GAS_PRESSURE 6
#define HIGHEST_GAS_PRESSURE 50    

#define PRESSURE_ONTIME 2
#define PRESSURE_OFFTIME 2    
    
typedef struct
{ 
    bool burnerPotEn;
    bool radiatPotEn;
    bool pageChngEn;
    bool fuelFeed;
    bool circulationPump;
    bool keyStatus;
    bool inverterStatus;
    bool ignitorStatus;
    bool combustionSuccessful;  
    bool reachedProcessTemperatureOnce;
    bool gasStatus;
    bool statusFillValve;
    bool statusReleaseValve;  
    bool is_sdcard_ok; 
    bool gasLockout; 
    bool gasReset;
    int pressureTop;
    int tempSensor;
    int tempThermoC;
    int displayPage;    
    int tcAvg;
    int lastTcAvg;
    int pressAvg;
    int maxTopPressure;
    int minTopPressure;
    int displayChange;
    int boardTemp;
    int logReturn;
    int lastLogReturn;
    int inverterOnCounter;
    int inverterOffCounter;
    int error;
    int warning;
    int errorCode;
    int valvePos;  
    int newValvePos;
    int stageSystem;
    int amtFuel;  
    int combustionSuccessfullTime;
    int returnVal;
    int fillPressure;   
    int releasePressure;  
    int prevSetPressure;
    int pressureSet;	
    unsigned int nSecondCounter;
    unsigned int nPressureCounter;   
    unsigned int nSetPressureCounter;  
    unsigned int nFinalFeedRampCounter;	
	float BurnerFanVoltage;
    float RadiatorFanVoltage_;
    float BurnerFanVoltage_;
    float FeederOnTime;
    float pelletPowerkW;  
    int limpMode;
    float version;
    bool versionWritten;  
} portableStruct;
    

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
    bool variable_GasLockout;
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
    float variable_GasLevel;
} melacsReceive;

void CheckAndDoShutdown(melacsReceive * recvCollection, melacsSend * sendCollection);
void ExecuteReceivedCommands(portableStruct * ps, melacsReceive * recvCollection, melacsSend * sendCollection);
void GetStageSpecificParameters(portableStruct * ps, melacsReceive * recvCollection);
void UpdateTimeCounter(portableStruct * ps);
void PreCombustion(portableStruct * ps, melacsReceive * recvCollection);
void StageTwoAndThree(portableStruct * ps, melacsReceive * recvCollection);
void StageFour(portableStruct * ps, melacsReceive * recvCollection);
void Gas(portableStruct * ps, melacsReceive * recvCollection);
void PostCombustion(portableStruct * ps, melacsReceive * recvCollection);
void KeyOnRoutine(portableStruct * ps, melacsReceive * recvCollection);
void KeyOffRoutine(portableStruct * ps, melacsReceive * recvCollection);
void InverterStatusCalc(portableStruct * ps, melacsReceive * recvCollection);
void RadiatorVoltageCalc(portableStruct * ps, melacsReceive * recvCollection);
void ValvePositionCalc(portableStruct * ps, melacsReceive * recvCollection);
void CirculationPumpCalc(portableStruct * ps, melacsReceive * recvCollection);
void PressureFillReleaseCalc(portableStruct * ps, melacsReceive * recvCollection);
void SystemRegulation(portableStruct * ps, melacsReceive * recvCollection);
void GetInputs(portableStruct * ps, melacsReceive * recvCollection);

void ReadAdAndRTC();
void SensorCheck(portableStruct * ps, melacsReceive * recvCollection);
void GetSensorValues(portableStruct * ps, melacsReceive * recvCollection);

int getTcAvgValue(int tcTemperature);
int getPressTopAvgValue(int pressure);
void getBurstPressureRead(int *maxTopPressure, int * minTopPressure, int averagingBurstLength, int burstPeriod, int burstLength, int delayValue,  int ADport);
void getBurstTopPressureRead(int *maxTopPressure, int * minTopPressure, int averagingBurstLength, int burstPeriod, int burstLength, int delayValue);
bool getShutdownStatus(int shutdownValue);
bool getKeyStatus(int keyValue);

float pelletTimeToKW(int time);
void OutputControl(portableStruct * ps, melacsReceive * recvCollection);

int checkRangeLong(long value, long max, long min);
int checkRangeDouble(double value, double max, double min);
int saveParametersToFile(melacsReceive * recvCollection);
int readParametersFromFile(melacsReceive * recvCollection);
int saveVersionInfo(portableStruct * ps);

void initMelacsSend(melacsSend * sendCollection);
int initMelacsRecv(melacsReceive * recvCollection);
void writeToUsbSendBuffer(melacsSend * sendCollection);
void readFromUsbReceiveBuffer(melacsReceive * recvCollection);
void SendToUsb(portableStruct * ps, melacsSend * sendCollection); 

void OutputControl(portableStruct * ps, melacsReceive * recvCollection);
void Display(portableStruct * ps, melacsReceive * recvCollection);
void Gsm(portableStruct * ps, melacsReceive * recvCollection);
void Log(portableStruct * ps, melacsReceive * recvCollection);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_PORTABLE_AUTOMATION_H */
