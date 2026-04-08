#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _ALARM_FUNC_

#include "alarmCode.h"

//Implement Data Structure Instead
//http://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c

char * getErrorString(int errorCode)
{
    if(ERROR_IN_COMBUSTION == errorCode)
    {
        return "Error: In Combustion   ";
    }
    else if(ERROR_OVERCURRENT_RADIATORFAN == errorCode)
    {
        return "Overcurrent RadiatorFan";
    }  
    else if(ERROR_OVERCURRENT_BURNERFAN == errorCode)
    {
        return "Overcurrent BurnerFan  ";
    }  
    else if(UNUSUAL_ENGINE_TEMPERATURE == errorCode)
    {
        return "Unusual Engine Temp    ";
    }   
    else if(UNUSUAL_HEATER_TEMPERATURE == errorCode)
    {
        return "Unusual Heater Temp    ";
    }      
    else if(UNUSUAL_PRESSURE_VALUE == errorCode)
    {
        return "Unusual Pressure Value ";
    }        
    else if(ERROR_GAS_COMBUSTION == errorCode)
    {
        return "Error Gas Combustion   ";
    }     
    else if(ALARM_A2 == errorCode)
    {
        return "ALARM : A2             ";
    }           
    else if(ALARM_A3 == errorCode)
    {
        return "ALARM : A3             ";
    }     
    else if(ALARM_A4 == errorCode)
    {
        return "ALARM : A4             ";
    }     
    else if(ALARM_A5 == errorCode)
    {
        return "ALARM : A5             ";
    }    
    else if(ALARM_A6 == errorCode)
    {
        return "ALARM : A6             ";
    }     
    else if(ALARM_A7 == errorCode)
    {
        return "ALARM : A7             ";
    }     
    else if(ALARM_A8 == errorCode)
    {
        return "ALARM : A8             ";
    }    
    else if(ALARM_A9 == errorCode)
    {
        return "ALARM : A9             ";
    }                                        
    else                
    {
        return NULL;
    }
}


#endif
