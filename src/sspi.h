
#include "global.h"

// Define GPIOB pin mappings for software '4-wire' SPI.
#define PB_MOSI (5)
#define PB_SCK  (3)
#define PB_DC   (4)
#define PA_CS   (12)
#define PA_RST  (15)

/* Software SPI functions. */
// Write a byte of data using software SPI.
inline void sspi_w(uint8_t dat);
// Write a 'command' byte for 4-wire SPI interfaces.
inline void sspi_cmd(uint8_t cdat);

/* Hardware SPI functions. */
void hspi_init();
void hspi_w8(uint8_t dat);
void hspi_w16(uint16_t dat);
void hspi_cmd(uint8_t cmd);
