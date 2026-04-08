/*
 *  File name: BSP_PWM.c
 *
 *  Description: Board Support Package function implementations for PWM processing
 *
 *  Author: Future Electronics
 *
 */

#include <p33EP128GS706.h>

#include "global_includes.h"

static volatile uint16_t	BSP_PWM_Channel_1_Range;
static volatile uint16_t	BSP_PWM_Channel_1_Offset;
static volatile uint16_t	BSP_PWM_Channel_2_Range;
static volatile uint16_t	BSP_PWM_Channel_2_Offset;
static volatile uint16_t	BSP_PWM_Channel_3_Range;
static volatile uint16_t	BSP_PWM_Channel_3_Offset;
static volatile uint16_t	BSP_PWM_Channel_4_Range;
static volatile uint16_t	BSP_PWM_Channel_4_Offset;
static volatile uint16_t	BSP_PWM_Channel_5_Range;
static volatile uint16_t	BSP_PWM_Channel_5_Offset;

volatile uint8_t			BSP_PWM_Trigger_Sync;

void BSP_PWM_Core_Enable(void)
{
	PTCONbits.PTEN = 1;			// Enable the PWM module
}

void BSP_PWM_Core_Disable(void)
{
	PTCONbits.PTEN = 0;			// Disable the PWM module
}

void BSP_PWM_Core_Init(void)
{
	BSP_PWM_Core_Disable();		// Disable the PWM module during configuration
	PTCONbits.PTSIDL = 0;		// PWM time base runs in CPU Idle mode
	PTCONbits.SEIEN = 0;		// Special Event Interrupt is disabled
	PTCONbits.EIPU = 0;			// Active Period register updates occur on PWM cycle boundaries
	PTCONbits.SYNCPOL = 0;		// SYNCIx/SYNCO is active-high
	PTCONbits.SYNCOEN = 0;		// SYNCO output is disabled
	PTCONbits.SYNCEN = 0;		// External synchronization of primary time base is disabled
	PTCONbits.SYNCSRC = 0;		// Primary Time Base Sync Source
	PTCONbits.SEVTPS = 0;		// Primary Special Event Trigger Output Postscaler = 1:1
	
	STCONbits.SEIEN = 0;		// Special Event Interrupt is disabled
	STCONbits.EIPU = 0;			// Active Period register updates occur on PWM cycle boundaries
	STCONbits.SYNCPOL = 0;		// SYNCIx/SYNCO is active-high
	STCONbits.SYNCOEN = 0;		// SYNCO output is disabled
	STCONbits.SYNCEN = 0;		// External synchronization of primary time base is disabled
	STCONbits.SYNCSRC = 0;		// Secondary Time Base Sync Source
	STCONbits.SEVTPS = 0;		// Secondary Special Event Trigger Output Postscaler = 1:1
	
	BSP_PWM_Trigger_Sync = 0;
}

static void BSP_PWM_Channel_1_Update_Range_and_Offset(void)
{
#if BSP_SETTINGS_PWM_MARGIN == 2
	BSP_PWM_Channel_1_Offset = DTR1 + DTR1;
#if (BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_1_Range = PTPER - (BSP_PWM_Channel_1_Offset + ALTDTR1 + ALTDTR1);
#else	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_1_Range = STPER - (BSP_PWM_Channel_1_Offset + ALTDTR1 + ALTDTR1);
#endif	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT
#elif BSP_SETTINGS_PWM_MARGIN == 1
	BSP_PWM_Channel_1_Offset = DTR1;
#if (BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_1_Range = PTPER - (BSP_PWM_Channel_1_Offset + ALTDTR1);
#else	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_1_Range = STPER - (BSP_PWM_Channel_1_Offset + ALTDTR1);
#endif	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT
#elif BSP_SETTINGS_PWM_MARGIN == 0
	BSP_PWM_Channel_1_Offset = 0;
#if (BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_1_Range = PTPER - BSP_PWM_Channel_1_Offset;
#else	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_1_Range = STPER - BSP_PWM_Channel_1_Offset;
#endif	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT
#else	// BSP_SETTINGS_PWM_MARGIN
#error	Please setup correctly BSP_SETTINGS_PWM_MARGIN
#endif	// BSP_SETTINGS_PWM_MARGIN
}

static void BSP_PWM_Channel_2_Update_Range_and_Offset(void)
{
#if BSP_SETTINGS_PWM_MARGIN == 2
	BSP_PWM_Channel_2_Offset = DTR2 + DTR2;
#if (BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_2_Range = PTPER - (BSP_PWM_Channel_2_Offset + ALTDTR2 + ALTDTR2);
#else	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_2_Range = STPER - (BSP_PWM_Channel_2_Offset + ALTDTR2 + ALTDTR2);
#endif	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT
#elif BSP_SETTINGS_PWM_MARGIN == 1
	BSP_PWM_Channel_2_Offset = DTR2;
#if (BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_2_Range = PTPER - (BSP_PWM_Channel_2_Offset + ALTDTR2);
#else	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_2_Range = STPER - (BSP_PWM_Channel_2_Offset + ALTDTR2);
#endif	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT
#elif BSP_SETTINGS_PWM_MARGIN == 0
	BSP_PWM_Channel_2_Offset = 0;
#if (BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_2_Range = PTPER - BSP_PWM_Channel_2_Offset;
#else	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_2_Range = STPER - BSP_PWM_Channel_2_Offset;
#endif	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT
#else	// BSP_SETTINGS_PWM_MARGIN
#error	Please setup correctly BSP_SETTINGS_PWM_MARGIN
#endif	// BSP_SETTINGS_PWM_MARGIN
}

static void BSP_PWM_Channel_3_Update_Range_and_Offset(void)
{
#if BSP_SETTINGS_PWM_MARGIN == 2
	BSP_PWM_Channel_3_Offset = DTR3 + DTR3;
#if (BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_3_Range = PTPER - (BSP_PWM_Channel_3_Offset + ALTDTR3 + ALTDTR3);
#else	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_3_Range = STPER - (BSP_PWM_Channel_3_Offset + ALTDTR3 + ALTDTR3);
#endif	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT
#elif BSP_SETTINGS_PWM_MARGIN == 1
	BSP_PWM_Channel_3_Offset = DTR3;
#if (BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_3_Range = PTPER - (BSP_PWM_Channel_3_Offset + ALTDTR3);
#else	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_3_Range = STPER - (BSP_PWM_Channel_3_Offset + ALTDTR3);
#endif	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT
#elif BSP_SETTINGS_PWM_MARGIN == 0
	BSP_PWM_Channel_3_Offset = 0;
#if (BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_3_Range = PTPER - BSP_PWM_Channel_3_Offset;
#else	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_3_Range = STPER - BSP_PWM_Channel_3_Offset;
#endif	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT
#else	// BSP_SETTINGS_PWM_MARGIN
#error	Please setup correctly BSP_SETTINGS_PWM_MARGIN
#endif	// BSP_SETTINGS_PWM_MARGIN
}

static void BSP_PWM_Channel_4_Update_Range_and_Offset(void)
{
	BSP_PWM_Channel_4_Offset = DTR4 + DTR4;
#if (BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_4_Range = PTPER - (BSP_PWM_Channel_4_Offset + ALTDTR4 + ALTDTR4);
#else	// BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_4_Range = STPER - (BSP_PWM_Channel_4_Offset + ALTDTR4 + ALTDTR4);
#endif	// BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT
}

