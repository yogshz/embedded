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

	DDRB |= _BV(DDB5);

	for(;;){ // loop forever...

		PORTB |= _BV(PB5);
		_delay_ms(200);
		PORTB &= ~_BV(PB5);
		_delay_ms(200);
	}
}

