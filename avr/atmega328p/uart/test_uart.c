/**
 * This file contains bare-metal code for 
 * testing of USART peripheral on the 
 * ATMega328p (on Arduino Nano board)
 * */

/* Header file inclusions
 * */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/*
 * All pre-procesor directives defined here
 * */
#define FOSC       F_CPU
#define BAUD       115200L
#define UBRR_VAL   ( FOSC / 16 / BAUD )


/**
 * Global variable definitions
 * */
volatile unsigned char rx_cir_buff[50] = {0};
volatile unsigned int  rx_cnt = 0; // Rx counter
volatile unsigned int  tx_cnt = 0; // Tx counter


/*
 * ********* Interrupt Service Routines ************
 **/

/* 
 * USART0 RX (Complete) ISR
 * */
ISR ( USART_RX_vect ) {

	if ( rx_cnt >= sizeof(rx_cir_buff) )
	       rx_cnt = 0; //resetting to zero after hitting max size of buffer
	
	rx_cir_buff[rx_cnt++] = UDR0; //read data from Rx buffer
		 
}

/**
 * USART0 (TX) Data-Register-Empty ISR 
 * */
ISR ( USART_UDRE_vect ) {

	if ( tx_cnt < sizeof(rx_cir_buff) ) {
		UDR0 = rx_cir_buff[tx_cnt]; //write to USART data reg
		rx_cir_buff[tx_cnt] = 0; //clear entry from Rx buffer after writing to Tx buffer
		tx_cnt++;
	}

}


/* 
 * USART-0 setup  
 * */
void usart0_setup ( unsigned int ubrr ) {

	cli(); // disable all interrupts

	UBRR0H = (unsigned char)( ubrr >> 8 );
	UBRR0L = (unsigned char) ubrr;
	UCSR0A = 0x00; // init A
	UCSR0B = 0x00; // init B
	/* Enable Tx and Rx */
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
	UCSR0C = 0x00; // init C
	/* Set Asynch mode, 8N1 config for USART  */
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);

	sei(); // enable all  interrupts
}


/* 
 * Main program execution 
 * */
int main ( void ) {

	usart0_setup( UBRR_VAL );

	/* Loop forever....*/
	for ( ; ; ) { 
		
		if ( rx_cnt > 0 ) {

			while ( tx_cnt < rx_cnt )
				UCSR0B |= _BV(UDRIE0); // enable Tx UDRE Interrupt as we still have data in Rx buffer

			UCSR0B &= ~_BV(UDRIE0); // disable Tx UDRE Interrupt as Rx buffer is empty
			rx_cnt = 0; // reset Rx counter
			tx_cnt = 0; // reset Tx counter

		}

		_delay_ms( 1000 ); //unconditional long delay in the main loop helps to test buffering of data between RX and TX
	}

	return (0);
}

