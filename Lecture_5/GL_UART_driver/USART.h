#include "stm32f3xx.h"                  // Device header
#include <string.h>
#include <stdint.h>

/* USART1 init function ---------------------------------------------*/
void UART1_init(void);

/* USART1 open function ---------------------------------------------*/
void UART1_open(void);

/* USART1 send symbol function --------------------------------------*/
void USART1_send_symb( char symbol);

/* USART1 send string function ------------------------------------*/
void UART1_write(char *, size_t);

/* USART1 read string function ------------------------------------*/
void UART1_read(char *, size_t);

/* USART1 close function --------------------------------------------*/
void UART1_close(void);

/* USART1 deinit function -------------------------------------------*/
void USART1_DeInit (void);

