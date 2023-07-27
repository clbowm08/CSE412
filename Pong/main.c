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
	SendCommand(0x3C);
    while (1)
    {
	    PollInputs(player);
	    CheckInputs(player);
        //// Write a string to the LCD
        //char myString[] = "Hello, LCD!";
        //for (int i = 0; myString[i] != '\0'; i++)
        //{
	        //SendData(myString[i]);
	        //_delay_ms(100);
	    //}
	}
}

