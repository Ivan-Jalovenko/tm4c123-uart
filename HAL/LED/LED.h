#ifndef LED_H
#define LED_H

#include <stdint.h>

int LED_setup(void);

void LED_on(uint32_t led_mask);
void LED_off(uint32_t led_mask);

#endif // LED_H
