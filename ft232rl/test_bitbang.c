#include <stdio.h>
#include <unistd.h>
#include <libftdi1/ftdi.h>

/* The 8-bit word implies the following pins:
   RIN(D7)    0x80 
   DCD(D6)    0x40   
   DSR(D5)    0x20
   DTR(D4)    0x10
   CTS(D3)    0x08
   RTS(D2)    0x04
   RXD(D1)    0x02
   TXD(D0)    0x01
 */
#define PIN_STAT ((unsigned char)(0x10 | 0x02 | 0x01 | 0x04)) // DTR,RXD,TXD,RTS

int main()
{
						/* ALL(ON) DTR(ON), RXD(ON),TXD(ON), RTS(ON) */
	unsigned char c[] = {PIN_STAT, 0x10,    0x02,      0x01, 0x04};
	unsigned int itr = 0;
	int ret = -1;
	unsigned char rdbuf[10] = {0};
		/* ctx is the FTDI context, we'll use this to control the
		*      * FTDI devices later. We'd need to initialise it first
		*           */
	struct ftdi_context ctx;
	if (ftdi_init(&ctx) < 0) {
		printf("failed to initialize device: %s\n", ftdi_get_error_string(&ctx));
		return 1;
	}
	/*  Open FTDI Devices based on FTDI VID/PID */
	if (ftdi_usb_open(&ctx, 0x0403, 0x6001) < 0) {
			printf("Can't open device: %s\n", ftdi_get_error_string(&ctx));
				return 1;
	}
	/* Enable bitbang mode for all output lines */
	if (ftdi_set_bitmode(&ctx, PIN_STAT, BITMODE_BITBANG/*BITMODE_SYNCBB*/) < 0) {
		printf("Failed to set bitbang mode: %s\n", ftdi_get_error_string(&ctx));
		return 1;
	}
		/* Endless loop: invert LED state, 
	*     * write output, pause 1 second */
	for(;;) {

				if (ftdi_write_data(&ctx, &c[itr], 1) < 0) {
					printf("Failed to write data: %s\n", ftdi_get_error_string(&ctx));
					return 1;
				}
				itr = (itr < (sizeof(c)/sizeof(*c))) ? (itr + 1) : 0;
				usleep(200000); /* pause for 200000 microseconds*/
				
				if (ftdi_write_data(&ctx, &c[itr], 1) < 0) {
					printf("Failed to write data: %s\n", ftdi_get_error_string(&ctx));
					return 1;
				}
				itr = (itr < (sizeof(c)/sizeof(*c))) ? (itr + 1) : 0;
				usleep(200000); /* pause for 200000 microseconds*/

				if (ftdi_read_data(&ctx, rdbuf, sizeof(rdbuf)) < 0) {
					printf("Failed to write data: %s\n", ftdi_get_error_string(&ctx));
					return 1;
				}
				puts("Data read: ");
				for (int i = 0; i < sizeof(rdbuf)/sizeof(*rdbuf); i++) {
					printf(" 0x%02X", rdbuf[i]);
					rdbuf[i] = 0;
				}
				puts("\n");
				usleep(200000); /* pause for 200000 microseconds*/
			}
}
