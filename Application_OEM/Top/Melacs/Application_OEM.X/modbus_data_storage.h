
#ifndef MODBUS_DATA_STORAGE_H    /* Guard against multiple inclusion */
#define MODBUS_DATA_STORAGE_H
typedef enum 
{
    APP_SM_SYSTEM_MODE_STANDALONE_1_PHASE = 0,
	APP_SM_SYSTEM_MODE_STANDALONE_3_PHASES,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE_NO_BAT,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES_NO_BAT,
	APP_SM_SYSTEM_MODE_TEST,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES,
	APP_SM_SYSTEM_MODE_IDLE // Default IDLE

}SM_SYSTEM_MODE_t;

typedef enum
{ 
    PRE_START,
    START,
    IDLE,
    ERROR,
    GRID_RLY_CLOSE,
    DPLL_INIT,
    DPLL_LOCKED,
    INV_RLY_CLOSE,
    DELAY,
    TIMEOUT,
    WAIT_FOR_REINIT,
    ISLAND_MODE,
    ANTY_ISLANDING,
    C_RAMP_BEGIN,
    C_RAM_END
}SM_STATE_t; 

typedef enum
{
    NONE,
    CRITICAL,
    INITIAL,
    NO_DPLL_LOCK,
    NO_GRID,
    OVERCURRENT,
    INV_VOLTAGE,
    MID_VOLTAGE,
    GRID_VOLTAGE,
    TIMEOUT_ERROR
}SM_ERROR_t;

typedef struct Device_info_tag
{
    uint16_t HW_INFO;
	uint16_t FW_VERSION;
    uint16_t FW_DATE; 
	uint16_t FW_MONTH_DAY;
    
}Device_info_t;


typedef struct Calib_info_tag
{
    uint16_t L1_I_INV_RAW_ERR;	//R	INT	L1_I_INV_RAW_ERR value in ADC steps units	
    uint16_t L1_I_INV_UNIT_ERR;	//R	INT	L1_I_INV_ERR value in 1/32 A units	
    uint16_t L2_I_INV_RAW_ERR;	//R	INT	L2_I_INV_ERR value in ADC steps units	
    uint16_t L2_I_INV_UNIT_ERR;	//R	INT	L2_I_INV_ERR value in 1/32 A units	
    uint16_t L3_I_INV_RAW_ERR;	//R	INT	L3_I_INV_ERR value in ADC steps units	
    uint16_t L3_I_INV_UNIT_ERR;	//R	INT	L3_I_INV_ERR value in 1/32 A units	
    uint16_t L1_I_GRID_RAW_ERR;  //R	INT	L1_I_GRID_ERR value in ADC steps units	
    uint16_t L1_I_GRID_UNIT_ERR;	//R	INT	L1_I_GRID_ERR value in 1/32 A units	
    uint16_t L2_I_GRID_RAW_ERR;  //R	INT	L2_I_GRID_ERR value in ADC steps units	
    uint16_t L2_I_GRID_UNIT_ERR;	//R	INT	L2_I_GRID_ERR value in 1/32 A units	
    uint16_t L3_I_GRID_RAW_ERR;	//R	INT	L3_I_GRID_ERR value in ADC steps units	
    uint16_t L3_I_GRID_UNIT_ERR;	//R	INT	L3_I_GRID_ERR value in 1/32 A units	
    uint16_t L1_U_INV_RAW_ERR;   //R	INT	L1_U_INV_ERR value in ADC steps units	
    uint16_t L1_U_INV_UNIT_ERR;	//R	INT	L1_U_INV_ERR value in 1/32 V units	
    uint16_t L2_U_INV_RAW_ERR;	//R	INT	L2_U_INV_ERR value in ADC steps units	
    uint16_t L2_U_INV_UNIT_ERR;	//R	INT	L2_U_INV_ERR value in 1/32 V units	
    uint16_t L3_U_INV_RAW_ERR;	//R	INT	L3_U_INV_ERR value in ADC steps units	
    uint16_t L3_U_INV_UNIT_ERR;	//R	INT	L3_U_INV_ERR value in 1/32 V units	
    uint16_t L1_U_MID_RAW_ERR;	//R	INT	L1_U_MID_ERR value in ADC steps units	
    uint16_t L1_U_MID_UNIT_ERR;	//R	INT	L1_U_MID_ERR value in 1/32 V units	
    uint16_t L2_U_MID_RAW_ERR;	//R	INT	L2_U_MID_ERR value in ADC steps units	
    uint16_t L2_U_MID_UNIT_ERR;	//R	INT	L2_U_MID_ERR value in 1/32 V units	
    uint16_t L3_U_MID_RAW_ERR;   //R	INT	L3_U_MID_ERR value in ADC steps units	
    uint16_t L3_U_MID_UNIT_ERR;	//R	INT	L3_U_MID_ERR value in 1/32 V units	
    uint16_t L1_U_GRID_RAW_ERR; 	//R	INT	L1_U_GRID_ERR value in ADC steps units	
    uint16_t L1_U_GRID_UNIT_ERR;	//R	INT	L1_U_GRID_ERR value in 1/32 V units	
    uint16_t L2_U_GRID_RAW_ERR;	//R	INT	L2_U_GRID_ERR value in ADC steps units	
    uint16_t L2_U_GRID_UNIT_ERR;	//R	INT	L2_U_GRID_ERR value in 1/32 V units	
    uint16_t L3_U_GRID_RAW_ERR;	//R	INT	L3_U_GRID_ERR value in ADC steps units	
    uint16_t L3_U_GRID_UNIT_ERR; //R	INT	L3_U_GRID_ERR value in 1/32 V units	

}Calib_info_t;

