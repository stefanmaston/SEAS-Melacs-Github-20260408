#include "pic32_board.h"
#include "pin_map.h"

#include <xc.h>

static void cs_idle(void)
{
    PIN_CS_AD_LAT = 1;
    PIN_CS_RTC_LAT = 1;
    PIN_CS_SD_LAT = 1;
    PIN_CS_ETH_LAT = 1;
}

void spi_bus_init(void)
{
    PIN_CS_AD_TRIS = 0;
    PIN_CS_RTC_TRIS = 0;
    PIN_CS_SD_TRIS = 0;
    PIN_CS_ETH_TRIS = 0;
    PIN_SPI_SCK_TRIS = 0;
    PIN_SPI_MOSI_TRIS = 0;
    PIN_SPI_MISO_TRIS = 1;
    cs_idle();
    spi_hw_on(1);
}

void spi_hw_on(int slow)
{
    uint8_t dump;

    cs_idle();
    SPI3CON = 0;
    dump = (uint8_t)SPI3BUF;
    (void)dump;
    SPI3STATCLR = 1u << 6;
    SPI3BRG = slow ? 44 : 2;
    SPI3CONbits.MSTEN = 1;
    SPI3CONbits.CKE = 1;
    SPI3CONbits.SMP = 1;
    SPI3CONbits.ON = 1;
}

void spi_hw_off(void)
{
    SPI3CONbits.ON = 0;
    PIN_SPI_SCK_TRIS = 0;
    PIN_SPI_MOSI_TRIS = 0;
    PIN_SPI_MISO_TRIS = 1;
    PIN_SPI_SCK_LAT = 0;
    PIN_SPI_MOSI_LAT = 0;
}

uint8_t spi_xfer(uint8_t value)
{
    SPI3BUF = value;
    while (!SPI3STATbits.SPIRBF) {
    }
    return (uint8_t)SPI3BUF;
}

uint8_t bb_xfer(uint8_t value)
{
    uint8_t in = 0;
    int i;

    for (i = 0; i < 8; i++) {
        PIN_SPI_MOSI_LAT = (value & 0x80u) ? 1 : 0;
        value <<= 1;
        delay_us(2);
        PIN_SPI_SCK_LAT = 1;
        delay_us(2);
        in = (uint8_t)((in << 1) | (PIN_SPI_MISO_PORT ? 1 : 0));
        PIN_SPI_SCK_LAT = 0;
    }
    return in;
}
