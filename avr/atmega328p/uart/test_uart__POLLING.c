/* 
 * This file contains bare-metal code for 
 * testing of USART peripheral on the 
 * ATMega328p (on Arduino Nano board)
 * */

/* Header file inclusions
 * */
#include <avr/io.h>
#include <util/delay.h>


/*
 * All pre-procesor directives defined here
 * */
#define FOSC       F_CPU
#define BAUD       115200L
#define UBRR_VAL   ( FOSC / 16 / BAUD )


/**
 * Global definition
 * */


/* 
 * USART-0 setup  
 * */
void usart0_setup ( unsigned int ubrr ) {

	UBRR0H = (unsigned char)( ubrr >> 8 );
	UBRR0L = (unsigned char) ubrr;
	UCSR0A = 0x00; // init A
	UCSR0B = 0x00; // init B
	/* Enable Tx and Rx */
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0);// | _BV(RXCIE0);
	UCSR0C = 0x00; // init C
	/* Set Asynch mode, 8N1 config for USART  */
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);

}

/*
 * Transmit character on USART0 (polling method)
 * */
void uart_transmit ( unsigned char data ) {

	while ( !( UCSR0A & _BV(UDRE0) ) ) _delay_ms( 50 );

	UDR0 = data;
}

/*
 * Receive char on USART0 (polling method)
 * */
unsigned char uart_receive ( void ) {

	while ( !( UCSR0A & _BV(RXC0) ) ) _delay_ms( 50 );

	return UDR0;
}


/* 
 * Main program execution 
 * */
int main ( void ) {

	unsigned char rxbuff;

	usart0_setup( UBRR_VAL );

	/*Loop forever....*/
	for ( ; ; ) {
		rxbuff = 0;
		rxbuff = uart_receive();
		uart_transmit( rxbuff );

		_delay_ms( 50 );

	}

	return 0;
}