static void BSP_PWM_Channel_5_Update_Range_and_Offset(void)
{
	BSP_PWM_Channel_5_Offset = DTR5 + DTR5;
#if (BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
	BSP_PWM_Channel_5_Range = PTPER - (BSP_PWM_Channel_5_Offset + ALTDTR5 + ALTDTR5);
#else	// BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
	BSP_PWM_Channel_5_Range = STPER - (BSP_PWM_Channel_5_Offset + ALTDTR5 + ALTDTR5);
#endif	// BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT
}

void BSP_PWM_Set_TimeBase(unsigned char TimeBase_Source, unsigned long Freq_Hz)
{
	if(TimeBase_Source == BSP_PWM_MASTER_TIME_BASE_PRIMARY) {
		PTCON2bits.PCLKDIV = BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV - 1;		// PWM Clock = PLL/1 = 944MHz
		PTPER = (1000000000000LL / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * Freq_Hz)); // PTPER = ((1 / 16kHz) / 1.06ns) = 58962 - where 16kHz is the switching frequency 16960000
	} else {
		STCON2bits.PCLKDIV = BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV - 1;		// PWM Clock = PLL/1 = 944MHz
		STPER =  (1000000000000LL / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * Freq_Hz)); // STPER = ((1 / 250kHz) / 1.06ns) = 3774 - where 200kHz is the switching frequency 265000000
	}
	BSP_PWM_Channel_1_Update_Range_and_Offset();
	BSP_PWM_Channel_2_Update_Range_and_Offset();
	BSP_PWM_Channel_3_Update_Range_and_Offset();
	BSP_PWM_Channel_4_Update_Range_and_Offset();
	BSP_PWM_Channel_5_Update_Range_and_Offset();
}

void BSP_PWM_Channel_Init(char Channel, unsigned char Pins_Enable, unsigned char Pins_Polarity, unsigned char Pins_Mode, unsigned char Dead_Time_Mode)
{
	bool PinHighPWM;
	bool PinLowPWM;
	bool PinHighPolarity;
	bool PinLowPolarity;

	if(Pins_Enable & 0x02)
		PinHighPWM = true;
	else
		PinHighPWM = false;
	if(Pins_Enable & 0x01)
		PinLowPWM = true;
	else
		PinLowPWM = false;
	if(Pins_Polarity & 0x02)
		PinHighPolarity = false;
	else
		PinHighPolarity = true;
	if(Pins_Polarity & 0x01)
		PinLowPolarity = false;
	else
		PinLowPolarity = true;
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
			IOCON1bits.PENH = PinHighPWM;			// PWM1H pin is controlled by PWM or GPIO module
			IOCON1bits.PENL = PinLowPWM;			// PWM1L pin is controlled by PWM or GPIO module
			IOCON1bits.POLH = PinHighPolarity;		// PWM1H drive signal is active-high or active-low
			IOCON1bits.POLL = PinLowPolarity;		// PWM1L drive signal is active-high or active-low
			IOCON1bits.PMOD = Pins_Mode;			// PWM I/O pin pair is in the Complementary or True Independent mode
			IOCON1bits.OVRENH = 0;		// PWM generator provides data for PWMxH pin
			IOCON1bits.OVRENL = 0;		// PWM generator provides data for PWMxL pin
			IOCON1bits.OVRDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML
			IOCON1bits.FLTDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML

			PWMCON1bits.TRGIEN = 0;		// Trigger event interrupts are disabled
			PWMCON1bits.ITB = 0;		// PTPER register provides timing for this PWM generator. Select Primary Timebase mode.
			PWMCON1bits.MDCS = 0;		// PDCx and SDCx registers provide duty cycle information for this PWM generator
			PWMCON1bits.DTC = Dead_Time_Mode;	// Positive dead time or Disabled
			PWMCON1bits.MTBS = BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT;		//  Select Primary or Secondary Timebase mode.
			PWMCON1bits.CAM = 0;		//  Edge-Aligned mode.
			PWMCON1bits.XPRES = 0;		//  External pins do not affect the PWMx time base.
			PWMCON1bits.IUE = 0;		// Updates to the active PDCx registers are synchronized to the PWM time base

			FCLCON1bits.FLTMOD = 3;		// Fault input is disabled
			FCLCON1bits.CLMOD = 0;		// Current-Limit mode is disabled

			TRGCON1bits.TRGDIV = 0;		// Trigger interrupt generated once every PWM cycle
			TRGCON1bits.TRGSTRT = 0;	// Trigger generated after waiting 0 PWM cycles
			TRIG1 = 0;					// Trigger location - at the start of the PWM cycle

#if 0
			DTR1 = (uint32_t)BSP_PWM_CHANNEL_1_DEF_DEAD_TIME_RISING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;		// Apply Dead-Time at Rising Edge
			ALTDTR1 = (uint32_t)BSP_PWM_CHANNEL_1_DEF_DEAD_TIME_FALLING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;	// Apply Dead-Time at Falling Edge
#else
#if BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			DTR1 = (uint32_t)BSP_PWM_CHANNEL_1_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);			// Apply Dead-Time at Rising Edge
			ALTDTR1 = (uint32_t)BSP_PWM_CHANNEL_1_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);		// Apply Dead-Time at Falling Edge
#else
			DTR1 = (uint32_t)BSP_PWM_CHANNEL_1_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);		// Apply Dead-Time at Rising Edge
			ALTDTR1 = (uint32_t)BSP_PWM_CHANNEL_1_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);	// Apply Dead-Time at Falling Edge
#endif
#endif
			PDC1 = DTR1 + ALTDTR1;																					// Initial Pulse-Width = minimum Dead-Time required (DTR1 + ALTDTR1)
			SDC1 = PDC1;																							// Initial Pulse-Width = minimum Dead-Time required (DTR1 + ALTDTR1)
			BSP_PWM_Channel_1_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			IOCON2bits.PENH = PinHighPWM;			// PWM2H pin is controlled by PWM or GPIO module
			IOCON2bits.PENL = PinLowPWM;			// PWM2L pin is controlled by PWM or GPIO module
			IOCON2bits.POLH = PinHighPolarity;		// PWM2H drive signal is active-high or active-low
			IOCON2bits.POLL = PinLowPolarity;		// PWM2L drive signal is active-high or active-low
			IOCON2bits.PMOD = Pins_Mode;			// PWM I/O pin pair is in the Complementary or True Independent mode
			IOCON2bits.OVRENH = 0;		// Disable Override feature for PWMxH pin
			IOCON2bits.OVRENL = 0;		// Disable Override feature for PWMxL pin
			IOCON2bits.OVRDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML
			IOCON2bits.FLTDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML

			PWMCON2bits.TRGIEN = 0;		// Trigger event interrupts are disabled
			PWMCON2bits.ITB = 0;		// PTPER register provides timing for this PWM generator. Select Primary Timebase mode.
			PWMCON2bits.MDCS = 0;		// PDCx and SDCx registers provide duty cycle information for this PWM generator
			PWMCON2bits.DTC = Dead_Time_Mode;	// Positive dead time or Disabled
			PWMCON2bits.MTBS = BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT;		//  Select Primary or Secondary Timebase mode.
			PWMCON2bits.CAM = 0;		//  Edge-Aligned mode.
			PWMCON2bits.XPRES = 0;		//  External pins do not affect the PWMx time base.
			PWMCON2bits.IUE = 0;		// Updates to the active PDCx registers are synchronized to the PWM time base

			FCLCON2bits.FLTMOD = 3;		// Fault input is disabled
			FCLCON2bits.CLMOD = 0;		// Current-Limit mode is disabled

			TRGCON2bits.TRGDIV = 0;		// Trigger interrupt generated once every PWM cycle
			TRGCON2bits.TRGSTRT = 0;	// Trigger generated after waiting 0 PWM cycles
			TRIG2 = 0;					// Trigger location - at the start of the PWM cycle

