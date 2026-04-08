#include "configurations.h"
#include "main.h"

// Configuration Bit settings
// SYSCLK = 72 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 36 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#if defined(NO_PRI_OSC)
#pragma config FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
//#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2
#pragma config POSCMOD = OFF, FNOSC = FRCPLL, FPBDIV = DIV_2
#pragma config FSOSCEN = OFF
#define _USB_
#elif defined(EIGHT_MHZ_OSC)
#pragma config FPLLODIV = DIV_1, FSOSCEN = OFF, FPLLMUL = MUL_18
#prragma config FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_2
#pragma config POSCMOD = XT, FNOSC = PRIPLL, CP = OFF
#ifdef _USB_
#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF   // external PHY in RMII/alternate configuration
#pragma config UPLLEN = ON, UPLLIDIV = DIV_2
#endif
#elif defined(SIXTEEN_MHZ_OSC)
#pragma config FPLLODIV = DIV_1, FSOSCEN = OFF, FPLLMUL = MUL_18
#pragma config FPLLIDIV = DIV_4, FWDTEN = OFF, FPBDIV = DIV_2
#pragma config POSCMOD = HS, FNOSC = PRIPLL, CP = OFF

#ifdef _USB_
#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF   // external PHY in RMII/alternate configuration
#pragma config UPLLEN = ON, UPLLIDIV = DIV_4
#endif
#endif

#ifdef _ETHERNET_
/********************************************************************
 * Ethernet MII Enable bit [FMIIEN]
 * 
 * ON   - MII enabled, RMII disabled  
 * OFF  - MII disabled, RMII enabled  
 ********************************************************************/
#pragma config FMIIEN = OFF


/********************************************************************
 * Ethernet IO Pin Selection bit [FETHIO]
 * 
 * ON   - Default Ethernet IO Pins   
 * OFF  - Alternate Ethernet IO Pins  
 ********************************************************************/
#pragma config FETHIO = OFF

#endif