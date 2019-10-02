#include "clock.h"

extern Clock_struct clock_data;

void CLOCK_INITIALIZATION(void){
	unsigned char SYSDIV = (400/clock_data.required_freq)-1;
	//use RCC2
	RCC2_CLOCK_REG|=(1<<31);  //USEERCC2 31
	//bypass PLL   (bybass bit 11 in RCC2)
	RCC2_CLOCK_REG|=(1<<11);
	RCC_CLOCK_REG = (RCC_CLOCK_REG&(0xFFFFF83F))|((clock_data.crystal<<6));
	RCC2_CLOCK_REG = (RCC2_CLOCK_REG&~((1<<4)|(1<<5)))|(clock_data.source_clock<<4);
	//enable PLL by clear bit 13 PWRDN2 in RCC2
	RCC2_CLOCK_REG&=~(1<<13);
	//to use 400MHZ PLL set DIV400 bit 30 in RCC2
	RCC2_CLOCK_REG |= (1<<30);
	//put the required sysdiv bit 23 to 28 in RCC2
	RCC2_CLOCK_REG = (RCC2_CLOCK_REG&0xE07FFFFF)|(SYSDIV<<23);
	// wait untill PLL is lock by waiting untill(PLLRIS bit 6 in RIS) will be high 
	while((RIS_CLOCK_REG&(1<<6)) == 0);
	//enable the PLL
	RCC2_CLOCK_REG&=~(1<<11);
}

