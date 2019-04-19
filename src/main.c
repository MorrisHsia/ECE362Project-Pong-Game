/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
			

/*void init_SPI(){


    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODER12_1 | GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1 | GPIO_MODER_MODER15_1 ; // Set PB12, 13, 15 as AF
    GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH4; // SET PB12 TO AF0
    GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH5; // SET PB13 TO AF0
    GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH6; // SET PB14 TO AF0
    GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH7; // SET PB15 TO AF0

    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; // Enable SPI2

    SPI2->CR1 &= ~SPI_CR1_SPE; // Disable SPI2

    // Bits 5:3: Baud rate control - slowest possible (48MHz/256)
    SPI2->CR1 = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;

    // Bit 2: Master Selection (1: Master configuration)
    SPI2->CR1 |= SPI_CR1_MSTR;

    // Bit 1: Clock polarity (0: CK to 0 when idle)
    SPI2->CR1 &= ~SPI_CR1_CPOL;

    // Bit 0: Clock phase (0: first clock transition is the first data capture edge)
    SPI2->CR1 &= ~SPI_CR1_CPHA;




}*/

int main(void)
{


    printf("Hello World");

	for(;;);
}
