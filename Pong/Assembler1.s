
/*
 * Assembler1.s
 *
 * Created: 7/25/2023 10:53:38 AM
 *  Author: Clbow
 */ 

 
.section ".data"					//student comment here
.equ	DDRB,0x04					//student comment here
.equ	DDRD,0x0A					//student comment here
.equ	PORTB,0x05					//student comment here
.equ	PORTD,0x0B					//student comment here
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
.global cycle_level			//duty cycle container

.section ".text"			//student comment here


.global SET_SPEAKER_PARAMS
SET_SPEAKER_PARAMS:
		cli
		ldi	r16,0xFF				;PB1 or OC1A Output
		out	DDRB,r16
;initialize and start Timer A, compare match, interrupt enabled
		ldi	r16,0xC0			;set OC to compare match set output to high level
		sts TCCR1A,r16			;timer 1 control register a, Set OC1A/OC1B on compare match
		ldi r16,0x01			;set clock prescaler
		sts TCCR1B,r16			;timber 1 control register b, clk io/64
		ldi r16,0x80			;force output compare, set PB1 high
		sts TCCR1C,r16			;student comment here
		ldi r16,0x40			;Student comment here
		sts TCCR1A,r16			;student comment here
		lds r18, freq_high
		lds r17, freq_low
		lds r16,TCNT1L			;student comment here
		add r17,r16				;student comment here
		lds r16,TCNT1H			;student comment here
		adc r18,r16				;student comment here
		sts OCR1AH,r18			;student comment here
		sts OCR1AL,r17			;student comment here
		ldi r19,0				;student comment here
		ldi r16,0x02			;student comment here
		sts TIMSK1,r16			;student comment here
		out TIFR1,r16			;student comment here
		sei						;student comment here
ret

.global TIM1_COMPA
TIM1_COMPA:
		lds		r19, cycle_level
		sbrc	r19,0				;student comment here
		rjmp	ONE					;student cmment here
		lds		r17, freq_low			;student comment here
		lds		r18, freq_high			;student comment here
		ldi		r19,1				;student comment here
		rjmp	BEGIN				;student comment here	
ONE:	lds		r17,freq_low			;student comment here
		lds		r18,freq_high			;student comment here
		ldi		r19,0				;student comment here

		lds		r20, max_cycle_L
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
		cli
		ldi r16,0x00			;student comment here
		sts TIMSK1,r16			;student comment here
		out TIFR1,r16	
		ldi r16,0x00			;Student comment here
		sts TCCR1A,r16
		sei

BEGIN:	lds		r16,OCR1AL			;student comment here
		add		r17,r16				;student comment here
		lds		r16,OCR1AH			;student comment here
		adc		r18,r16				;student comment here
		sts		OCR1AH,r18			;student comment here
		sts		OCR1AL,r17			;student comment here
		sbrc r19,0
		rjmp Return
Return:
	sts cycle_level,r19
	ret

		.end