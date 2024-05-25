/* *
 * Linker sciprt file for STM32F103C8T6 
 * */

MEMORY
{
	ROM (rx)  : ORIGIN = 0x08000000 , LENGTH = 64K
	RAM (rwx) : ORIGIN = 0x20000000 , LENGTH = 20K
}

ENTRY (Reset_Handler)

SECTIONS
{
	.text :
	{
		*( .vectors )
		*( .text )
		*( .rodata )
		. = ALIGN( 4 );
		_etext = .;

	} >ROM

	.data :
	{
		_sdata = .;
		*( .data )
		. = ALIGN( 4 );
		_edata = .;
	} >RAM AT >ROM

	.bss :
	{
		_sbss = .;
		*( .bss )
		. = ALIGN ( 4 );
		_ebss = .;
	} >RAM
}

PROVIDE(_stack = ORIGIN( RAM ) + LENGTH( RAM ));
