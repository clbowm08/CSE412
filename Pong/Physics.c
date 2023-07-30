/*
 * CFile1.c
 *
 * Created: 7/28/2023 3:30:44 PM
 *  Author: Joey Lyvers
 */ 
#include "Physics.h"
#include "Sound.h"
#define xmax 20
#define ymax 4
#define xmin 1
#define ymin 1

void init_ball(struct Ball *ball, unsigned char xpos, unsigned char ypos, signed char xvel,signed char yvel){
	ball[0].xPos = xpos;
	ball[0].yPos = ypos;
	ball[0].xVel = xvel;
	ball[0].yVel = yvel;
	ball[0].curXCoord = 0;
	ball[0].curYCoord = 0;
	ball[0].prevXCoord = 0;
	ball[0].prevYCoord = 0;
	ball[0].speedOfBall = 1;
}
void UpdateBallPosVel(struct Ball *ball, float deltaTime){
	UpdateBallVel(ball);
	ball[0].prevXCoord = ball[0].curXCoord;
	ball[0].prevYCoord = ball[0].curYCoord; 
	
	ball[0].xPos +=(ball[0].xVel * deltaTime * ball[0].speedOfBall);
	ball[0].yPos +=(ball[0].yVel * deltaTime * 5);
	
	ball[0].curXCoord = round(ball[0].xPos);
	ball[0].curYCoord = round(ball[0].yPos);
}
void UpdateBallVel(struct Ball *ball){
	if ((ball[0].yPos <= ymin) && (ball[0].yVel<0)){
		ball[0].yVel = -1*ball[0].yVel;
		bounce_sound();
	}
	if ((ball[0].yPos >= ymax) && (ball[0].yVel>0)){
		ball[0].yVel = -1*ball[0].yVel;
		bounce_sound();
	}
}
void reflect_paddles(struct Player *player, struct Ball *ball){
	if(((ball[0].curXCoord <= (player[0].xPos + 3)) && (ball[0].xVel < 0)) && ((ball[0].curYCoord >= player[0].curYCoord) && (ball[0].curYCoord <= player[0].curYCoord + 1)))
	{
		ball[0].xVel = -1 * ball[0].xVel;
		paddle_sound();
		ball[0].speedOfBall += 1;
	}
	if(((ball[0].curXCoord > (player[1].xPos)) && (ball[0].xVel > 0)) && ((ball[0].curYCoord >= player[1].curYCoord) && (ball[0].curYCoord <= player[1].curYCoord + 1)))
	{
		ball[0].xVel = -1 * ball[0].xVel;
		paddle_sound();
		ball[0].speedOfBall += 1;
	}
	
}