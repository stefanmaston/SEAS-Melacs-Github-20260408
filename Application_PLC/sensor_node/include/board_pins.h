#ifndef BOARD_PINS_H
#define BOARD_PINS_H

/*
 * RP2350A på mät- och styrpunkten. GPIO26–GPIO29 är de fyra ADC-ingångarna.
 * USB, QSPI-flash och SWD sitter vid sidan av GPIO0–GPIO29.
 *
 * Delare 0–10 V: 75 kΩ uppifrån, 33 kΩ mot jord. 10 V ger 3,056 V på benet.
 * 4–20 mA: 150 Ω börda. 20 mA ger 3,00 V.
 * 0–10 V ut: MCP4822 kanal A, förstärkning 2 (0–4,096 V), operationsförstärkare
 * med 10,0 kΩ mot jord och 14,4 kΩ i återkopplingen (förstärkning 2,44).
 * mA ut: MCP4822 kanal B till XTR111, Rset 2,05 kΩ, så full skala är 20,0 mA.
 */

#define BOARD_GPIO_COUNT 30
#define BOARD_PIN_UART_TX 0
#define BOARD_PIN_UART_RX 1
#define BOARD_PIN_SPI_SCK 2
#define BOARD_PIN_SPI_MOSI 3
#define BOARD_PIN_SPI_MISO 4
#define BOARD_PIN_CS_TC 5
#define BOARD_PIN_CS_RTD 6
#define BOARD_PIN_CS_DAC 7
#define BOARD_PIN_RS485_DE 8
#define BOARD_PIN_OW 9
#define BOARD_PIN_I2C_SDA 10
#define BOARD_PIN_I2C_SCL 11
#define BOARD_PIN_DI0 12
#define BOARD_PIN_DI1 13
#define BOARD_PIN_DI2 14
#define BOARD_PIN_DI3 15
#define BOARD_PIN_DO0 16
#define BOARD_PIN_DO1 17
#define BOARD_PIN_DO2 18
#define BOARD_PIN_DO3 19
#define BOARD_PIN_ADC_LM35 26
#define BOARD_PIN_ADC_V0 27
#define BOARD_PIN_ADC_MA 28
#define BOARD_PIN_ADC_V1 29

#define BOARD_ADC_FULL 4095u
#define BOARD_ADC_MV 3300u
#define BOARD_DIV_TOP 75u
#define BOARD_DIV_BOT 33u
#define BOARD_BURDEN_OHM 150u
#define BOARD_PT_RREF_OHM 4000u

#define BOARD_USED_COUNT 24

/* GPIO20–GPIO25 är lediga och kan bli fler isolerade in- eller utgångar. */
#define BOARD_FREE_FIRST 20
#define BOARD_FREE_COUNT 6

#endif
