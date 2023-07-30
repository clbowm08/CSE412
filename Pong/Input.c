/*
 * Input.c
 *
 * Created: 7/25/2023 11:45:55 AM
 *  Author: Clbow
 */ 
 #define F_CPU 16000000UL
#include "Input.h"
#include "Sound.h"
#include "LCD.h"
#include <avr/io.h>

#define PADDLE_VELOCITY 5

void InitInputs(struct Player *player)
{	
	//Initializing data direction register for button ports to be Inputs
	DDRC |= (0 << DDRC3);
	DDRC |= (0 << DDRC2);
	DDRC |= (0 << DDRC1);
	DDRC |= (0 << DDRC0);
	
	//Initializing ports of buttons to produce a signal enabling ()
	PORTC |= (1 << PORTC3);
	PORTC |= (1 << PORTC2);
	PORTC |= (1 << PORTC1);
	PORTC |= (1 << PORTC0);
	
	//Initializing LED output (CAN BE DELETED AFTER DEBUG PHASE)
	DDRB |= (1 << DDRB5);
	
	player[0].prevYCoord = 0;
	player[0].curYCoord = 0;
	player[1].prevYCoord = 0;
	player[1].curYCoord = 0;
}

void PollInputs(struct Player *player)
{
	//Poll for first button
	if (!(BUTTON_PORTS & FIRST_BUTTON_PIN_LOCATION))
	{
		player[0].downFlag = true;
	}
	else
	{
		player[0].downFlag = false;
	}
	
	//Poll for second button
	if (!(BUTTON_PORTS & SECOND_BUTTON_PIN_LOCATION))
	{
		player[0].upFlag = true;
	}
	else
	{
		player[0].upFlag = false;
	}
	
	//Poll for third button
	if (!(BUTTON_PORTS & THIRD_BUTTON_PIN_LOCATION))
	{
		player[1].downFlag = true;
	}
	else
	{
		player[1].downFlag = false;
	}
	
	//Poll for fourth button
	if (!(BUTTON_PORTS & FOURTH_BUTTON_PIN_LOCATION))
	{
		player[1].upFlag = true;
	}
	else
	{
		player[1].upFlag = false;
	}
}

void CheckInputs(struct Player *player)
{

	//checking for double inputs
	if ((player[0].downFlag == true) && (player[0].upFlag == true))
	{
		player[0].downFlag = false;
		player[0].upFlag = false;
	}
	if ((player[1].downFlag == true) && (player[1].upFlag == true))
	{
		player[1].downFlag = false;
		player[1].upFlag = false;
	}
	
	//Checking up flag boundaries
	if ((player[0].upFlag == true) && (player[0].curYCoord <= 1))
	{
		player[0].upFlag = false;
	}
	if ((player[1].upFlag == true) && (player[1].curYCoord <= 1))
	{
		player[1].upFlag = false;
	}
	
	//Checking down flag boundaries
	if ((player[0].downFlag == true) && (player[0].curYCoord >= 3))
	{
		player[0].downFlag = false;
	}
	if ((player[1].downFlag == true) && (player[1].curYCoord >= 3))
	{
		player[1].downFlag = false;
	}
}

void ExecuteInputs(struct Player *player, float deltaTime)
{
	player[0].prevYCoord = player[0].curYCoord;
	player[1].prevYCoord = player[1].curYCoord;
	if (player[0].upFlag)
	{	
		player[0].yPos -= PADDLE_VELOCITY * deltaTime;
	}
	if (player[0].downFlag)
	{
		player[0].yPos += PADDLE_VELOCITY * deltaTime;
	}
	if (player[1].upFlag)
	{
		player[1].yPos -= PADDLE_VELOCITY * deltaTime;
	}
	if (player[1].downFlag)
	{
		player[1].yPos += PADDLE_VELOCITY * deltaTime;
	}
	player[0].curYCoord = round(player[0].yPos);
	player[1].curYCoord = round(player[1].yPos);
}