#if 0
			DTR2 = (uint32_t)BSP_PWM_CHANNEL_2_DEF_DEAD_TIME_RISING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;		// Apply Dead-Time at Rising Edge
			ALTDTR2 = (uint32_t)BSP_PWM_CHANNEL_2_DEF_DEAD_TIME_FALLING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;	// Apply Dead-Time at Falling Edge
#else
#if BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			DTR2 = (uint32_t)BSP_PWM_CHANNEL_2_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);			// Apply Dead-Time at Rising Edge
			ALTDTR2 = (uint32_t)BSP_PWM_CHANNEL_2_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);		// Apply Dead-Time at Falling Edge
#else
			DTR2 = (uint32_t)BSP_PWM_CHANNEL_2_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);		// Apply Dead-Time at Rising Edge
			ALTDTR2 = (uint32_t)BSP_PWM_CHANNEL_2_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);	// Apply Dead-Time at Falling Edge
#endif
#endif
			PDC2 = DTR2 + ALTDTR2;																					// Initial Pulse-Width = minimum Dead-Time required (DTR2 + ALTDTR2)
			SDC2 = PDC2;																							// Initial Pulse-Width = minimum Dead-Time required (DTR2 + ALTDTR2)
			BSP_PWM_Channel_2_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
			IOCON3bits.PENH = PinHighPWM;			// PWM3H pin is controlled by PWM or GPIO module
			IOCON3bits.PENL = PinLowPWM;			// PWM3L pin is controlled by PWM or GPIO module
			IOCON3bits.POLH = PinHighPolarity;		// PWM3H drive signal is active-high or active-low
			IOCON3bits.POLL = PinLowPolarity;		// PWM3L drive signal is active-high or active-low
			IOCON3bits.PMOD = Pins_Mode;			// PWM I/O pin pair is in the Complementary or True Independent mode
			IOCON3bits.OVRENH = 0;		// Disable Override feature for PWMxH pin
			IOCON3bits.OVRENL = 0;		// Disable Override feature for PWMxL pin
			IOCON3bits.OVRDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML
			IOCON3bits.FLTDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML

			PWMCON3bits.TRGIEN = 0;		// Trigger event interrupts are disabled
			PWMCON3bits.ITB = 0;		// PTPER register provides timing for this PWM generator.
			PWMCON3bits.MDCS = 0;		// PDCx and SDCx registers provide duty cycle information for this PWM generator
			PWMCON3bits.DTC = Dead_Time_Mode;	// Positive dead time or Disabled
			PWMCON3bits.MTBS = BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT;		//  Select Primary or Secondary Timebase mode.
			PWMCON3bits.CAM = 0;		//  Edge-Aligned mode.
			PWMCON3bits.XPRES = 0;		//  External pins do not affect the PWMx time base.
			PWMCON3bits.IUE = 0;		// Updates to the active PDCx registers are synchronized to the PWM time base

			FCLCON3bits.FLTMOD = 3;		// Fault input is disabled
			FCLCON3bits.CLMOD = 0;		// Current-Limit mode is disabled

			TRGCON3bits.TRGDIV = 0;		// Trigger interrupt generated once every PWM cycle
			TRGCON3bits.TRGSTRT = 0;	// Trigger generated after waiting 0 PWM cycles
			TRIG3 = 0;					// Trigger location - at the start of the PWM cycle

#if 0
			DTR3 = (uint32_t)BSP_PWM_CHANNEL_3_DEF_DEAD_TIME_RISING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;		// Apply Dead-Time at Rising Edge
			ALTDTR3 = (uint32_t)BSP_PWM_CHANNEL_3_DEF_DEAD_TIME_FALLING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;	// Apply Dead-Time at Falling Edge
#else
#if BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			DTR3 = (uint32_t)BSP_PWM_CHANNEL_3_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);			// Apply Dead-Time at Rising Edge
			ALTDTR3 = (uint32_t)BSP_PWM_CHANNEL_3_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);		// Apply Dead-Time at Falling Edge
#else
			DTR3 = (uint32_t)BSP_PWM_CHANNEL_3_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);		// Apply Dead-Time at Rising Edge
			ALTDTR3 = (uint32_t)BSP_PWM_CHANNEL_3_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);	// Apply Dead-Time at Falling Edge
#endif
#endif
			PDC3 = DTR3 + ALTDTR3;																					// Initial Pulse-Width = minimum Dead-Time required (DTR3 + ALTDTR3)
			SDC3 = PDC3;																							// Initial Pulse-Width = minimum Dead-Time required (DTR3 + ALTDTR3)
			BSP_PWM_Channel_3_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
			IOCON4bits.PENH = PinHighPWM;			// PWM4H pin is controlled by PWM or GPIO module
			IOCON4bits.PENL = PinLowPWM;			// PWM4L pin is controlled by PWM or GPIO module
			IOCON4bits.POLH = PinHighPolarity;		// PWM4H drive signal is active-high or active-low
			IOCON4bits.POLL = PinLowPolarity;		// PWM4L drive signal is active-high or active-low
			IOCON4bits.PMOD = Pins_Mode;			// PWM I/O pin pair is in the Complementary or True Independent mode
			IOCON4bits.OVRENH = 0;		// Disable Override feature for PWMxH pin
			IOCON4bits.OVRENL = 0;		// Disable Override feature for PWMxL pin
			IOCON4bits.OVRDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML
			IOCON4bits.FLTDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML

			PWMCON4bits.TRGIEN = 0;		// Trigger event interrupts are disabled
			PWMCON4bits.ITB = 0;		// PTPER register provides timing for this PWM generator. Select Primary Timebase mode.
			PWMCON4bits.MDCS = 0;		// PDCx and SDCx registers provide duty cycle information for this PWM generator
			PWMCON4bits.DTC = Dead_Time_Mode;	// Positive dead time or Disabled
			PWMCON4bits.MTBS = BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT;		//  Select Primary or Secondary Timebase mode.
			PWMCON4bits.CAM = 0;		//  Edge-Aligned mode.
			PWMCON4bits.XPRES = 0;		//  External pins do not affect the PWMx time base.
			PWMCON4bits.IUE = 0;		// Updates to the active PDCx registers are synchronized to the PWM time base

			FCLCON4bits.FLTMOD = 3;		// Fault input is disabled
			FCLCON4bits.CLMOD = 0;		// Current-Limit mode is disabled

			TRGCON4bits.TRGDIV = 0;		// Trigger interrupt generated once every PWM cycle
			TRGCON4bits.TRGSTRT = 0;	// Trigger generated after waiting 0 PWM cycles
			TRIG4 = 0;					// Trigger location - at the start of the PWM cycle

