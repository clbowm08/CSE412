/*
 * Physics.h
 *
 * Created: 7/28/2023 3:31:46 PM
 *  Author: Joey Lyvers
 */ 


#ifndef PHYSICS_H_
#define PHYSICS_H_

typedef struct Ball{
	unsigned char xPos;
	unsigned char yPos;
	signed char xVel;
	signed char yVel;
}Ball_t;
void UpdateBallPosVel(struct Ball *ball);
void init_ball(struct Ball *ball, unsigned char xpos, unsigned char ypos, signed char xvel,signed char yvel);
void reflect_paddles(unsigned char p1_x,unsigned char p1_y,unsigned char p2_x, unsigned char p2_y,struct Ball *ball);

#endif /* PHYSICS_H_ */