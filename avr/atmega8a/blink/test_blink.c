/* 
 * This file contains bare-metal code for 
 * blinking inbuilt LED on PORTB5 of 
 * ATMega328p (on Arduino Nano board)
 * 
 * */

#include <avr/io.h>
#include <util/delay.h>


/*
 * All pre-procesor directives defined here
 * */


/* 
 * Main program execution 
 * */
int main ( void ) {

	DDRB |= _BV(DDB0);

	for(;;){ // loop forever...

		PORTB |= _BV(PB0);
		_delay_ms(500);
		PORTB &= ~_BV(PB0);
		_delay_ms(2000);
	}
}

