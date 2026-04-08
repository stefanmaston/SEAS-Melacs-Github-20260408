#ifndef CONFIG_HARDWARE_H
#define CONFIG_HARDWARE_H

#include <p33Exxxx.h>
// the above include path may be different for each user.  If a compile
// time error appears then check the path for the file above and edit
// the include statement above.

// GPIOs
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
//#define GPIO_LED_1_PORTPIN	D10			// Pin RD10 (LED502)
//#define GPIO_LED_2_PORTPIN	D14			// Pin RD14 (LED501)
//#define GPIO_LED_3_PORTPIN	B6			// Pin RB6  (LED500)
#define GPIO_LED_HB_PORTPIN		D10			// Pin RD10 (LED502)
#define GPIO_TST1_PORTPIN		D14			// Pin RD14 (LED501)
#define GPIO_TST2_PORTPIN		B6			// Pin RB6  (LED500)
#ifdef HARDWARE_VERSION_1
#define GPIO_TST3_PORTPIN		B7			// Pin RB7
#endif	// HARDWARE_VERSION_1
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
//#define GPIO_LED_1_PORTPIN	C0			// Pin RC0  (LED1)
#define GPIO_LED_2_PORTPIN		C13			// Pin RC13 (LED2)
#define GPIO_LED_HB_PORTPIN		C0			// Pin RC0  (LED1)
#else
// 28-pins Starter Board
//#define GPIO_LED_1_PORTPIN	A3			// Pin RA3  (LED4)
//#define GPIO_LED_2_PORTPIN	A4			// Pin RA4  (LED5)
//#define GPIO_LED_3_PORTPIN	B14			// Pin RB14 (LED6)
//#define GPIO_LED_4_PORTPIN	B13			// Pin RB13 (LED7)
//#define GPIO_LED_HB_PORTPIN	A3			// Pin RA3  (LED4)
#define GPIO_TST1_PORTPIN		B5			// Pin RB5
#define GPIO_TST2_PORTPIN		B15			// Pin RB15
#endif

// UARTs
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
#ifdef DEBUG_ON_RS485
#define UART1_RX_PORTPIN		C14			// Pin RC14 (U1_RXD)
#define UART1_TX_PORTPIN		C15			// Pin RC15 (U1_TXD)
#define UART1_RX_REMAP			62			// Pin RP62 (U1_RXD)
#define UART1_TX_REMAP			63			// Pin RP63 (U1_TXD)
#else
#define UART1_RX_PORTPIN		C0			// Pin RC0  (U2_RXD)
#define UART1_TX_PORTPIN		C13			// Pin RC13 (U2_TXD)
#define UART1_RX_REMAP			48			// Pin RP48 (U2_RXD)
#define UART1_TX_REMAP			61			// Pin RP61 (U2_TXD)
#endif
#define UART2_RX_PORTPIN		C14			// Pin RC14 (U1_RXD)
#define UART2_TX_PORTPIN		C15			// Pin RC15 (U1_TXD)
#define UART2_RX_REMAP			62			// Pin RP62 (U1_RXD)
#define UART2_TX_REMAP			63			// Pin RP63 (U1_TXD)
#define UART2_TXEN_PORTPIN		B4			// Pin RB4  (U1_TXEN)
#define UART2_TXEN_REMAP		36			// Pin RP36 (U1_TXEN)
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
#define UART1_RX_PORTPIN		B4			// Pin RB4  (UART_TXD)
#define UART1_TX_PORTPIN		C14			// Pin RC14 (UART_RXD)
#define UART1_RX_REMAP			36			// Pin RP36 (UART_TXD)
#define UART1_TX_REMAP			62			// Pin RP62 (UART_RXD)
#define UART2_TXEN_PORTPIN		C8			// Pin RC8  (I2C_SCL)
#define UART2_RX_PORTPIN		C7			// Pin RC7  (I2C_SDA)
#define UART2_TX_PORTPIN		C15			// Pin RC15 (SPI_SCK)
#define UART2_RX_REMAP			27			// Pin RP27 (I2C_SDA)
#define UART2_TX_REMAP			34			// Pin RP34 (SPI_SCK)
#else
// 28-pins Starter Board
#define UART1_RX_PORTPIN		B7			// Pin RB7 (RX/PGC)
#define UART1_TX_PORTPIN		B6			// Pin RB6 (TX/PGD)
#define UART1_RX_REMAP			39			// Pin RP39 (RX/PGC)
#define UART1_TX_REMAP			38			// Pin RP38 (TX/PGD)
#endif

