#include <TM4C123GH6PM.h>

#include "../../src/config.h"
#include "../../src/constants.h"

void UART_pins_setup(void);
void UART0_setup(void);

char UART0_read_char(void);

void UART0_write_char(char c);
void UART0_write_string(char * c);



void UART_pins_setup(void) {
	SYSCTL->RCGCGPIO |= GPIO_PORT_A;
  
	while((SYSCTL->PRGPIO & GPIO_PORT_A) == PERIPH_NOT_READY) {}
  
	GPIOA->AFSEL |= PA0 | PA1;
  GPIOA->PCTL = (GPIOA->PCTL & ~(GPIO_PCTL_PA0_M | GPIO_PCTL_PA1_M)) | GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX; // Set UART0 function
  GPIOA->DEN |= PA0 | PA1;
}

void UART0_setup(void) {
	SYSCTL->RCGCUART |= UART_0;
  while((SYSCTL->PRUART & UART_0) == PERIPH_NOT_READY) {}
  
	UART0->CTL = UART_CTL_DISABLE;

  // Baud rate setup for 16 MHz
	UART0->CC = UART_CC_PIOSC;
	UART0->IBRD = UART_IBRD_9600;
  UART0->FBRD = UART_FBRD_9600;
  UART0->LCRH = UART_LCRH_8N1;                       // 8-bit, no parity, 1 stop bit, no FIFO

  UART0->CTL = UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;
		
	for(int i=0; i < 100000; ++i); // delay ~100 ms before first UART write
}

char UART0_read_char(void) {
	while ((UART0->FR & UART_FR_RXFF) != 0); // wait till register is not empty 
	return (char)UART0->DR;
}

void UART0_write_char(char data) {
	while ((UART0->FR & UART_FR_TXFF) != 0); // wait till register is not full
	
	UART0->DR = (uint8_t)data;
}

void UART0_write_string(char* data) {
	for (; *data != '\0'; ++data) { UART0_write_char(*data); }
}
