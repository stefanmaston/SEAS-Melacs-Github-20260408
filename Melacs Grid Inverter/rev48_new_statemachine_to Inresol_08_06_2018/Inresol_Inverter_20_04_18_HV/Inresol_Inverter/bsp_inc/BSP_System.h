#ifndef __BSP_SYSTEM__
#define __BSP_SYSTEM__

extern volatile uint16_t BSP_System_Reset_State;

void BSP_System_PLL_Main_Setup(void);
void BSP_System_OSC_Switch(void);
void BSP_System_PLL_Aux_Setup(void);
void BSP_System_RST_Read(void);

void BSP_System_WDT_Disable(void);

void BSP_System_SW_Reset(void);

#endif	// __BSP_SYSTEM__