#if 0
			DTR4 = (uint32_t)BSP_PWM_CHANNEL_4_DEF_DEAD_TIME_RISING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;		// Apply Dead-Time at Rising Edge
			ALTDTR4 = (uint32_t)BSP_PWM_CHANNEL_4_DEF_DEAD_TIME_FALLING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;	// Apply Dead-Time at Falling Edge
#else
#if BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			DTR4 = (uint32_t)BSP_PWM_CHANNEL_4_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);			// Apply Dead-Time at Rising Edge
			ALTDTR4 = (uint32_t)BSP_PWM_CHANNEL_4_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);		// Apply Dead-Time at Falling Edge
#else
			DTR4 = (uint32_t)BSP_PWM_CHANNEL_4_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);		// Apply Dead-Time at Rising Edge
			ALTDTR4 = (uint32_t)BSP_PWM_CHANNEL_4_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);	// Apply Dead-Time at Falling Edge
#endif
#endif
			PDC4 = DTR4 + ALTDTR4;																					// Initial Pulse-Width = minimum Dead-Time required (DTR4 + ALTDTR4)
			SDC4 = PDC4;																							// Initial Pulse-Width = minimum Dead-Time required (DTR4 + ALTDTR4)
			BSP_PWM_Channel_4_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
			IOCON5bits.PENH = PinHighPWM;			// PWM5H pin is controlled by PWM or GPIO module
			IOCON5bits.PENL = PinLowPWM;			// PWM5L pin is controlled by PWM or GPIO module
			IOCON5bits.POLH = PinHighPolarity;		// PWM5H drive signal is active-high or active-low
			IOCON5bits.POLL = PinLowPolarity;		// PWM5L drive signal is active-high or active-low
			IOCON5bits.PMOD = Pins_Mode;			// PWM I/O pin pair is in the Complementary or True Independent mode
			IOCON5bits.OVRENH = 0;		// Disable Override feature for PWMxH pin
			IOCON5bits.OVRENL = 0;		// Disable Override feature for PWMxL pin
			IOCON5bits.OVRDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML
			IOCON5bits.FLTDAT = 0b00;	// Shut down PWM with override 0 on PWMH and PWML

			PWMCON5bits.TRGIEN = 0;		// Trigger event interrupts are disabled
			PWMCON5bits.ITB = 0;		// PTPER register provides timing for this PWM generator.
			PWMCON5bits.MDCS = 0;		// PDCx and SDCx registers provide duty cycle information for this PWM generator
			PWMCON5bits.DTC = Dead_Time_Mode;	// Positive dead time or Disabled
			PWMCON5bits.MTBS = BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT;		//  Select Primary or Secondary Timebase mode.
			PWMCON5bits.CAM = 0;		//  Edge-Aligned mode.
			PWMCON5bits.XPRES = 0;		//  External pins do not affect the PWMx time base.
			PWMCON5bits.IUE = 0;		// Updates to the active PDCx registers are synchronized to the PWM time base

			FCLCON5bits.FLTMOD = 3;		// Fault input is disabled
			FCLCON5bits.CLMOD = 0;		// Current-Limit mode is disabled

			TRGCON5bits.TRGDIV = 0;		// Trigger interrupt generated once every PWM cycle
			TRGCON5bits.TRGSTRT = 0;	// Trigger generated after waiting 0 PWM cycles
			TRIG5 = 0;					// Trigger location - at the start of the PWM cycle

#if 0
			DTR5 = (uint32_t)BSP_PWM_CHANNEL_5_DEF_DEAD_TIME_RISING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;		// Apply Dead-Time at Rising Edge
			ALTDTR5 = (uint32_t)BSP_PWM_CHANNEL_5_DEF_DEAD_TIME_FALLING_EDGE * 1000 / BSP_SETTINGS_PWM_CLOCK_PERIOD;	// Apply Dead-Time at Falling Edge
#else
#if BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			DTR5 = (uint32_t)BSP_PWM_CHANNEL_5_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);			// Apply Dead-Time at Rising Edge
			ALTDTR5 = (uint32_t)BSP_PWM_CHANNEL_5_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);		// Apply Dead-Time at Falling Edge
#else
			DTR5 = (uint32_t)BSP_PWM_CHANNEL_5_DEF_DEAD_TIME_RISING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);		// Apply Dead-Time at Rising Edge
			ALTDTR5 = (uint32_t)BSP_PWM_CHANNEL_5_DEF_DEAD_TIME_FALLING_EDGE * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);	// Apply Dead-Time at Falling Edge
#endif
#endif
			PDC5 = DTR5 + ALTDTR5;																					// Initial Pulse-Width = minimum Dead-Time required (DTR5 + ALTDTR5)
			SDC5 = PDC5;																							// Initial Pulse-Width = minimum Dead-Time required (DTR5 + ALTDTR5)
			BSP_PWM_Channel_5_Update_Range_and_Offset();
			break;
	}
}

// PWM Output Override Logic is used here to set both switches in inactive state
void BSP_PWM_Channel_Off_Outputs(char Channel, unsigned char Pins_Enable, unsigned char Pins_Polarity)
{
	bool PinHighPWM;
	bool PinLowPWM;
	uint8_t PinsHLOverride;

	if(Pins_Enable & 0x02)
		PinHighPWM = true;
	else
		PinHighPWM = false;
	if(Pins_Enable & 0x01)
		PinLowPWM = true;
	else
		PinLowPWM = false;
	PinsHLOverride = ~Pins_Polarity;
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
			IOCON1bits.OVRDAT = PinsHLOverride;		// Shut down PWM with override 0 or 1 on PWMH<1> and PWML<0>
			if(PinHighPWM)
				IOCON1bits.OVRENH = 1;				// Enable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON1bits.OVRENL = 1;				// Enable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			IOCON2bits.OVRDAT = PinsHLOverride;		// Shut down PWM with override 0 or 1 on PWMH<1> and PWML<0>
			if(PinHighPWM)
				IOCON2bits.OVRENH = 1;				// Enable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON2bits.OVRENL = 1;				// Enable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
			IOCON3bits.OVRDAT = PinsHLOverride;		// Shut down PWM with override 0 or 1 on PWMH<1> and PWML<0>
			if(PinHighPWM)
				IOCON3bits.OVRENH = 1;				// Enable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON3bits.OVRENL = 1;				// Enable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
			IOCON4bits.OVRDAT = PinsHLOverride;		// Shut down PWM with override 0 or 1 on PWMH<1> and PWML<0>
			if(PinHighPWM)
				IOCON4bits.OVRENH = 1;				// Enable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON4bits.OVRENL = 1;				// Enable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
			IOCON5bits.OVRDAT = PinsHLOverride;		// Shut down PWM with override 0 or 1 on PWMH<1> and PWML<0>
			if(PinHighPWM)
				IOCON5bits.OVRENH = 1;				// Enable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON5bits.OVRENL = 1;				// Enable Override feature for PWMxL pin
			break;
	}
}