// ADCs
#if (!defined PINS28_STARTER_BOARD)
// Inresol Inverter
// Engineering Sample Evaluation Board
#define ADC_CORE1_AN0_PORTPIN	A0			// Pin RA0 (AN0)
#define ADC_CORE1_AN7_PORTPIN	B2			// Pin RB2 (AN7)
#define ADC_CORE2_AN1_PORTPIN	A1			// Pin RA1 (AN1)
#define ADC_CORE2_AN18_PORTPIN	B3			// Pin RB3 (AN18)
#define ADC_CORE3_AN2_PORTPIN	A2			// Pin RA2 (AN2)
#define ADC_CORE3_AN11_PORTPIN	C9			// Pin RC9 (AN11)
#define ADC_CORE4_AN3_PORTPIN	B0			// Pin RB0 (AN3)
#define ADC_CORE4_AN15_PORTPIN	D7			// Pin RD7 (AN15)
#define ADC_CORE5_AN4_PORTPIN	B9			// Pin RB9 (AN4)
#define ADC_CORE5_AN5_PORTPIN	D8			// Pin RD8 (AN5)
#define ADC_CORE5_AN6_PORTPIN	B1			// Pin RB1 (AN6)
#define ADC_CORE5_AN8_PORTPIN	C1			// Pin RC1 (AN8)
#define ADC_CORE5_AN9_PORTPIN	C2			// Pin RC2 (AN9)
#define ADC_CORE5_AN10_PORTPIN	C10			// Pin RC10 (AN10)
#define ADC_CORE5_AN12_PORTPIN	D5			// Pin RD5 (AN12)
#define ADC_CORE5_AN13_PORTPIN	D13			// Pin RD13 (AN13)
#define ADC_CORE5_AN14_PORTPIN	C12			// Pin RC12 (AN14)
#define ADC_CORE5_AN16_PORTPIN	D2			// Pin RD2 (AN16)
#define ADC_CORE5_AN17_PORTPIN	C6			// Pin RC6 (AN17)
#define ADC_CORE5_AN19_PORTPIN	B5			// Pin RB5 (AN19)
#ifndef HARDWARE_VERSION_1
#define ADC_CORE5_AN21_PORTPIN	B7			// Pin RB7 (AN21)
#endif	// HARDWARE_VERSION_1
#else
// 28-pins Starter Board
#define ADC_CORE1_AN0_PORTPIN	A0			// Pin RA0 (AN0)
//#define ADC_CORE1_AN7_PORTPIN	B2			// Pin RB2 (AN7)
#define ADC_CORE2_AN1_PORTPIN	A1			// Pin RA1 (AN1)
//#define ADC_CORE2_AN18_PORTPIN	B3			// Pin RB3 (AN18)
#define ADC_CORE3_AN2_PORTPIN	A2			// Pin RA2 (AN2)
//#define ADC_CORE3_AN11_PORTPIN	C9			// Pin RC9 (AN11)
#define ADC_CORE4_AN3_PORTPIN	B0			// Pin RB0 (AN3)
//#define ADC_CORE4_AN15_PORTPIN	D7			// Pin RD7 (AN15)
#define ADC_CORE5_AN4_PORTPIN	B9			// Pin RB9 (AN4)
//#define ADC_CORE5_AN5_PORTPIN	B10			// Pin RB10 (AN5)
//#define ADC_CORE5_AN6_PORTPIN	B1			// Pin RB1 (AN6)
//#define ADC_CORE5_AN8_PORTPIN	C1			// Pin RC1 (AN8)
//#define ADC_CORE5_AN9_PORTPIN	C2			// Pin RC2 (AN9)
//#define ADC_CORE5_AN10_PORTPIN	C10			// Pin RC10 (AN10)
//#define ADC_CORE5_AN12_PORTPIN	D5			// Pin RD5 (AN12)
//#define ADC_CORE5_AN13_PORTPIN	D13			// Pin RD13 (AN13)
//#define ADC_CORE5_AN14_PORTPIN	C12			// Pin RC12 (AN14)
//#define ADC_CORE5_AN16_PORTPIN	D2			// Pin RD2 (AN16)
//#define ADC_CORE5_AN17_PORTPIN	C6			// Pin RC6 (AN17)
//#define ADC_CORE5_AN19_PORTPIN	B5			// Pin RB5 (AN19)
//#define ADC_CORE5_AN20_PORTPIN	B6			// Pin RB6 (AN20)
//#define ADC_CORE5_AN21_PORTPIN	B7			// Pin RB7 (AN21)
#endif

