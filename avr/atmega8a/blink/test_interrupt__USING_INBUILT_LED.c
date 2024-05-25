/* 
 * This file contains bare-metal code for 
 * blinking inbuilt LED on PORTB5 of 
 * ATMega328p (on Arduino Nano board)
 * 
 * */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 * All pre-procesor directives defined here
 * */
#define FALSE 0
#define TRUE  1
/*
 * F_CPU @16MHz. prescaler of 1024, we get timer-clk-freq of 16000000/1024 = 15625 Hz 
 * OR the Compare reg value = 15625-1 = 15624(0x3D08) timer ticks per second
 * */
#define TIMER_MAX_VAL 0x03D0 //62.5ms 
//#define TIMER_MAX_VAL 0x07A1 //125ms 
//#define TIMER_MAX_VAL 0x0F42 //250ms 
//#define TIMER_MAX_VAL 0x1E84 //500ms 
//#define TIMER_MAX_VAL 0x3D08 //1sec 

/**
 * Global definition
 * */
volatile unsigned char t1_hit = FALSE;



/**
 * Timer-1 interrupt service routine
 * */
ISR ( TIMER1_COMPA_vect ) {
	t1_hit = TRUE;
}

/*
 * Timer-1 setup
 * */
void timer1_setup( void ) {
	/* Timer-1 as CTC setup */
	cli();
	OCR1A  = TIMER_MAX_VAL; // Set Timer resolution to be compared against the TCNT1
	TCCR1A = 0x00; // Normal PORT operation OR intialize
	TCCR1B = 0x00; // Initialize
	//TCCR1C = 0x00; // NA
	TCNT1  = 0x000; // Initialize counter to BOTTOM
	TIFR   |= _BV(OCF1A); // clear Output Compare Interrupt flag (if set)
	TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10); // CTC1 mode enabled,  CLK/1024 pre-scaler set

	/* Enable interrupts for Timer-1 Output compare events */
	TIMSK  |= _BV(OCIE1A); // Output Compare Interrupt Enable  
	sei(); // global interrupt enable flag in SREG
}

/* 
 * Main program execution 
 * */
int main ( void ) {

	timer1_setup();
	DDRB |= _BV(DDB5); // setting PORTB5 pin as output
	

	/*Loop forever....*/
	for ( ; ; ) { 
		if ( TRUE == t1_hit ) {
			t1_hit = FALSE;
			PORTB = (PORTB & _BV(PB5)) ? (PORTB & ~_BV(PB5)) : (PORTB | _BV(PB5)); //Toggle PORTB5 pin
		} else {
			_delay_ms(50);
		}

	}
}

