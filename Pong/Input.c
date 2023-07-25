/*
 * Input.c
 *
 * Created: 7/25/2023 11:45:55 AM
 *  Author: Clbow
 */ 
#include "Input.h"
#include <avr/io.h>

void PollInputs()
{
	
	if (!(PINC & (1 << PINC5)))
	{
		PORTB = (1 << PORTB5);
	}
}