// PWM Output Logic is used here to set both switches in normal active state
void BSP_PWM_Channel_On_Outputs(char Channel, unsigned char Pins_Enable)
{
	bool PinHighPWM;
	bool PinLowPWM;

	if(Pins_Enable & 0x02)
		PinHighPWM = true;
	else
		PinHighPWM = false;
	if(Pins_Enable & 0x01)
		PinLowPWM = true;
	else
		PinLowPWM = false;
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
			if(PinHighPWM)
				IOCON1bits.OVRENH = 0;				// Disable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON1bits.OVRENL = 0;				// Disable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			if(PinHighPWM)
				IOCON2bits.OVRENH = 0;				// Disable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON2bits.OVRENL = 0;				// Disable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
			if(PinHighPWM)
				IOCON3bits.OVRENH = 0;				// Disable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON3bits.OVRENL = 0;				// Disable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
			if(PinHighPWM)
				IOCON4bits.OVRENH = 0;				// Disable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON4bits.OVRENL = 0;				// Disable Override feature for PWMxL pin
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
			if(PinHighPWM)
				IOCON5bits.OVRENH = 0;				// Disable Override feature for PWMxH pin
			if(PinLowPWM)
				IOCON5bits.OVRENL = 0;				// Disable Override feature for PWMxL pin
			break;
	}
}

void BSP_PWM_Channel_Set_DeadTime(char Channel, unsigned long Rising_Edge_Dead_Time, unsigned long Falling_Edge_Dead_Time)
{
	unsigned long Rising_Edge_Dead_Time_REG;
	unsigned long Falling_Edge_Dead_Time_REG;
	
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
			if(Rising_Edge_Dead_Time < BSP_PWM_CHANNEL_1_MIN_DEAD_TIME_RISING_EDGE)
				Rising_Edge_Dead_Time = BSP_PWM_CHANNEL_1_MIN_DEAD_TIME_RISING_EDGE;
			if(Falling_Edge_Dead_Time < BSP_PWM_CHANNEL_1_MIN_DEAD_TIME_FALLING_EDGE)
				Falling_Edge_Dead_Time = BSP_PWM_CHANNEL_1_MIN_DEAD_TIME_FALLING_EDGE;
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			if(Rising_Edge_Dead_Time < BSP_PWM_CHANNEL_2_MIN_DEAD_TIME_RISING_EDGE)
				Rising_Edge_Dead_Time = BSP_PWM_CHANNEL_2_MIN_DEAD_TIME_RISING_EDGE;
			if(Falling_Edge_Dead_Time < BSP_PWM_CHANNEL_2_MIN_DEAD_TIME_FALLING_EDGE)
				Falling_Edge_Dead_Time = BSP_PWM_CHANNEL_2_MIN_DEAD_TIME_FALLING_EDGE;
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
			if(Rising_Edge_Dead_Time < BSP_PWM_CHANNEL_3_MIN_DEAD_TIME_RISING_EDGE)
				Rising_Edge_Dead_Time = BSP_PWM_CHANNEL_3_MIN_DEAD_TIME_RISING_EDGE;
			if(Falling_Edge_Dead_Time < BSP_PWM_CHANNEL_3_MIN_DEAD_TIME_FALLING_EDGE)
				Falling_Edge_Dead_Time = BSP_PWM_CHANNEL_3_MIN_DEAD_TIME_FALLING_EDGE;
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
			if(Rising_Edge_Dead_Time < BSP_PWM_CHANNEL_4_MIN_DEAD_TIME_RISING_EDGE)
				Rising_Edge_Dead_Time = BSP_PWM_CHANNEL_4_MIN_DEAD_TIME_RISING_EDGE;
			if(Falling_Edge_Dead_Time < BSP_PWM_CHANNEL_4_MIN_DEAD_TIME_FALLING_EDGE)
				Falling_Edge_Dead_Time = BSP_PWM_CHANNEL_4_MIN_DEAD_TIME_FALLING_EDGE;
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
			if(Rising_Edge_Dead_Time < BSP_PWM_CHANNEL_5_MIN_DEAD_TIME_RISING_EDGE)
				Rising_Edge_Dead_Time = BSP_PWM_CHANNEL_5_MIN_DEAD_TIME_RISING_EDGE;
			if(Falling_Edge_Dead_Time < BSP_PWM_CHANNEL_5_MIN_DEAD_TIME_FALLING_EDGE)
				Falling_Edge_Dead_Time = BSP_PWM_CHANNEL_5_MIN_DEAD_TIME_FALLING_EDGE;
			break;
	}
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
#if (BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			if(Rising_Edge_Dead_Time_REG > PTPER)
				Rising_Edge_Dead_Time_REG = PTPER;
			if(Falling_Edge_Dead_Time_REG > PTPER)
				Falling_Edge_Dead_Time_REG = PTPER;
#else	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			if(Rising_Edge_Dead_Time_REG > STPER)
				Rising_Edge_Dead_Time_REG = STPER;
			if(Falling_Edge_Dead_Time_REG > STPER)
				Falling_Edge_Dead_Time_REG = STPER;
#endif	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT
			DTR1 = Rising_Edge_Dead_Time_REG;		// Apply Dead-Time at Rising Edge
			ALTDTR1 = Falling_Edge_Dead_Time_REG;	// Apply Dead-Time at Falling Edge
//			PDC1 = DTR1 + ALTDTR1;					// Initial Pulse-Width = minimum Dead-Time required (DTR1 + ALTDTR1)
//			SDC1 = DTR1 + ALTDTR1;					// Initial Pulse-Width = minimum Dead-Time required (DTR1 + ALTDTR1)
			BSP_PWM_Channel_1_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
#if (BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			if(Rising_Edge_Dead_Time_REG > PTPER)
				Rising_Edge_Dead_Time_REG = PTPER;
			if(Falling_Edge_Dead_Time_REG > PTPER)
				Falling_Edge_Dead_Time_REG = PTPER;
#else	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			if(Rising_Edge_Dead_Time_REG > STPER)
				Rising_Edge_Dead_Time_REG = STPER;
			if(Falling_Edge_Dead_Time_REG > STPER)
				Falling_Edge_Dead_Time_REG = STPER;
#endif	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT
			DTR2 = Rising_Edge_Dead_Time_REG;		// Apply Dead-Time at Rising Edge
			ALTDTR2 = Falling_Edge_Dead_Time_REG;	// Apply Dead-Time at Falling Edge
//			PDC2 = DTR2 + ALTDTR2;					// Initial Pulse-Width = minimum Dead-Time required (DTR2 + ALTDTR2)
//			SDC2 = DTR2 + ALTDTR2;					// Initial Pulse-Width = minimum Dead-Time required (DTR2 + ALTDTR2)
			BSP_PWM_Channel_2_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
#if (BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			if(Rising_Edge_Dead_Time_REG > PTPER)
				Rising_Edge_Dead_Time_REG = PTPER;
			if(Falling_Edge_Dead_Time_REG > PTPER)
				Falling_Edge_Dead_Time_REG = PTPER;
#else	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			if(Rising_Edge_Dead_Time_REG > STPER)
				Rising_Edge_Dead_Time_REG = STPER;
			if(Falling_Edge_Dead_Time_REG > STPER)
				Falling_Edge_Dead_Time_REG = STPER;
#endif	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT
			DTR3 = Rising_Edge_Dead_Time_REG;		// Apply Dead-Time at Rising Edge
			ALTDTR3 = Falling_Edge_Dead_Time_REG;	// Apply Dead-Time at Falling Edge
//			PDC3 = DTR3 + ALTDTR3;					// Initial Pulse-Width = minimum Dead-Time required (DTR3 + ALTDTR3)
//			SDC3 = DTR3 + ALTDTR3;					// Initial Pulse-Width = minimum Dead-Time required (DTR3 + ALTDTR3)
			BSP_PWM_Channel_3_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
