#include "functions.h"

uint8_t dutycycle = 50;
void DelayDynamicms(uint8_t ms){
    OCR2 = ms;
	TCCR2 = 0b00001111;
	while ((TIFR & (1 << OCF2))== 0);
	TCCR2 = 0;
	TIFR = (1 << OCF2);
}

uint8_t debounce( uint8_t port, uint8_t pin) {
    if (!(port & (1 << pin))) {  
        DelayDynamicms(77);      
        if (!(port & (1 << pin))) {  
            return 1;            
        }
    } 
    return 0;          
}

void PWM_ININT_SWITCH1() {
        OCR2 = ((uint16_t)dutycycle * 255) / 100;
        TCCR2 = 0b01101111;

            if (debounce(PINB, PB6)) {  
                if (dutycycle <= 90) {
                    dutycycle += 10;
                }
                OCR2 = ((uint16_t)dutycycle * 255) / 100;
                while (!(PINB & (1 << PB6))); // espera a soltar el botón

            } else if (debounce(PINB, PB7)) {  // Botón bajar
                if (dutycycle >= 20) {       // >= 20 para que no baje de 10
                    dutycycle -= 10;
                }
                OCR2 = ((uint16_t)dutycycle * 255) / 100;
                while (!(PINB & (1 << PB7))); // espera a soltar el botón
            }
}