/*
 * CFile1.c
 *
 * Created: 7/25/2023 10:39:40 AM
 *  Author: Joey Lyvers
 */ 
#include <math.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Sound.h"

#define F_CPU 16000000UL

int g_freq = 120;//integer global frequency
char freq_high = 0x03; //8 bit equivalents to integer
char freq_low = 0xF8; 
char max_cycle_L = 120;//maximum number of timer cycles for sound, determines length of noise, 2 8bits
char max_cycle_H = 120;
char cycle_count_L = 0;//counts clock timer for sound up to maximum
char cycle_count_H = 0;
char cycle_level = 0; //variable to track which side of duty cycle sound is on

void Play_speaker(int freq, int len_ms){
	int freq_adj = 500000/freq+30; //calculate the timing ofcycles, needs offset to prevent error at small values
	freq_high = (freq_adj>>8) & 0xff;//bitshifting to change integer to char
	freq_low = freq_adj & 0xff;
	cycle_count_L = 0;//set cycles to zero
	cycle_count_H = 0;
	cycle_level = 0;
	int count_cycle = (long)freq*(long)len_ms/1000;//integer number for maximum cycles, need long cast to prevent intermediate overflow value
	max_cycle_H = (count_cycle>>8) & 0xff;//bitshift int to chars
	max_cycle_L = count_cycle & 0xff;
	SET_SPEAKER_PARAMS();//set timer values
}

ISR(TIMER1_COMPA_vect){
	TIM1_COMPA();//calls assembly interrupt handle
}
void TIM1_COMPA();
	
void SET_SPEAKER_PARAMS()
{
	cli();//turn off interrupts
	DDRB |= (1<<PORTB1);//set pin B1 to output for sound
	TCCR1A = 0xC0;
	TCCR1B = 0x01;//clk/8 time
	TCCR1C = 0x80;
	TCCR1A = 0x40;
	int tcount = TCNT1L + (TCNT1H<<8);//get clock value
	tcount = tcount + g_freq; //increase clock value
	OCR1AL = tcount & 0xff;//load to output compare registers
	OCR1AH = (tcount>>8) & 0xff;
	cycle_level = 0;///reset cycle level
	TIMSK1 = 0x02;//set interrupts
	TIFR1 = 0x02;
	sei();//enable global interrupts
}

void score_sound(){
	Play_speaker(400,1000);
	_delay_ms(8000);
	Play_speaker(440,1000);
	_delay_ms(8000);
	Play_speaker(380,1000);
	_delay_ms(8000);
}
	
void bounce_sound(){
	Play_speaker(120,500);
}
void paddle_sound(){
	Play_speaker(240,500);
}
