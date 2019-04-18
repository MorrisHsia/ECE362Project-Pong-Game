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

#include "structures.h"

// GLOBAL VARIABLE

Paddle p1, p2;
Ball ball;
			

void init_game(){

    p1.x = 0;
    p1.y = 0;
    p1.score = 0;

    p2.x = 0;
    p2.y = 320;
    p2.score = 0;

    ball.x = 120;
    ball.y = 160;
    ball.speedX = 2;
    ball.speedY = 1;
}


int main(void)
{
    printf("Hello World\n");

    // Set up the game
    init_game();

    // Enabling buttons and timers
    enableButtons();

	for(;;);

	return 0;
}
