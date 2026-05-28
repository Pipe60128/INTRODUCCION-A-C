#ifndef functions_h
#define functions_h
#define __AVR_ATmega16__
#include <avr/io.h>
#include <util/delay.h>

void DelayDynamicms(uint8_t ms);
uint8_t debounce(uint8_t port, uint8_t pin);
void PWM_ININT_SWITCH1();
void contartimer1();
void delaydinamics();
void SWITCH3();
void activateT0PWM(uint8_t ocr0);
void deactivateT0PWM();
void activateT1PWM();
void deactivateT1PWM();


#endif