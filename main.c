/*
 * Pong.c
 *
 * Created: 7/25/2023 10:51:14 AM
 * Author : Clbow
 */ 
 // Lab3P1.c
 //
 // Created: 1/30/2018 4:04:52 AM
 // Author : Your name
 // Copyright 2018, All Rights Reserved
 #define F_CPU 16000000UL
#include <math.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

void TIM1_COMPA();
void SET_SPEAKER_PARAMS();

char cycle = 0;
char freq_high = 0x03;
char freq_low = 0xF8;
char max_cycle_L = 120;
char max_cycle_H = 120;
char cycle_count_L = 0;
char cycle_count_H = 0;
char cycle_level = 0;


void Play_speaker(int freq, int len_ms){
	int freq_adj = 500000/freq+24;
	freq_high = (freq_adj>>8) & 0xff;
	freq_low = freq_adj & 0xff;
	cycle_count_L = 0;
	cycle_count_H = 0;
	cycle_level = 0;
	long count_cycle = (long)freq*(long)len_ms/1000;
	max_cycle_H = (count_cycle>>8) & 0xff;
	max_cycle_L = count_cycle & 0xff;
	SET_SPEAKER_PARAMS();
}

ISR(TIMER1_COMPA_vect){
	TIM1_COMPA();
}
int main(void)
{
	cli();
	while (1)
	{
		 Play_speaker(261,4000);
		 _delay_ms(5000);
		 Play_speaker(261,4000);
		 _delay_ms(5000);
		 Play_speaker(392,4000);
		 _delay_ms(5000);
		 Play_speaker(392,4000);
		 _delay_ms(5000);
		 Play_speaker(440,4000);
		 _delay_ms(5000);
		 Play_speaker(440,4000);
		 _delay_ms(5000);
		 Play_speaker(392,4000);
		 _delay_ms(5000);
		 _delay_ms(16000);
	}
}