#if (BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			if(Rising_Edge_Dead_Time_REG > PTPER)
				Rising_Edge_Dead_Time_REG = PTPER;
			if(Falling_Edge_Dead_Time_REG > PTPER)
				Falling_Edge_Dead_Time_REG = PTPER;
#else	// BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			if(Rising_Edge_Dead_Time_REG > STPER)
				Rising_Edge_Dead_Time_REG = STPER;
			if(Falling_Edge_Dead_Time_REG > STPER)
				Falling_Edge_Dead_Time_REG = STPER;
#endif	// BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT
			DTR4 = Rising_Edge_Dead_Time_REG;		// Apply Dead-Time at Rising Edge
			ALTDTR4 = Falling_Edge_Dead_Time_REG;	// Apply Dead-Time at Falling Edge
//			PDC4 = DTR4 + ALTDTR4;					// Initial Pulse-Width = minimum Dead-Time required (DTR4 + ALTDTR4)
//			SDC4 = DTR4 + ALTDTR4;					// Initial Pulse-Width = minimum Dead-Time required (DTR4 + ALTDTR4)
			BSP_PWM_Channel_4_Update_Range_and_Offset();
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
#if (BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV);
			if(Rising_Edge_Dead_Time_REG > PTPER)
				Rising_Edge_Dead_Time_REG = PTPER;
			if(Falling_Edge_Dead_Time_REG > PTPER)
				Falling_Edge_Dead_Time_REG = PTPER;
#else	// BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
			Rising_Edge_Dead_Time_REG = Rising_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			Falling_Edge_Dead_Time_REG = Falling_Edge_Dead_Time * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV);
			if(Rising_Edge_Dead_Time_REG > STPER)
				Rising_Edge_Dead_Time_REG = STPER;
			if(Falling_Edge_Dead_Time_REG > STPER)
				Falling_Edge_Dead_Time_REG = STPER;
#endif	// BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT
			DTR5 = Rising_Edge_Dead_Time_REG;		// Apply Dead-Time at Rising Edge
			ALTDTR5 = Falling_Edge_Dead_Time_REG;	// Apply Dead-Time at Falling Edge
//			PDC5 = DTR5 + ALTDTR5;					// Initial Pulse-Width = minimum Dead-Time required (DTR5 + ALTDTR5)
//			SDC5 = DTR5 + ALTDTR5;					// Initial Pulse-Width = minimum Dead-Time required (DTR5 + ALTDTR5)
			BSP_PWM_Channel_5_Update_Range_and_Offset();
			break;
	}
}

#if 0
void BSP_PWM_Channel_Set_Trigger(char Channel, unsigned long Location, unsigned char Cycle, unsigned char Start)
{
	unsigned long Location_REG;

	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
#if BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			Location_REG += (DTR1 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG1bits.TRGCMP = Location_REG;	// Trigger generated at time x of PWM active period
			TRGCON1bits.TRGDIV = Cycle;			// Trigger output for every x-nd trigger event
			TRGCON1bits.TRGSTRT = Start;		// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON1bits.TRGIEN = 1;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			//TRIG2 = Location_REG;			// Trigger generated at time x of PWM active period
			//TRIG2 = 1132 << 3;	// 1200ns
			//TRIG2bits.TRGCMP = 1132;
			//TRIG2bits.TRGCMP = 0;
			//TRIG2bits.TRGCMP = 141;	// div by 8 (-815)
			//TRIG2bits.TRGCMP = 282;	// div by 8 (-815)
			//TRIG2bits.TRGCMP = 564;	// div by 8 (-815)
#if BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			Location_REG += (DTR2 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG2bits.TRGCMP = Location_REG;	// Trigger generated at time x of PWM active period
			TRGCON2bits.TRGDIV = Cycle;			// Trigger output for every x-nd trigger event
			TRGCON2bits.TRGSTRT = Start;		// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON2bits.TRGIEN = 1;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
#if BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			Location_REG += (DTR3 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG3bits.TRGCMP = Location_REG;	// Trigger generated at time x of PWM active period
			TRGCON3bits.TRGDIV = Cycle;			// Trigger output for every x-nd trigger event
			TRGCON3bits.TRGSTRT = Start;		// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON3bits.TRGIEN = 1;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
#if BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			Location_REG += (DTR4 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG4bits.TRGCMP = Location_REG;	// Trigger generated at time x of PWM active period
			TRGCON4bits.TRGDIV = Cycle;			// Trigger output for every x-nd trigger event
			TRGCON4bits.TRGSTRT = Start;		// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON4bits.TRGIEN = 1;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
#if BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			Location_REG = Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			Location_REG += (DTR5 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG5bits.TRGCMP = Location_REG;	// Trigger generated at time x of PWM active period
			TRGCON5bits.TRGDIV = Cycle;			// Trigger output for every x-nd trigger event
			TRGCON5bits.TRGSTRT = Start;		// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON5bits.TRGIEN = 1;				// Trigger event interrupts are enabled
			break;
	}
}
#else
void BSP_PWM_Channel_Set_Trigger(char Channel, unsigned long First_Location, unsigned long Second_Location, unsigned char Cycle, unsigned char Start, unsigned char Int_Enable)
{
	unsigned long First_Location_REG, Second_Location_REG;

	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
#if BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			First_Location_REG += (DTR1 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			Second_Location_REG += (DTR1 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG1bits.TRGCMP = First_Location_REG;			// Trigger generated at time x of PWM active period
			if(Second_Location_REG == 0) {
				TRGCON1bits.DTM = 0;						// Secondary trigger event is not combined with the primary trigger event to create a PWM trigger
			} else {
				STRIG1bits.STRGCMP = Second_Location_REG;	// Trigger generated at time x of PWM active period
				TRGCON1bits.DTM = 1;						// Secondary trigger event is combined with the primary trigger event to create a PWM trigger
			}
			TRGCON1bits.TRGDIV = Cycle;						// Trigger output for every x-nd trigger event
			TRGCON1bits.TRGSTRT = Start;					// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON1bits.TRGIEN = Int_Enable;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
#if BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			First_Location_REG += (DTR2 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			Second_Location_REG += (DTR2 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG2bits.TRGCMP = First_Location_REG;			// Trigger generated at time x of PWM active period
			if(Second_Location_REG == 0) {
				TRGCON2bits.DTM = 0;						// Secondary trigger event is not combined with the primary trigger event to create a PWM trigger
			} else {
				STRIG2bits.STRGCMP = Second_Location_REG;	// Trigger generated at time x of PWM active period
				TRGCON2bits.DTM = 1;						// Secondary trigger event is combined with the primary trigger event to create a PWM trigger
			}
			TRGCON2bits.TRGDIV = Cycle;						// Trigger output for every x-nd trigger event
			TRGCON2bits.TRGSTRT = Start;					// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON2bits.TRGIEN = Int_Enable;				// Trigger event interrupts are enabled/disabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
#if BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			First_Location_REG += (DTR3 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			Second_Location_REG += (DTR3 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG3bits.TRGCMP = First_Location_REG;			// Trigger generated at time x of PWM active period
			if(Second_Location_REG == 0) {
				TRGCON3bits.DTM = 0;						// Secondary trigger event is not combined with the primary trigger event to create a PWM trigger
			} else {
				STRIG3bits.STRGCMP = Second_Location_REG;	// Trigger generated at time x of PWM active period
				TRGCON3bits.DTM = 1;						// Secondary trigger event is combined with the primary trigger event to create a PWM trigger
			}
			TRGCON3bits.TRGDIV = Cycle;						// Trigger output for every x-nd trigger event
			TRGCON3bits.TRGSTRT = Start;					// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON3bits.TRGIEN = Int_Enable;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
#if BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			First_Location_REG += (DTR4 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			Second_Location_REG += (DTR4 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG4bits.TRGCMP = First_Location_REG;			// Trigger generated at time x of PWM active period
			if(Second_Location_REG == 0) {
				TRGCON4bits.DTM = 0;						// Secondary trigger event is not combined with the primary trigger event to create a PWM trigger
			} else {
				STRIG4bits.STRGCMP = Second_Location_REG;	// Trigger generated at time x of PWM active period
				TRGCON4bits.DTM = 1;						// Secondary trigger event is combined with the primary trigger event to create a PWM trigger
			}
			TRGCON4bits.TRGDIV = Cycle;						// Trigger output for every x-nd trigger event
			TRGCON4bits.TRGSTRT = Start;					// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON4bits.TRGIEN = Int_Enable;				// Trigger event interrupts are enabled
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
#if BSP_PWM_CHANNEL_5_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_PRIMARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#else
			First_Location_REG = First_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
			Second_Location_REG = Second_Location * 1000 / (BSP_SETTINGS_PWM_CLOCK_PERIOD * BSP_SETTINGS_PWM_TIME_BASE_SECONDARY_DIV * BSP_SETTINGS_PWM_TRIGGER_DIV);
#endif
			First_Location_REG += (DTR5 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			Second_Location_REG += (DTR5 / BSP_SETTINGS_PWM_TRIGGER_DIV);	// Time correction (Extended with Rising Edge Dead Time)
			TRIG5bits.TRGCMP = First_Location_REG;			// Trigger generated at time x of PWM active period
			if(Second_Location_REG == 0) {
				TRGCON5bits.DTM = 0;						// Secondary trigger event is not combined with the primary trigger event to create a PWM trigger
			} else {
				STRIG5bits.STRGCMP = Second_Location_REG;	// Trigger generated at time x of PWM active period
				TRGCON5bits.DTM = 1;						// Secondary trigger event is combined with the primary trigger event to create a PWM trigger
			}
			TRGCON5bits.TRGDIV = Cycle;						// Trigger output for every x-nd trigger event
			TRGCON5bits.TRGSTRT = Start;					// Wait x PWM cycles before generating the first trigger event after the module is enabled
			PWMCON5bits.TRGIEN = Int_Enable;				// Trigger event interrupts are enabled
			break;
	}
}
#endif

