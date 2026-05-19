#ifndef functions_h
#define functions_h
#define __AVR_ATmega16__
#include <avr/io.h>

void DelayDynamicms(uint8_t ms);
uint8_t debounce(uint8_t port, uint8_t pin);
void PWM_ININT_SWITCH1();

#endif