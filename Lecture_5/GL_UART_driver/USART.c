#include "stm32f3xx.h"                  // Device header
#include <string.h>
#include "USART.h"

/* USART1 init function ---------------------------------------------*/
void UART1_init(void)
{
	RCC->AHBENR|=RCC_AHBENR_GPIOCEN;// I/O port C clock enable - 72 MHz
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1 clock enable

	//  Configure PC4 Tx Port and PC5 Rx Port
	GPIOC->MODER |= GPIO_MODER_MODER4_1;//pin4 in Alternate function mode (set -> 10)
	GPIOC->MODER |= GPIO_MODER_MODER5_1;//pin5 in Alternate function mode (set -> 10)

	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_4;//0 - 0: push-pull output or push-pull reduced PP (after reset)
	//GPIOA->OTYPER |= GPIO_OTYPER_OT_9;    // pin9 Output open-drain
	//GPIOA->OTYPER |= GPIO_OTYPER_OT_10;   // pin10 Output open-drain
	
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR4; //reset
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR4_0;//01 - pull to power plus or pull-up is abbreviated PU
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR5;//00 - state after reset, no pull up, pull down
	//GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0;  // pin9 Pull-up
	//GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0; // pin10 Pull-up
	
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;// 11 - 50 MHz, high-frequency output
	
	GPIOC->AFR[0] = 0X00770000;						//pin4 and pin5 AF7 for USART1

	//RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1 clock enable
	
	USART1->BRR = 0x341; // USART Baud rate register = 8MHz/9600(b/s)
	USART1->CR1 |= USART_CR1_TE; //  Transmitter enable
	USART1->CR1 |= USART_CR1_RE; //  Receiver enable 
	
	// ENABLE INTERRUPTS				+
	USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Interrupt Enable
}

/* USART1 open function ---------------------------------------------*/
void UART1_open(void)
{	
	USART1->CR1 |= USART_CR1_UE; //  USART enable
}

/* USART1 send symbol function --------------------------------------*/
void USART1_send_symb(char symbol)
{
	while (!(USART1->ISR & USART_ISR_TC)); // waiting while Transmission of the last symbol is complete
	
	USART1->TDR = symbol;
}
/* USART1 send string function ------------------------------------*/
void UART1_write(char *string, size_t len)
{
	
	uint8_t string_point = 0;
	
	while (string_point < len)
	{
		USART1_send_symb( string[string_point++] );
	}
}
/* USART1 read string function ------------------------------------*/
void UART1_read(char *string, size_t len)
{
	uint8_t string_point = 0;
	while (string_point < len)
	{
		while ((USART1->ISR & USART_ISR_RXNE) == 0)
		{
		}
		string[string_point++] = USART1->RDR; 	// read data from RDR
	}
}
/* USART1 close function --------------------------------------------*/
void UART1_close(void)
{		
	USART1->CR1 &= ~USART_CR1_UE; //  USART disable
}
/* USART1 deinit function -------------------------------------------*/
void USART1_DeInit (void)
{
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; //USART1 reset
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
}