// RLYs
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
#define GPIO_RLY_INV_P_PORTPIN		D4			// Pin RD4
#define GPIO_RLY_INV_N_PORTPIN		D12			// Pin RD12
#define GPIO_RLY_GRID_P_PORTPIN		D15			// Pin RD15
#define GPIO_RLY_GRID_N_PORTPIN		D0			// Pin RD0
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
#define GPIO_RLY_INV_P_PORTPIN		C7			// Pin RC7  (J4 CONN - I2C SDA)
#define GPIO_RLY_INV_N_PORTPIN		C8			// Pin RC8  (J4 CONN - I2C SCL)
#define GPIO_RLY_GRID_P_PORTPIN		C15			// Pin RC15 (J4 CONN - SPI SCK)
#define GPIO_RLY_GRID_N_PORTPIN		D9			// Pin RD9  (CAN RX)
#else
// 28-pins Starter Board
#endif

// OCPs
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
#define OC_L1_INV_PORTPIN		C4			// Pin RC4  (L1_I_INV_OC)
#define OC_L2_INV_PORTPIN		C5			// Pin RC5  (L2_I_INV_OC)
#define OC_L3_INV_PORTPIN		C7			// Pin RC7  (L3_I_INV_OC)
#define OC_L1_GRID_PORTPIN		C8			// Pin RC8  (L1_I_GRID_OC)
#define OC_L2_GRID_PORTPIN		D11			// Pin RD11 (L2_I_GRID_OC)
#define OC_L3_GRID_PORTPIN		D9			// Pin RD9  (L3_I_GRID_OC)
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
#define OC_L1_INV_PORTPIN		C4			// Pin RC4  (J5 CONN)
#define OC_L2_INV_PORTPIN		C5			// Pin RC5  (J5 CONN)
#define OC_L3_INV_PORTPIN		D4			// Pin RD4  (J5 CONN)
#define OC_L1_GRID_PORTPIN		D12			// Pin RD12 (J5 CONN)
#define OC_L2_GRID_PORTPIN		D15			// Pin RD15 (J5 CONN)
#define OC_L3_GRID_PORTPIN		D11			// Pin RD11 (J5 CONN)
#else
// 28-pins Starter Board
#endif

