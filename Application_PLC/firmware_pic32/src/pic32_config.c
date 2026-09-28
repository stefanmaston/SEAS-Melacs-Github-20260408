#include <xc.h>

/* 16 MHz kristall. SYSCLK = 16/4*18 = 72 MHz. PBCLK = 36 MHz. */

#pragma config FPLLIDIV = DIV_4
#pragma config FPLLMUL = MUL_18
#pragma config FPLLODIV = DIV_1
#pragma config UPLLIDIV = DIV_4
#pragma config UPLLEN = ON

#pragma config FNOSC = PRIPLL
#pragma config POSCMOD = HS
#pragma config FSOSCEN = OFF
#pragma config IESO = OFF
#pragma config OSCIOFNC = OFF
#pragma config FPBDIV = DIV_2
#pragma config FCKSM = CSECME
#pragma config FWDTEN = OFF
#pragma config WDTPS = PS1048576

#pragma config DEBUG = OFF
#pragma config ICESEL = ICS_PGx2
#pragma config CP = OFF
#pragma config BWP = OFF
#pragma config PWP = OFF

#pragma config FMIIEN = OFF
#pragma config FETHIO = OFF
#pragma config FUSBIDIO = OFF
#pragma config FVBUSONIO = OFF
