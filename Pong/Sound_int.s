
/*
 * Sound_int.s
 *
  // Created: 1/30/2018 4:15:16 AM
 // Author : Eugene Rockey
 // Copyright 2018, All Rights Reserved

 * Created: 7/25/2023 3:59:36 PM
 *  Author: Joey Lyvers
 */ 
 .section ".data"					
.equ	DDRB,0x04					
.equ	PORTB,0x05					
.equ	TCCR1A, 0x80
.equ	TCCR1B, 0x81
.equ	TCCR1C, 0x82
.equ	TCNT1L, 0x84
.equ	TCNT1H, 0x85
.equ	OCR1AH, 0x89
.equ	OCR1AL, 0x88
.equ	TIMSK1, 0x6F
.equ	TIFR1, 0x36
.global freq_high			//variable for setting frequency of sound H
.global freq_low			//L
.global max_cycle_L			//maximum number of sound cycles for timing
.global max_cycle_H	
.global cycle_count_L			//count of cycles
.global cycle_count_H
.global cycle_level			
.section ".text"			

.global TIM1_COMPA
TIM1_COMPA:
		lds		r19, cycle_level
		sbrc	r19,0				
		rjmp	ONE					
		lds		r25, freq_low			
		lds		r18, freq_high			
		ldi		r19,1				
		rjmp	BEGIN				
ONE:	lds		r25,freq_low			
		lds		r18,freq_high			
		ldi		r19,0				

		lds		r20, max_cycle_L//one side of cycle, load and compares cycle to max
		lds		r21, max_cycle_H
		lds		r22, cycle_count_L
		lds		r23, cycle_count_H
		ldi     r24, 0x1
		add     r22,r24
		adc		r23,r19
		sts		cycle_count_L,r22
		sts		cycle_count_H,r23
		cp		r20,r22
		cpc		r21,r23
		brge	BEGIN
		cli						//at max, disable interrups
		ldi r26,0x00			
		sts TIMSK1,r26			
		out TIFR1,r26	
		ldi r26,0x00			
		sts TCCR1A,r26//turn off B1 output pin
		sei

BEGIN:	lds		r26,OCR1AL			
		add		r25,r26			
		lds		r26,OCR1AH			
		adc		r18,r26				
		sts		OCR1AH,r18			
		sts		OCR1AL,r25			
		sbrc r19,0
		rjmp Return
Return:
	sts cycle_level,r19
	ret

		.end