// ***********************
// Conditional Definitions
// ***********************
#ifdef GPIO_LED_1_PORTPIN
#define GPIO_LED_1_SET()		BSP_IO_GPIO_SET(GPIO_LED_1_PORTPIN)
#define GPIO_LED_1_CLR()		BSP_IO_GPIO_CLR(GPIO_LED_1_PORTPIN)
#define GPIO_LED_1_TGL()		BSP_IO_GPIO_TGL(GPIO_LED_1_PORTPIN)
#else
#define GPIO_LED_1_SET()
#define GPIO_LED_1_CLR()
#define GPIO_LED_1_TGL()
#endif
#ifdef GPIO_LED_2_PORTPIN
#define GPIO_LED_2_SET()		BSP_IO_GPIO_SET(GPIO_LED_2_PORTPIN)
#define GPIO_LED_2_CLR()		BSP_IO_GPIO_CLR(GPIO_LED_2_PORTPIN)
#define GPIO_LED_2_TGL()		BSP_IO_GPIO_TGL(GPIO_LED_2_PORTPIN)
#else
#define GPIO_LED_2_SET()
#define GPIO_LED_2_CLR()
#define GPIO_LED_2_TGL()
#endif
#ifdef GPIO_LED_3_PORTPIN
#define GPIO_LED_3_SET()		BSP_IO_GPIO_SET(GPIO_LED_3_PORTPIN)
#define GPIO_LED_3_CLR()		BSP_IO_GPIO_CLR(GPIO_LED_3_PORTPIN)
#define GPIO_LED_3_TGL()		BSP_IO_GPIO_TGL(GPIO_LED_3_PORTPIN)
#else
#define GPIO_LED_3_SET()
#define GPIO_LED_3_CLR()
#define GPIO_LED_3_TGL()
#endif
#ifdef GPIO_LED_4_PORTPIN
#define GPIO_LED_4_SET()		BSP_IO_GPIO_SET(GPIO_LED_4_PORTPIN)
#define GPIO_LED_4_CLR()		BSP_IO_GPIO_CLR(GPIO_LED_4_PORTPIN)
#define GPIO_LED_4_TGL()		BSP_IO_GPIO_TGL(GPIO_LED_4_PORTPIN)
#else
#define GPIO_LED_4_SET()
#define GPIO_LED_4_CLR()
#define GPIO_LED_4_TGL()
#endif
#ifdef GPIO_LED_HB_PORTPIN
#define GPIO_LED_HB_SET()		BSP_IO_GPIO_SET(GPIO_LED_HB_PORTPIN)
#define GPIO_LED_HB_CLR()		BSP_IO_GPIO_CLR(GPIO_LED_HB_PORTPIN)
#define GPIO_LED_HB_TGL()		BSP_IO_GPIO_TGL(GPIO_LED_HB_PORTPIN)
#else
#define GPIO_LED_HB_SET()
#define GPIO_LED_HB_CLR()
#define GPIO_LED_HB_TGL()
#endif
#ifdef GPIO_TST1_PORTPIN
#define GPIO_TST1_SET()			BSP_IO_GPIO_SET(GPIO_TST1_PORTPIN)
#define GPIO_TST1_CLR()			BSP_IO_GPIO_CLR(GPIO_TST1_PORTPIN)
#define GPIO_TST1_TGL()			BSP_IO_GPIO_TGL(GPIO_TST1_PORTPIN)
#else
#define GPIO_TST1_SET()
#define GPIO_TST1_CLR()
#define GPIO_TST1_TGL()
#endif
#ifdef GPIO_TST2_PORTPIN
#define GPIO_TST2_SET()			BSP_IO_GPIO_SET(GPIO_TST2_PORTPIN)
#define GPIO_TST2_CLR()			BSP_IO_GPIO_CLR(GPIO_TST2_PORTPIN)
#define GPIO_TST2_TGL()			BSP_IO_GPIO_TGL(GPIO_TST2_PORTPIN)
#else
#define GPIO_TST2_SET()
#define GPIO_TST2_CLR()
#define GPIO_TST2_TGL()
#endif
#ifdef GPIO_TST3_PORTPIN
#define GPIO_TST3_SET()			BSP_IO_GPIO_SET(GPIO_TST3_PORTPIN)
#define GPIO_TST3_CLR()			BSP_IO_GPIO_CLR(GPIO_TST3_PORTPIN)
#define GPIO_TST3_TGL()			BSP_IO_GPIO_TGL(GPIO_TST3_PORTPIN)
#else
#define GPIO_TST3_SET()
#define GPIO_TST3_CLR()
#define GPIO_TST3_TGL()
#endif

#define GPIO_UART2_TX_ON()		BSP_IO_GPIO_CLR(UART2_TXEN_PORTPIN)
#define GPIO_UART2_TX_OFF()		BSP_IO_GPIO_SET(UART2_TXEN_PORTPIN)

#endif	// CONFIG_HARDWARE_H