typedef struct Discrete_Inputs_tag
{
    bool OCP_OC_L1_INV;
    bool OCP_OC_L2_INV;
    bool OCP_OC_L3_INV;
    bool OCP_OC_L1_GRID;
    bool OCP_OC_L2_GRID;
    bool OCP_OC_L3_GRID;

}Discrete_Inputs_t;

typedef struct Relay_Output_tag
{
bool RELAY_INV_PHASE;
bool RELAY_INV_NEUTRAL;
bool RELAY_GRID_PHASE;
bool RELAY_GRID_NEUTRAL;


}Relay_Output_t;
typedef struct System_Status_tag
{
bool SYS_RELOADED;
bool SYS_SHUTDOWN;
bool REC_DATA_READY;
bool REC_DATA_REREAD;
bool SM_REC_STATE;


}System_Status_t;


typedef struct Reset_Source_tag
{
bool RST_POR;
bool RST_BOR;
bool RST_IDLE;
bool RST_SLEEP;
bool RST_WDTO;
bool RST_SWDTEN;
bool RST_SWR;
bool RST_EXTR;
bool RST_VREGS;
bool RST_CM;
//bool DummyOnAddress10;
bool RST_VREGSF;
//bool DummyOnAddress12;
//bool DummyOnAddress13;
bool RST_IOPUWR;
bool RST_TRAPR;

}Reset_Source_t;