// unsigned long __builtin_muluu(const unsigned int p0, const unsigned int p1);
// unsigned int __builtin_divud(const unsigned long num, const unsigned int den);

inline void BSP_PWM_Channel_1_Set_DutyCycle(uint16_t Duty_Cycle)
{
//	Duty_Cycle_REG = ((float)(PTPER - (DTR1 + ALTDTR1)) * Duty_Cycle) + DTR1;
//	Duty_Cycle_REG = ((float)(PTPER - (DTR1 + DTR1 + ALTDTR1 + ALTDTR1)) * Duty_Cycle) + DTR1 + DTR1;
//	Duty_Cycle_REG = ((((uint32_t)(PTPER - (DTR1 + DTR1 + ALTDTR1 + ALTDTR1)) * Duty_Cycle) / 32768) + DTR1 + DTR1);
#if (BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
//	PDC1 = __builtin_divud(__builtin_muluu(PTPER - (DTR1 + DTR1 + ALTDTR1 + ALTDTR1), Duty_Cycle), 65535) + DTR1 + DTR1;
#else	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
//	PDC1 = __builtin_divud(__builtin_muluu(STPER - (DTR1 + DTR1 + ALTDTR1 + ALTDTR1), Duty_Cycle), 65535) + DTR1 + DTR1;
#endif	// BSP_PWM_CHANNEL_1_MASTER_TIME_BASE_SELECT
	PDC1 = __builtin_divud(__builtin_muluu(BSP_PWM_Channel_1_Range, Duty_Cycle), 65535) + BSP_PWM_Channel_1_Offset;
//	SDC1 = PDC1;
}

inline void BSP_PWM_Channel_2_Set_DutyCycle(uint16_t Duty_Cycle)
{
//	Duty_Cycle_REG = ((float)(PTPER - (DTR2 + ALTDTR2)) * Duty_Cycle) + DTR2;
//	Duty_Cycle_REG = ((float)(PTPER - (DTR2 + DTR2 + ALTDTR2)) * Duty_Cycle) + DTR2 + DTR2;
//	Duty_Cycle_REG = ((float)(PTPER - (DTR2 + DTR2 + ALTDTR2 + ALTDTR2)) * Duty_Cycle) + DTR2 + DTR2;
//	Duty_Cycle_REG = (((uint32_t)(PTPER - (DTR2 + DTR2 + ALTDTR2 + ALTDTR2)) * Duty_Cycle) + DTR2 + DTR2) / 65536;
//	Duty_Cycle_REG = ((((uint32_t)(PTPER - (DTR2 + DTR2 + ALTDTR2 + ALTDTR2)) * Duty_Cycle) / 65536) + DTR2 + DTR2);
//	Duty_Cycle_REG = __builtin_divud(((uint32_t)(PTPER - (DTR2 + DTR2 + ALTDTR2 + ALTDTR2)) * Duty_Cycle), 65535) + DTR2 + DTR2;
#if (BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
//	PDC2 = __builtin_divud(__builtin_muluu(PTPER - (DTR2 + DTR2 + ALTDTR2 + ALTDTR2), Duty_Cycle), 65535) + DTR2 + DTR2;
#else	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
//	PDC2 = __builtin_divud(__builtin_muluu(STPER - (DTR2 + DTR2 + ALTDTR2 + ALTDTR2), Duty_Cycle), 65535) + DTR2 + DTR2;
#endif	// BSP_PWM_CHANNEL_2_MASTER_TIME_BASE_SELECT
	PDC2 = __builtin_divud(__builtin_muluu(BSP_PWM_Channel_2_Range, Duty_Cycle), 65535) + BSP_PWM_Channel_2_Offset;
//	PDC2 = (__builtin_muluu(BSP_PWM_Channel_2_Range, Duty_Cycle) >> 16) + BSP_PWM_Channel_2_Offset;
//	SDC2 = PDC2;
}

inline void BSP_PWM_Channel_3_Set_DutyCycle(uint16_t Duty_Cycle)
{
//	Duty_Cycle_REG = ((float)(PTPER - (DTR3 + ALTDTR3)) * Duty_Cycle) + DTR3;
//	Duty_Cycle_REG = ((float)(PTPER - (DTR3 + DTR3 + ALTDTR3 + ALTDTR3)) * Duty_Cycle) + DTR3 + DTR3;
//	Duty_Cycle_REG = ((((uint32_t)(PTPER - (DTR3 + DTR3 + ALTDTR3 + ALTDTR3)) * Duty_Cycle) / 32768) + DTR3 + DTR3);
#if (BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
//	PDC3 = __builtin_divud(__builtin_muluu(PTPER - (DTR3 + DTR3 + ALTDTR3 + ALTDTR3), Duty_Cycle), 65535) + DTR3 + DTR3;
#else	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
//	PDC3 = __builtin_divud(__builtin_muluu(STPER - (DTR3 + DTR3 + ALTDTR3 + ALTDTR3), Duty_Cycle), 65535) + DTR3 + DTR3;
#endif	// BSP_PWM_CHANNEL_3_MASTER_TIME_BASE_SELECT
	PDC3 = __builtin_divud(__builtin_muluu(BSP_PWM_Channel_3_Range, Duty_Cycle), 65535) + BSP_PWM_Channel_3_Offset;
//	SDC3 = PDC3;
}

