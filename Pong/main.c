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

int main(void)
{	
	cli();
	struct Player player[2];
	InitInputs(player);
	InitLCD();
	ResetBoard(player);
    while (1)
    {
	    PollInputs(player);
	    CheckInputs(player);
		ExecuteInputs(player);
		UpdateBoard(player);
		_delay_ms(100);
	}
}

