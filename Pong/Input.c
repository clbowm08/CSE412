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

void InitInputs(struct Player *player)
{
	//Initializing Player Struct
	player[0].downFlag = false;
	player[0].upFlag = false;
	player[1].downFlag = false;
	player[1].upFlag = false;
	
	//Initializing data direction register for button ports to be Inputs
	DDRC |= (0 << DDRC5);
	DDRC |= (0 << DDRC4);
	DDRC |= (0 << DDRC3);
	DDRC |= (0 << DDRC2);
	
	//Initializing ports of buttons to produce a signal enabling ()
	PORTC |= (1 << PORTC3);
	PORTC |= (1 << PORTC2);
	PORTC |= (1 << PORTC1);
	PORTC |= (1 << PORTC0);
	
	//Initializing LED output (CAN BE DELETED AFTER DEBUG PHASE)
	DDRB |= (1 << DDRB5);
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
	
	//Temp tings
	bool lightOn = false;
	if (player[0].downFlag == true)
	{
		lightOn = true;
	}
	if (player[0].upFlag == true)
	{
		lightOn = true;
	}
	if (player[1].downFlag == true)
	{
		lightOn = true;
	}
	if (player[1].upFlag == true)
	{
		lightOn = true;
	}
	
	if (lightOn)
	{
		PORTB = (1 << PORTB5);
		SendCommand(0x0E);
	}
	else
	{
		PORTB = (0 << PORTB5);
	}
}