typedef struct Adc_Reading_tag
{
    uint16_t    L1_U_INV_RAW;
    int16_t		L1_U_INV_MEAN;
    int16_t		L1_U_INV_PKPK;
    int16_t		L1_U_INV_RMS;
    uint16_t	L1_I_INV_RAW;
    int16_t 	L1_I_INV_MEAN;
    int16_t 	L1_I_INV_PKPK;
    int16_t 	L1_I_INV_RMS;
    uint16_t	L2_U_INV_RAW;
    int16_t 	L2_U_INV_MEAN;
    int16_t 	L2_U_INV_PKPK;
    int16_t 	L2_U_INV_RMS;
    uint16_t	L2_I_INV_RAW;
    int16_t 	L2_I_INV_MEAN;
    int16_t 	L2_I_INV_PKPK;
    int16_t 	L2_I_INV_RMS;
    uint16_t	L3_U_INV_RAW;
    int16_t 	L3_U_INV_MEAN;
    int16_t 	L3_U_INV_PKPK;
    int16_t 	L3_U_INV_RMS;
    uint16_t	L3_I_INV_RAW;
    int16_t 	L3_I_INV_MEAN;
    int16_t 	L3_I_INV_PKPK;
    int16_t 	L3_I_INV_RMS;
    uint16_t	L1_U_MID_RAW;
    int16_t 	L1_U_MID_MEAN;
    int16_t 	L1_U_MID_PKPK;
    int16_t 	L1_U_MID_RMS;
    uint16_t	L2_U_MID_RAW;
    int16_t 	L2_U_MID_MEAN;
    int16_t 	L2_U_MID_PKPK;
    int16_t 	L2_U_MID_RMS;
    uint16_t	L3_U_MID_RAW;
    int16_t 	L3_U_MID_MEAN;
    int16_t 	L3_U_MID_PKPK;
    int16_t 	L3_U_MID_RMS;
    uint16_t	L1_U_GRID_RAW;
    int16_t 	L1_U_GRID_MEAN;
    int16_t 	L1_U_GRID_PKPK;
    int16_t 	L1_U_GRID_RMS;
    uint16_t	L1_I_GRID_RAW;
    int16_t 	L1_I_GRID_MEAN;
    int16_t 	L1_I_GRID_PKPK;
    int16_t 	L1_I_GRID_RMS;
    uint16_t	L2_U_GRID_RAW;
    int16_t 	L2_U_GRID_MEAN;
    int16_t 	L2_U_GRID_PKPK;
    int16_t 	L2_U_GRID_RMS;
    uint16_t	L2_I_GRID_RAW;
    int16_t 	L2_I_GRID_MEAN;
    int16_t 	L2_I_GRID_PKPK;
    int16_t 	L2_I_GRID_RMS;
    uint16_t	L3_U_GRID_RAW;
    int16_t 	L3_U_GRID_MEAN;
    int16_t 	L3_U_GRID_PKPK;
    int16_t 	L3_U_GRID_RMS;
    uint16_t	L3_I_GRID_RAW;
    int16_t 	L3_I_GRID_MEAN;
    int16_t 	L3_I_GRID_PKPK;
    int16_t 	L3_I_GRID_RMS;
    uint16_t	P_U_DC_RAW;
    uint16_t	P_U_DC_MEAN;
    uint16_t	P_U_DC_PKPK;
    uint16_t	P_U_DC_RMS;
    uint16_t	N_U_DC_RAW;
    uint16_t	N_U_DC_MEAN;
    uint16_t	N_U_DC_PKPK;
    uint16_t	N_U_DC_RMS;
    uint16_t	T1_RAW;
    int16_t 	T1_CELSIUS;
    uint64_t 	T1_RESISTANCE;
    uint16_t	T2_RAW;
    int16_t 	T2_CELSIUS;
    uint64_t 	T2_RESISTANCE;
    uint16_t	T3_RAW;
    int16_t 	T3_CELSIUS;
    uint64_t 	T3_RESISTANCE;
}Adc_Reading_t;

typedef struct Mode_Reading_tag
{
    uint64_t POWERUP_COUNTER;
    uint16_t SYSTEM_MODE;
  
}Mode_Reading_t;

typedef struct DDS_Reading_tag
{

    uint16_t WAVES_FREQ;
    int16_t SHIFT_PHASE_CH2;
    int16_t SHIFT_PHASE_CH3;
    uint16_t GAIN_CH1;
    uint16_t GAIN_CH2;
    uint16_t GAIN_CH3;

}DDS_Reading_t;


typedef struct ITRIP_Reading_tag
{
    uint16_t ITRIP_INV_UPPER;
    uint16_t ITRIP_GRID_LOWER;
    
}ITRIP_Reading_t;


typedef struct DPLL_Reading_tag
{
    int16_t ID_SET;
    int16_t IQ_SET;
    int16_t VD_SET; 
    int16_t VQ_SET;
    int16_t OMEGA_L;

}DPLL_Reading_t;
/*
typedef struct SM_Reading_tag
{
uint8_t SM_REC_STATE;
uint16_t SM_STATE_ERROR;
uint16_t SM_TIMESTAMP_MS;
uint64_t SM_TIMESTAMP_S;

}SM_Reading_t;
*/



#endif /* MODBUS_DATA_STORAGE_H */

