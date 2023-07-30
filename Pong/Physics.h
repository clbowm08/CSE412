/*
 * Physics.h
 *
 * Created: 7/28/2023 3:31:46 PM
 *  Author: Joey Lyvers
 */ 

#include "Input.h"

#ifndef PHYSICS_H_
#define PHYSICS_H_

typedef struct Ball{
	float xPos;
	float yPos;
	
	unsigned char curXCoord;
	unsigned char curYCoord;
	unsigned char prevXCoord;
	unsigned char prevYCoord;
	
	unsigned char speedOfBall;
	
	signed char xVel;
	signed char yVel;
}Ball_t;
void UpdateBallPosVel(struct Ball *ball, float deltaTime);
void init_ball(struct Ball *ball, unsigned char xpos, unsigned char ypos, signed char xvel,signed char yvel);
void reflect_paddles(struct Player *player, struct Ball *ball);

#endif /* PHYSICS_H_ */