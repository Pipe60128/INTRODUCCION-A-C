/*
Ejercicio 5 Generar usando el Timer 0 una señal PWM de 31250HZ  con 75% de ciclo útil. Utilice
FAST PWM y modo no invertido.
*/

#define __AVR_ATmega16__
#include <avr/io.h> 

int main(void) {
    DDRB |= (1<<PB3); 
    OCR0 = 191;
    TCCR0 = 0b01101001;
    while(1);
    return 0;
}