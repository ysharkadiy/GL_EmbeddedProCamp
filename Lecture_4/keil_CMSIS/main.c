
#include "stm32f3xx.h"                  // Device header
unsigned int i;

void delay()
{
	for(i=0;i<1000000;i++);
}

int main(void)
{
	RCC->AHBENR |= (1<<21);					//Configure PORT E for Clock using RCC
	GPIOE ->MODER |= 0x55550000;		//Configure PORT E pn 8-15 for output
	
	while(1)
	{
		delay();
		GPIOE ->ODR |= 0x0000FF00;		//Pin 8-15 ODR Output Data Register set to 1
		delay();
		GPIOE ->ODR &= ~(0x0000FF00);	//Pin 8-15 ODR Output Data Register set to 0
	}
}