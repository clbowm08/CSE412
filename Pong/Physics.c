/*
 * CFile1.c
 *
 * Created: 7/28/2023 3:30:44 PM
 *  Author: Joey Lyvers
 */ 
#include "Physics.h"
//#include "Input.h"
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
}
void UpdateBallPosVel(struct Ball *ball){
	UpdateBallVel(ball);
	ball[0].xPos +=ball[0].xVel;
	ball[0].yPos +=ball[0].yVel;
}
void UpdateBallVel(struct Ball *ball){
	if (ball[0].xPos == xmin & ball[0].xVel<0){
		ball[0].xVel = -1*ball[0].xVel;
		//Play_speaker(440,500);
	}
	if (ball[0].xPos == xmax & ball[0].xVel>0){
		ball[0].xVel = -1*ball[0].xVel;
		//Play_speaker(440,500);
	}
	if (ball[0].yPos == ymin & ball[0].yVel<0){
		ball[0].yVel = -1*ball[0].yVel;
		bounce_sound();
	}
	if (ball[0].yPos == ymax & ball[0].yVel>0){
		ball[0].yVel = -1*ball[0].yVel;
		bounce_sound();
	}
}
void reflect_paddles(unsigned char p1_x,unsigned char p1_y,unsigned char p2_x, unsigned char p2_y,struct Ball *ball){
	if((ball[0].xPos==p1_x+3)&(ball[0].xVel<0) &((ball[0].yPos == p1_y )|(ball[0].yPos == p1_y+1 )))
	{
		ball[0].xVel = -1*ball[0].xVel;
		paddle_sound();
	}
	if((ball[0].xPos==p2_x+1)&(ball[0].xVel>0) &((ball[0].yPos == p2_y )|(ball[0].yPos == p2_y+1 )))
	{
		ball[0].xVel = -1*ball[0].xVel;
		paddle_sound();
	}
	
}