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

volatile uint32_t milliseconds = 0;
volatile uint32_t previousTime = 0;

uint32_t myMillis() {
	uint32_t ms;
	// Disable interrupts to ensure atomic access to the variable
	cli();
	ms = milliseconds;
	// Enable interrupts back
	sei();
	return ms;
}

float GetDeltaTime()
{
	uint32_t currentTime = myMillis();
	uint32_t deltaTime = (currentTime - previousTime);
	previousTime = currentTime;
	return deltaTime;
}

void init_timer0() {
	// Set the timer mode to CTC (Clear Timer on Compare Match) mode
	TCCR0A |= (1 << WGM01);

	// Set the prescaler to 64 (adjust as needed for your application)
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Calculate the compare match value (OCR0A) for 1 ms interrupt period
	OCR0A = (F_CPU / (64UL * 1000)) - 1;

	// Enable TIMER0 compare match interrupt
	TIMSK0 |= (1 << OCIE0A);

	// Enable global interrupts
	sei();
}

// TIMER0 compare match interrupt handler
ISR(TIMER0_COMPA_vect) {
	milliseconds++;
}

int main(void)
{	
	//_delay_ms(1000);
	cli();
	init_timer0();
	float deltaTime = (GetDeltaTime() / 1000.0);
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
		ExecuteInputs(player, deltaTime);
		reflect_paddles(player[0].xPos,player[0].yPos,player[1].xPos,player[1].yPos,ball);
		UpdateBallPosVel(ball, deltaTime);
		char resetDeltaTime = 0;
		DetectUpdateScore(player, ball, &resetDeltaTime);
		if (resetDeltaTime == 1)
		{
			deltaTime = (GetDeltaTime() / 1000);
			deltaTime = (GetDeltaTime() / 1000);
		}
		UpdateBoard(player,ball);
		deltaTime = (GetDeltaTime() / 1000);
	}
}



