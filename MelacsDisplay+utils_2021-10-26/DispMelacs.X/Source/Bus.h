/******************************************************************************
 * The slave-portion of the bus protocol between the Melacs unit and one or two
 * displays
 ******************************************************************************/
#ifndef _BUS_H
#define _BUS_H

void Bus_Init(void);
unsigned char Bus_Get(void);
void Bus_Interrupt(void);

// Enable the attention interrupt in order to actually start communicating
#define Bus_Activate()       ((void) (INTCON3bits.INT3IE = 1))
// Check if there is data left to read in the stream
#define Bus_Ready()          (_Bus_Tail != _Bus_Head)
// Temporarily stop communicating while a response is formed
#define Bus_LockResponse()   ((void) (INTCONbits.GIEL = 0))
#define Bus_UnlockResponse() ((void) (INTCONbits.GIEL = 1))
// Check whether this is the primary or secondary slave node
#define Bus_IsPrimary()      (!BUS_ACK1_TRIS)
#define Bus_IsSecondary()    (!BUS_ACK2_TRIS)

// An externally defined buffer is used to store the current response, which
// is sent asynchronously whenever the master asks for it
/* extern volatile union Bus_Response Bus_Response; */
extern volatile signed char Bus_ResponseLen;

extern volatile unsigned char _Bus_Head;
extern volatile unsigned char _Bus_Tail;

#endif
