#include <TM4C123GH6PM.h>

#include "config.h"
#include "constants.h"

#include "../HAL/LED/LED.h"
#include "../HAL/UART/UART.h"
#include "../HAL/UI/UI.h"

int main(void) {
	LED_setup();
	
	UART_pins_setup();
	UART0_setup();

	for(;;) {
		char input = UI_prompt();
		
		switch (input) {
			case CMD_LED_RED:
				LED_on(LED_RED);
				break;
			
			case CMD_LED_GREEN:
				LED_on(LED_GREEN);
				break;
			
			case CMD_LED_BLUE:
				LED_on(LED_BLUE);
				break;
			
			case CMD_LED_OFF:
				LED_off(LED_RED | LED_GREEN | LED_BLUE);
				break;
			
			case CMD_HELP:
				UI_help();
				break;
			
			default:
				UI_invalid();
				break;
		}
	}
	
	return SUCCESS;
}
