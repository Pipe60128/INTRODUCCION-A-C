/*
1) Cuando el sistema esté energizado pero ningún switch esté activo (estado IDLE o reposo), 
los 3 LEDs del sistema deberán estar parpadeando de la siguiente manera: 30ms 
encendidos, y 30ms apagados, y así infiniramente hasta que haya un cambio en algún 
switch (Este es el modo de espera). 
*/
#include "functions.h"  
int main() {
    DDRD |= 0b11111111;
    while (1) {
        PORTD &= ~(1<<PD0) & ~(1<<PD1) & ~(1<<PD5) & ~(1<<PD7);
        DelayDynamicms(233);
        PORTD |= (1<<PD0) | (1<<PD1) | (1<<PD5) | (1<<PD7);
        DelayDynamicms(233); 
        while (!(PINB & (1<< PB0)))  {
            PWM_ININT_SWITCH1();
        }
         while (!(PINB & (1<< PB2)))  {
            SWITCH3();
        }
    }
}