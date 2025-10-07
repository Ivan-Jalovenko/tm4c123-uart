#include "UI.h"

#include "../UART/UART.h"


char UI_prompt(void) {
	UART0_write_string("Enter 'r', 'g', 'b', 'f' or 'h' for help: ");
	char input = UART0_read_char();
	
	UART0_write_char('\n');
	return input;
}

void UI_help(void) {
	UART0_write_string("For turning red LED use     'r'\n");
	UART0_write_string("For turning green LED use   'g'\n");
	UART0_write_string("For turning blue LED use    'b'\n");
	UART0_write_string("For turn LEDs off use       'f'\n");
}

void UI_invalid(void) {
	UART0_write_string("\nPlease enter valid command!\n\n");
}
