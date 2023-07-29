 // PONG Project

 #define F_CPU 16000000UL
 
#include <math.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Input.h"
#include "LCD.h"
#include "BoardManager.h"
#include "Physics.h"

int main(void)
{	
	//_delay_ms(1000);
	cli();
	struct Player player[2];
	InitInputs(player);
	struct Ball ball[1];
	init_ball(ball,10,2,1,1);
	InitLCD();
	ResetBoard(player);
    while (1)
    {
	    PollInputs(player);
	    CheckInputs(player);
		ExecuteInputs(player);
		reflect_paddles(player[0].xPos,player[0].yPos,player[1].xPos,player[1].yPos,ball);
		UpdateBallPosVel(ball);
		UpdateBoard(player,ball);
		DetectUpdateScore(player,ball);
		_delay_ms(200);
	}
}

