/* 
 * This file contains bare-metal code for 
 * blinking inbuilt LED on PORTB5 of 
 * ATMega328p (on Arduino Nano board)
 * 
 * */


/*
 * All pre-procesor directives defined here
 * */
#define PORTB   *((volatile unsigned char*)0x25) // Register @0x25 represents PORTB
#define DDRB    *((volatile unsigned char*)0x24) // Register @0x24 represents direction for PORTB
#define BIT(n)  (1 << n)

/* 
 * Hardcoded delay for few milli-seconds 
 * */
void delay_few_msec( void ) {

	for (long d = 0; d < 70000; d++)
		__asm__("nop");
}

/* 
 * Hardcoded delay for few seconds
 * */
void delay_few_sec( void ) {

	for (long d = 0; d < 900000; d++)
		__asm__("nop");
}

/* 
 * Main program execution 
 * */
int main ( void ) {

	DDRB |= BIT(5); // only set direction bit for PORTB5 as output (1)

	for(;;){ // loop forever...

		PORTB |= BIT(5);  // set PORTB5 to high
		delay_few_msec();
		PORTB &= ~BIT(5); // set PORTB5 to low
		delay_few_sec();
	}
}

