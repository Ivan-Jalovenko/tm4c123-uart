#ifndef UART_H
#define UART_H

void UART_pins_setup(void);
void UART0_setup(void);

char UART0_read_char(void);

void UART0_write_char(char c);
void UART0_write_string(char * c);

#endif // UART_H
