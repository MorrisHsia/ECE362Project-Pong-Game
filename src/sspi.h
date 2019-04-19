#ifndef _VVC_SSPI_H
#define _VVC_SSPI_H

//#include "global.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"


// Define GPIOB pin mappings for software '4-wire' SPI.
#define PB_MOSI (15)
#define PB_SCK  (13)
#define PB_DC   (14)
#define PA_CS   (12)
#define PA_RST  (15) // for SPI1
#define PB_RST  (12) // for SPI2

/* Software SPI functions. */
// Write a byte of data using software SPI.
inline void sspi_w(uint8_t dat);
// Write a 'command' byte for 4-wire SPI interfaces.
inline void sspi_cmd(uint8_t cdat);

/* Hardware SPI functions. */
void hspi_init(SPI_TypeDef *SPIx);
void hspi_w8(SPI_TypeDef *SPIx, uint8_t dat);
void hspi_w16(SPI_TypeDef *SPIx, uint16_t dat);
void hspi_cmd(SPI_TypeDef *SPIx, uint8_t cmd);

#endif
