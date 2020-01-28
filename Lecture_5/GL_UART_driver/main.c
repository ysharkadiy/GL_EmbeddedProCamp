#include "stm32f3xx.h"                  // Device header
#include <string.h>
#include "USART.h"

/* Private function prototypes -----------------------------------------------*/

/* Test delay function --------------------------------------------*/
void delay(int test_delay)
{
	int i = test_delay * 100000;
	while(i--);
}


int main(void)
{
	//string for debug
	static char UART_rxdata[10] = {};
	static char UART_outdata[] = {"\nWas read:"};
	static char UART_closestr[] = {"\nEnter 111 to close UART communication:"};
	 
	UART1_init();
	UART1_open();
	 
	RCC->AHBENR |= (1<<21);					//Configure PORT E for Clock using RCC
	GPIOE ->MODER |= 0x55550000;		//Configure PORT E pn 8-15 for output
	UART1_write(UART_closestr, strlen(UART_closestr));
	
	while(1)
	{
		delay(10);
		GPIOE ->ODR |= 0x0000FF00;		//Pin 8-15 ODR Output Data Register set to 1
			
		UART1_read(UART_rxdata, 3);
		
		UART1_write(UART_outdata, strlen(UART_outdata));
		UART1_write(UART_rxdata, 3);
		
		delay(10);
		GPIOE ->ODR &= ~(0x0000FF00);	//Pin 8-15 ODR Output Data Register set to 0
		if (strcmp(UART_rxdata, "111")==0)
		{
			/* USART Disable */
			UART1_close();
			USART1_DeInit();
			break;
		}
	}
}

	
