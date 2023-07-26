 // PONG Project

 #define F_CPU 16000000UL
 
#include <math.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Input.h"
#include "LCD.h"

int main(void)
{
	cli();
	struct Player player[2];
	InitInputs(player);
	InitLCD();
	SendCommand(0x08);
    while (1)
    {
	    PollInputs(player);
	    CheckInputs(player);

	    // Clear the display before writing the string
	    SendCommand(0x08);
		if (TWSR0 == 0x68)
		{
			PORTB = (1 << PORTB5);
		}
		else
		{
			PORTB = (0 << PORTB5);
		}
	}
}

