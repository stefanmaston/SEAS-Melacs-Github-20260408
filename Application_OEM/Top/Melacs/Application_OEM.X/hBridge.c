#define _SUPPRESS_PLIB_WARNING
#include "main.h"
#ifdef _HBRIDGE_FUNC_

#include <stdio.h>
#include "speedControl.h"
#include "pinDefines.h"
#include "onBoardADC.h"
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include <time.h>
#include "timeDifference.h"
#include "analogSensor10bit.h"
#include "analogPhysical.h"  //needed for float defination, don't remove this header file

#define SWITCH_ON_SURGE_TIME 2

void hBridgeInit()
{

    //M1DIS to enable HBridge
    TRIS_M1DIS = 0;
    LAT_M1DIS = 0;

    //Set M1AHI as output
    TRIS_M1AHI = 0;
    LAT_M1AHI = 0;

    //Set M1ALI as output and to low
    TRIS_M1ALI = 0;
    LAT_M1ALI = 0;

    //Set M1AHI as output and to low
    TRIS_M1BHI = 0;
    LAT_M1BHI = 0;

    //Set M1ALI as output and to low
    TRIS_M1BLI = 0;
    LAT_M1BLI = 1;

    //M2DIS to enable HBridge
    TRIS_M2DIS = 0;
    LAT_M2DIS = 0;

    //Set M2BHI as output
    TRIS_M2AHI = 0;
    LAT_M2AHI = 0;

    //Set M2BLI as output and to low
    TRIS_M2ALI = 0;
    LAT_M2ALI = 0;

    //Set M2BHI as output and to low
    TRIS_M2BHI = 0;
    LAT_M2BHI = 0;

    //Set M2BLI as output and to low
    TRIS_M2BLI = 0;
    LAT_M2BLI = 1;    
    
    OpenOC1( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenOC3( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenTimer2( T2_ON | T2_PS_1_1 | T2_SOURCE_INT, 0x2FFF);
}

extern struct timespec currentTime;
struct timespec currentStampJP18;
struct timespec currentStampJP19;
bool changeSurgeCurrentJP18 = false;
bool changeSurgeCurrentJP19 = false;

#if 0
void setJP18volt(float voltage)
{
    int equivalentPWMValue;
    equivalentPWMValue = (voltage * 0x2FFF)/12.0;
    SetDCOC1PWM(equivalentPWMValue);    
}

void setJP19volt(float voltage)
{
    int equivalentPWMValue;
    equivalentPWMValue = (voltage * 0x2FFF)/12.0;
    SetDCOC3PWM(equivalentPWMValue);   
}
#endif

float M1CUR;
float M2CUR;
bool isJP18currentOkay()
{
    struct timespec result;

    timespec_diff(&currentStampJP18, &currentTime, &result);

    if((result.tv_sec < SWITCH_ON_SURGE_TIME) && (changeSurgeCurrentJP18))
    {
        //ignore the current for the first 2 seconds
        return true;
    }
    else
    {
        changeSurgeCurrentJP18 = false;
        M1CUR = convertHexToVolt(read_analog_M1CUR());
        if(M1CUR < 0.1) //0.4 volt on M1CUR belongs to 8 Ampere, in top to bottom direction
            return false;
        else if(M1CUR > 3.1) //2.7 volt on M1CUR belongs to 8 Ampere, in bottom to top direction
            return false;
        else
            return true;
    }
}



void setJP18volt_CurrentLimiter_(float voltage, int direction)
{
    static float prevVoltage = 0;
    int equivalentPWMValue; 

    equivalentPWMValue = (voltage * 0x2FFF)/12.0;
    if(voltage - prevVoltage > 0.5)
    {
        currentStampJP18.tv_sec = currentTime.tv_sec;
        currentStampJP18.tv_nsec = currentTime.tv_nsec;    
        changeSurgeCurrentJP18 = true;
    }
    
    if(0 == direction)
    {
        LAT_M1ALI = 0;            
        LAT_M1BLI = 1;
        LAT_M1BHI = 0;
        SetDCOC2PWM(0);             
        SetDCOC1PWM(equivalentPWMValue);               
    }
    else
    {
        LAT_M1ALI = 1;            
        LAT_M1BLI = 0;  
        LAT_M1AHI = 0;
        SetDCOC1PWM(0);                 
        SetDCOC2PWM(equivalentPWMValue);            
    }
            
    prevVoltage = voltage; 
}



void setJP18volt_CurrentLimiter(float voltage, int direction)
{
    static float jp18_voltage = 0;    
    static int jp18_direction = 0;    
    
    if(jp18_direction == direction)
    {
        if(voltage > (jp18_voltage + 0.2))
        {
            jp18_voltage = jp18_voltage + 0.2;
        }
        else
        {
            jp18_voltage = voltage;
        }           
    }
    else
    {
        if(0 == jp18_voltage)
        {
            if(voltage > (jp18_voltage + 0.2))
            {
                jp18_voltage = jp18_voltage + 0.2;
            }
            else
            {
                jp18_voltage = voltage;
            }               
        }
        else
        {
            jp18_voltage = 0;
        }
        
        jp18_direction = direction;
    }
    
    setJP18volt_CurrentLimiter_(jp18_voltage, jp18_direction);
}

bool isJP19currentOkay()
{
    struct timespec result;
    timespec_diff(&currentStampJP19, &currentTime, &result);

    if((result.tv_sec < SWITCH_ON_SURGE_TIME) && (1 == changeSurgeCurrentJP19))
    {
        //ignore the current for the first 2 seconds
        return true;
    }
    else
    {
        changeSurgeCurrentJP19 = false;
        M2CUR = convertHexToVolt(read_analog_M2CUR());
        if(M2CUR < 0.1) //0.4 volt on M1CUR belongs to 8 Ampere, in top to bottom direction
            return false;
        else if(M2CUR > 3.1) //2.7 volt on M1CUR belongs to 8 Ampere, in bottom to top direction
            return false;
        else
            return true;
    }
}

void setJP19volt_CurrentLimiter_(float voltage,int direction)
{
    static float prevVoltage = 0;
    int equivalentPWMValue;     
    equivalentPWMValue = (voltage * 0x2FFF)/12.0;
    if(voltage - prevVoltage > 0.5)
    {
        currentStampJP19.tv_sec = currentTime.tv_sec;
        currentStampJP19.tv_nsec = currentTime.tv_nsec;  
        changeSurgeCurrentJP19 = true;
    }

    if(0 == direction)
    {
        LAT_M2ALI = 0;            
        LAT_M2BLI = 1;  
        LAT_M2BHI = 0;
        SetDCOC4PWM(0);               
        SetDCOC3PWM(equivalentPWMValue); 
    }
    else
    {
        LAT_M2ALI = 1;            
        LAT_M2BLI = 0; 
        LAT_M2AHI = 0;
        SetDCOC3PWM(0);
        SetDCOC4PWM(equivalentPWMValue);            
    }    

    prevVoltage = voltage;
}



void setJP19volt_CurrentLimiter(float voltage, int direction)
{

    static float jp19_voltage = 0;
    static int jp19_direction = 0;    
    
    if(jp19_direction == direction)
    {
        if(voltage > (jp19_voltage + 0.2))
        {
            jp19_voltage = jp19_voltage + 0.2;
        }
        else
        {
            jp19_voltage = voltage;
        }           
    }
    else
    {
        if(0 == jp19_voltage)
        {
            if(voltage > (jp19_voltage + 0.2))
            {
                jp19_voltage = jp19_voltage + 0.2;
            }
            else
            {
                jp19_voltage = voltage;
            }               
        }
        else
        {
            jp19_voltage = 0;
        }
        
        jp19_direction = direction;
    }
    
    setJP19volt_CurrentLimiter_(jp19_voltage, jp19_direction);
}

#endif