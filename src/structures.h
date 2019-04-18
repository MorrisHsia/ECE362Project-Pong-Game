#ifndef STRUCTURES_H_   /* Include guard */
#define STRUCTURES_H_

/*
 *  Pong game paddle
 */
typedef struct Paddle {
    short x, y, speed, score;
} Paddle;

/*
 *  Pong game moving ball
 */
typedef struct Ball {
    short x, y, speedX, speedY;
} Ball;

#endif // STRUCTURES_H_
