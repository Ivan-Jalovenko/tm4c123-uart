/*
 * LED.c - Driver for internal & external LEDs 
 * based on configuration for TM4C123GH6PM
 * 
 * This module controls the onboard RGB LED connected to Port B/F based on configuration
 * pins PB2/PF1 (Red), PB3/PF2 (Blue), and PB4/PF3 (Green).
 */

#include <TM4C123GH6PM.h>

#include "LED.h"

#include "../../src/config.h"
#include "../../src/constants.h"

int LED_setup(void) {
  SYSCTL->RCGCGPIO |= LED_GPIO_BASE;
    
	LED_GPIO->DIR |= LED_RED | LED_GREEN | LED_BLUE;
    
	LED_GPIO->DEN |= LED_RED | LED_GREEN | LED_BLUE;
    
	LED_GPIO->DATA &= ~(LED_RED | LED_GREEN | LED_BLUE);
    
	return SUCCESS;
}

void LED_on(uint32_t led_mask) {
	uint32_t safe_mask = led_mask & LED_ALL;
	LED_GPIO->DATA |= safe_mask;
}

void LED_off(uint32_t led_mask) {
	uint32_t safe_mask = led_mask & LED_ALL;
	LED_GPIO->DATA &= ~safe_mask;
}
