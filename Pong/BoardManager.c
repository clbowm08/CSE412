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
}

void UpdateBoard(struct Player *player)
{
	SendCommand(0x01);
	SendCommand(0x02);
	SetCursorPosition(player[0].xPos, player[0].yPos);
	SendData(0x7C);
	SetCursorPosition((player[0].xPos), (player[0].yPos + 1));
	SendData(0x7C);
	SetCursorPosition(player[1].xPos, player[1].yPos);
	SendData(0x7C);
	SetCursorPosition(player[1].xPos, (player[1].yPos + 1));
	SendData(0x7C);
}