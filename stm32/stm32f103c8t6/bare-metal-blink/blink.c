/* Bare minimum program to test the arm-none-eabi-gcc compiler toolchain
 * */

#include <stdint.h>

/* ------ PORT-C CLOCK SETTING definitions ---------------- */
#define RCC_BASE		0x40021000

/* Enable clock on GPIO-C */
#define RCC_IOPCEN      (1 << 4)
/* ------------------------------------------- */

/* ------------- PORT-C DIRECTION and DATA REG definitions -------------- */
#define GPIOC_BASE      0x40011000

/* Port configuration register: GPIOx_CRH
   CNF13[1:0],MODE13[1:0],.......,CNF0[1:0],MODE0[1:0]
    23,22    ,    21,20  ,.......,   3,2   ,   1,0  <-- bit# 
 */
#define GPIOC_CRH_CNF13_SEL     (3UL << 22)	// CNF13 selector
#define GPIOC_CRH_MODE13_SEL    (3UL << 20) // MODE13 selector
#define GPIOC_CRH_MODE13_SET(m) ((uint32_t)m << 20)  // MODE13 setter

/* Define for selecting GPIO-C #13 (PC13) 
   or setting it HIGH */
#define GPIOC_ODR13_SET (1UL << 13)
/* --------------------------------------------------------------------- */

/* ---------- Pointer definitions to the respecitve registers ---------- */
//#define RCC_APB2ENR		*(volatile uint32_t*)(RCC_BASE + 0x18)
//#define GPIOC_CRH       *(volatile uint32_t*)(GPIOC_BASE + 0x04)
//#define GPIOC_ODR       *(volatile uint32_t*)(GPIOC_BASE + 0x0C)
/* -------------------------------------------------------------------- */

uint32_t volatile *const pRccApb2Enr = (uint32_t*)(RCC_BASE + 0x18);
uint32_t volatile *const pGpioC_Crh  = (uint32_t*)(GPIOC_BASE + 0x04);
uint32_t volatile *const pGpioC_Odr  = (uint32_t*)(GPIOC_BASE + 0x0C);
uint16_t dummyCntr;


int main ( void ) {

	*pRccApb2Enr |= RCC_IOPCEN;			// GPIOC clock enabled
	//RCC_APB2ENR |= RCC_IOPCEN;			// GPIOC Clock enabled
	*pGpioC_Crh   &= ~(GPIOC_CRH_CNF13_SEL | GPIOC_CRH_MODE13_SEL);  // GPIO#13 - Reset CNF & MODE bits (AND set as Push-Pull OUTPUT)
	//GPIOC_CRH   &= ~(GPIOC_CRH_CNF13_SEL | GPIOC_CRH_MODE13_SEL);  // GPIO#13 - Reset CNF & MODE bits (AND set as Push-Pull OUTPUT)
	*pGpioC_Crh   |= GPIOC_CRH_MODE13_SET(2);	// GPIOC #13 set MODE to max operation freq 2 MHz
	//GPIOC_CRH   |= GPIOC_CRH_MODE13_SET(2);	// GPIOC #13 set MODE to max operation freq 2 MHz
	
	while (1) {

		//GPIOC_ODR |= GPIOC_ODR13_SET;		   // GPIOC #13 - SET (HIGH): -----> LED OFF
		*pGpioC_Odr |= GPIOC_ODR13_SET;		   // GPIOC #13 - SET (HIGH): -----> LED OFF
		for (int cnt = 500000+dummyCntr; cnt > 0; cnt--) // delay
			__asm__("nop");

		//GPIOC_ODR &= ~(GPIOC_ODR13_SET);	   // GPIOC #13 - RESET (LOW): ----> LED ON
		*pGpioC_Odr &= ~(GPIOC_ODR13_SET);	   // GPIOC #13 - RESET (LOW): ----> LED ON
		for (int cnt = 500000+dummyCntr; cnt > 0; cnt--) // delay
			__asm__("nop");

		dummyCntr++;
		if (dummyCntr > 1023)
			dummyCntr = 0;
	}

	return 0;
}