inline void BSP_PWM_Channel_4_Set_DutyCycle(uint16_t Duty_Cycle)
{
//	Duty_Cycle_REG = ((float)(PTPER - (DTR4 + ALTDTR4)) * Duty_Cycle) + DTR4;
//	Duty_Cycle_REG = ((float)(PTPER - (DTR4 + DTR4 + ALTDTR4 + ALTDTR4)) * Duty_Cycle) + DTR4 + DTR4;
//	Duty_Cycle_REG = ((((uint32_t)(PTPER - (DTR4 + DTR4 + ALTDTR4 + ALTDTR4)) * Duty_Cycle) / 32768) + DTR4 + DTR4);
#if (BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_PRIMARY)
//	PDC4 = __builtin_divud(__builtin_muluu(PTPER - (DTR4 + DTR4 + ALTDTR4 + ALTDTR4), Duty_Cycle), 65535) + DTR4 + DTR4;
#else	// BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT == BSP_PWM_MASTER_TIME_BASE_SECONDARY
//	PDC4 = __builtin_divud(__builtin_muluu(STPER - (DTR4 + DTR4 + ALTDTR4 + ALTDTR4), Duty_Cycle), 65535) + DTR4 + DTR4;
#endif	// BSP_PWM_CHANNEL_4_MASTER_TIME_BASE_SELECT
	PDC4 = __builtin_divud(__builtin_muluu(BSP_PWM_Channel_4_Range, Duty_Cycle), 65535) + BSP_PWM_Channel_4_Offset;
//	SDC4 = PDC4;
}

inline void BSP_PWM_Channel_5_Set_DutyCycle(uint16_t Duty_Cycle)
{
	PDC5 = __builtin_divud(__builtin_muluu(BSP_PWM_Channel_5_Range, Duty_Cycle), 65535) + BSP_PWM_Channel_5_Offset;
}

inline void BSP_PWM_Channel_6_Set_DutyCycle(uint16_t Duty_Cycle)
{
	SDC5 = __builtin_divud(__builtin_muluu(BSP_PWM_Channel_5_Range, Duty_Cycle), 65535) + BSP_PWM_Channel_5_Offset;
}

void BSP_PWM_Channel_Set_DutyCycle(char Channel, uint16_t Duty_Cycle)
{
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
			BSP_PWM_Channel_1_Set_DutyCycle(Duty_Cycle);
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			BSP_PWM_Channel_2_Set_DutyCycle(Duty_Cycle);
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
			BSP_PWM_Channel_3_Set_DutyCycle(Duty_Cycle);
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
			BSP_PWM_Channel_4_Set_DutyCycle(Duty_Cycle);
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
			BSP_PWM_Channel_5_Set_DutyCycle(Duty_Cycle);
			break;
		case BSP_PWM_CHANNEL_NUMBER_6:
			BSP_PWM_Channel_6_Set_DutyCycle(Duty_Cycle);
			break;
	}
}

inline void BSP_PWM_Channel_1_Interrupt_Clear(void)
{
	IFS5bits.PWM1IF = 0;
}

inline void BSP_PWM_Channel_2_Interrupt_Clear(void)
{
	IFS5bits.PWM2IF = 0;
}

inline void BSP_PWM_Channel_3_Interrupt_Clear(void)
{
	IFS6bits.PWM3IF = 0;
}

inline void BSP_PWM_Channel_4_Interrupt_Clear(void)
{
	IFS6bits.PWM4IF = 0;
}

inline void BSP_PWM_Channel_5_Interrupt_Clear(void)
{
	IFS6bits.PWM5IF = 0;
}

void BSP_PWM_Interrupt_Enable(char Channel, unsigned char Level)
{
	switch(Channel) {
		case BSP_PWM_CHANNEL_NUMBER_1:
			IPC23bits.PWM1IP = Level;
			IFS5bits.PWM1IF = 0;
			IEC5bits.PWM1IE = 1;
			break;
		case BSP_PWM_CHANNEL_NUMBER_2:
			IPC23bits.PWM2IP = Level;
			IFS5bits.PWM2IF = 0;
			IEC5bits.PWM2IE = 1;
			break;
		case BSP_PWM_CHANNEL_NUMBER_3:
			IPC24bits.PWM3IP = Level;
			IFS6bits.PWM3IF = 0;
			IEC6bits.PWM3IE = 1;
			break;
		case BSP_PWM_CHANNEL_NUMBER_4:
			IPC24bits.PWM4IP = Level;
			IFS6bits.PWM4IF = 0;
			IEC6bits.PWM4IE = 1;
			break;
		case BSP_PWM_CHANNEL_NUMBER_5:
			IPC24bits.PWM5IP = Level;
			IFS6bits.PWM5IF = 0;
			IEC6bits.PWM5IE = 1;
			break;
	}
}

#if 0
void __attribute__((__interrupt__, no_auto_psv)) _PWM1Interrupt()
{
	BSP_PWM_Channel_1_Interrupt_Clear();
}
#endif

#if 0
uint8_t SinusQuarter = 0;
uint16_t SinusArrayCounter = 0;

void __attribute__((__interrupt__, no_auto_psv)) _PWM2Interrupt()
{
	unsigned int sample_int;
	float sample_float;

	IFS5bits.PWM2IF = 0;
	LED5_OUT ^= 1;

	if(SinusQuarter == 0) {
		sample_int = 32768 + sineTable512[SinusArrayCounter++];
		if(SinusArrayCounter == 511) {
			SinusQuarter++;
		}
	}
	if(SinusQuarter == 2) {
		sample_int = 32767 - sineTable512[SinusArrayCounter++];
		if(SinusArrayCounter == 511) {
			SinusQuarter++;
		}
	}
	if(SinusQuarter == 1) {
		sample_int = 32768 + sineTable512[SinusArrayCounter--];
		if(SinusArrayCounter == 0) {
			SinusQuarter++;
		}
	}
	if(SinusQuarter == 3) {
		sample_int = 32767 - sineTable512[SinusArrayCounter--];
		if(SinusArrayCounter == 0) {
			SinusQuarter = 0;
		}
	}
	sample_float = (float)sample_int / 65535.0;
//	PDC2 = sample_int;
	BSP_PWM_Channel_Set_DutyCycle(2, sample_float);
}
#else
void __attribute__((__interrupt__, no_auto_psv)) BSP_PWM_INTERRUPT_HANDLER()
{
	PWM_TST1_SET();
	BSP_PWM_Trigger_Sync = 0;
//	BSP_PWM_INTERRUPT_CALLBACK();
	BSP_PWM_INTERRUPT_CLEAR();
	PWM_TST1_CLR();
}
#endif
