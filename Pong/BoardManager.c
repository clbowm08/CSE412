/*
 * BoardManager.c
 *
 * Created: 7/28/2023 10:29:07 AM
 *  Author: Clbow
 */ 
#define F_CPU 16000000UL
#include "LCD.h"
#include <stdbool.h>
#include "Input.h"
#include <util/delay.h>
#include "Physics.h"
#include "Sound.h"

void ResetBoard(struct Player *player)
{
	player[0].downFlag = false;
	player[0].upFlag = false;
	player[1].downFlag = false;
	player[1].upFlag = false;
	
		
	player[0].xPos = 0;
	player[0].yPos = 2;
	player[1].xPos = 17;
	player[1].yPos = 2;
	
	player[0].score = 0;
	player[1].score = 0;
}

void UpdateBoard(struct Player *player,struct Ball *ball)
{
	_delay_ms(3);
	SendCommand(0x02);
	printscore(player[0].score,3);
	printscore(player[1].score,16);
	if ((ball[0].curXCoord != ball[0].prevXCoord) || (ball[0].curYCoord != ball[0].prevYCoord))
	{
		//Clear the ball from screen
		SetCursorPosition(ball[0].prevXCoord, ball[0].prevYCoord);
		SendData(' ');
		
		SetCursorPosition(ball[0].curXCoord, ball[0].curYCoord);
		SendData('o');
	}
	
	if (player[0].curYCoord != player[0].prevYCoord)
	{
		//clearing what needs to be cleared
		SetCursorPosition(2, player[0].prevYCoord);
		SendData(' ');
		SetCursorPosition(2, (player[0].prevYCoord + 1));
		SendData(' ');
		
		//Sending updated location
		SetCursorPosition(2, player[0].curYCoord);
		SendData(0x7C);
		SetCursorPosition(2, (player[0].curYCoord + 1));
		SendData(0x7C);
	}
	
	if (player[1].curYCoord != player[1].prevYCoord)
	{
		//clearing what needs to be cleared
		SetCursorPosition(19, player[1].prevYCoord);
		SendData(' ');
		SetCursorPosition(19, (player[1].prevYCoord + 1));
		SendData(' ');
		
		//Sending updated location
		SetCursorPosition(19, player[1].curYCoord);
		SendData(0x7C);
		SetCursorPosition(19, (player[1].curYCoord) + 1);
		SendData(0x7C);
	}
}
void printscore(unsigned char score, unsigned char xpos){
	SetCursorPosition(xpos+2,1);
	unsigned char out = (score%10)+48;
	SendData(out);
	if(score<10){
		return;
	}
	SetCursorPosition(xpos+1,1);
	out = (score%100)/10+48;
	SendData(out);
	if(score<100){
		return;
	}
	SetCursorPosition(xpos,1);
	out = score/100+48;
	SendData(out);
}
DetectUpdateScore(struct Player *player,struct Ball *ball, char *resetDeltaTime){
	if((ball[0].curXCoord <= 1) && (ball[0].xVel < 0)){
		player[1].score+=1;
		ball[0].xPos +=10; 
		ball[0].speedOfBall = 1;
		score_sound();
		_delay_ms(3000);
		*resetDeltaTime = 1;
		
	}
	if((ball[0].curXCoord >= 20) && (ball[0].xVel > 0)){
		player[0].score+=1;
		ball[0].xPos -=10;
		ball[0].speedOfBall = 0;
		score_sound();
		_delay_ms(2500);
		*resetDeltaTime = 1;
	}
}