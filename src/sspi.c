#include "sspi.h"

/*
 * Write a byte of data using software SPI. For each bit:
 * 1. Pull the clock pin low.
 * 2. Set the 'MOSI' data pin to the correct value.
 * 3. Pull the clock pin high.
 */
inline void sspi_w(uint8_t dat) {
  uint8_t sspi_i;
  // Send 8 bits, with the MSB first.
  for (sspi_i = 0x80; sspi_i != 0x00; sspi_i >>= 1) {
    GPIOB->ODR &= ~(1 << PB_SCK);
    if (dat & sspi_i) {
      GPIOB->ODR |=  (1 << PB_MOSI);
    }
    else {
      GPIOB->ODR &= ~(1 << PB_MOSI);
    }
    GPIOB->ODR |=  (1 << PB_SCK);
  }
}

/*
 * Write a 'Command byte' over software SPI.
 * "4-wire" SPI interfaces are common in devices like
 * screens. A 'Data/Command' pin determines whether
 * the SPI data is an instruction for the display,
 * or pixel data for the framebuffer RAM.
 * Here, '0' means 'Command' and '1' means 'Data'.
 */
inline void sspi_cmd(uint8_t cdat) {
  // Pull the 'D/C' pin low, write data, pull 'D/C' high.
  GPIOB->ODR &= ~(1 << PB_DC);
  sspi_w(cdat);
  GPIOB->ODR |=  (1 << PB_DC);
}

/*
 * Initialize the SPI peripheral for use with a 4-wire display.
 */
void hspi_init() {
  // Ensure that the peripheral is disabled, and reset it.
  SPI1->CR1 &= ~(SPI_CR1_SPE);
  if (SPI1 == SPI1) {
    RCC->APB2RSTR |=  (RCC_APB2RSTR_SPI1RST);
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST);
  }
  // Use unidirectional simplex mode.
  //SPI1->CR1 &= ~(SPI_CR1_BIDIMODE |
  //               SPI_CR1_BIDIOE);
  // Set clock polarity/phase to 0/0?
  SPI1->CR1 &= ~(SPI_CR1_CPOL |
                 SPI_CR1_CPHA);
  //SPI1->CR1 |=  (SPI_CR1_CPHA);
  // Or 1/1 seems to work...
  SPI1->CR1 |=  (SPI_CR1_CPOL |
                 SPI_CR1_CPHA);
  // Set the STM32 to act as a host device.
  SPI1->CR1 |=  (SPI_CR1_MSTR);
  // Set software 'Chip Select' pin.
  SPI1->CR1 |=  (SPI_CR1_SSM);
  // (Set the internal 'Chip Select' signal.)
  SPI1->CR1 |=  (SPI_CR1_SSI);
  // Use MSB-first format.
  SPI1->CR1 &= ~(SPI_CR1_LSBFIRST);
  // I think that these bits are required for some reason.
  //SPI1->CR2 |=  (SPI_CR2_SSOE);
  // Set 8 bits per frame.

    // (The F0 series features configurable frame width.)
    SPI1->CR2 |= (SPI_CR2_DS);
    SPI1->CR2 &= ~(SPI_CR2_DS_3);
    //SPI1->CR2 |=  (0x7 << SPI_CR2_DS_3);
  // Set the Baud rate prescaler.
  SPI1->CR1 &= ~(SPI_CR1_BR);
  // Start slow? SPI_clock = Core_clock / (2 ^ (BR))
  // So, a value of 4 should slow things down by a factor of 16.
  //SPI1->CR1 |=  (0x4 << SPI_CR1_BR_Pos);
  // Enable the peripheral.
  SPI1->CR1 |=  (SPI_CR1_SPE);
}

/*
 * Send a byte of data over hardware SPI.
 * This method does not wait for the communication to finish.
 * (The STM32 has an onboard FIFO queue, so we can check
 *  whether that has space for writing instead.)
 */
void hspi_w8(uint8_t dat) {
  // Wait for TXE.
  while (!(SPI1->SR & SPI_SR_TXE)) {};
  // Send the byte.
  *(uint8_t*)&(SPI1->DR) = dat;
}

/*
 * Send 16 bits of data over hardware SPI.
 * This method does not wait for the communication to finish.
 * It adds two bytes to the FIFO queue at once; that's one
 * pixel for a 16-bit color display.
 *
 * On L0 platforms, packing 2 data frames at once does
 * not appear to be supported.
 */
void hspi_w16(uint16_t dat) {
  // Wait for TXE.
  while (!(SPI1->SR & SPI_SR_TXE)) {};
  // Send the data.
  // (Flip the bytes for the little-endian ARM core.)
  dat = (((dat & 0x00FF) << 8) | ((dat & 0xFF00) >> 8));
  *(uint16_t*)&(SPI1->DR) = dat;
}

/*
 * Send a 'command' byte over hardware SPI.
 * Pull the 'D/C' pin low, send the byte, then pull the pin high.
 * Wait for the transmission to finish before changing the
 * 'D/C' pin value.
 */
void hspi_cmd(uint8_t cmd) {
  while ((SPI1->SR & SPI_SR_BSY)) {};
  GPIOB->ODR &= ~(1 << PB_DC);
  hspi_w8(cmd);
  while ((SPI1->SR & SPI_SR_BSY)) {};
  GPIOB->ODR |=  (1 << PB_DC);
}
