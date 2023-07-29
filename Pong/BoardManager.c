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
	SendCommand(0x01);
	_delay_ms(3);
	SendCommand(0x02);
	printscore(player[0].score,3);
	printscore(player[1].score,16);
	SetCursorPosition(ball[0].xPos,ball[0].yPos);
	SendData('o');
	SetCursorPosition(player[0].xPos+2, player[0].yPos);
	SendData(0x7C);
	SetCursorPosition((player[0].xPos)+2, (player[0].yPos + 1));
	SendData(0x7C);
	SetCursorPosition(player[1].xPos+2, player[1].yPos);
	SendData(0x7C);
	SetCursorPosition(player[1].xPos+2, (player[1].yPos + 1));
	SendData(0x7C);

	//SetCursorPosition(ball[0].xPos,ball[0].yPos);
	//SendData(0x01);
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
DetectUpdateScore(struct Player *player,struct Ball *ball){
	if(ball[0].xPos == 1){
		player[1].score+=1;
		ball[0].xPos +=10; 
		score_sound();
		_delay_ms(3000);
		
		
	}
	if(ball[0].xPos == 20){
		player[0].score+=1;
		ball[0].xPos -=10;
		score_sound();
		_delay_ms(2500);
		
	}
}