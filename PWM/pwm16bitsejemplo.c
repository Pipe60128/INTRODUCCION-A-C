/*
Ejercicio 6 Generar usando el Timer 1 una señal PWM de 50ms  con 70% de ciclo útil. Utilice
FAST PWM y modo no invertido.
*/

#define __AVR_ATmega16__
#include <avr/io.h> 

int main(void){
    DDRD |= (1<<PD4);
    OCR1A = 389;
    OCR1B = 272;
    TCCR1A = 0b00100011;
    TCCR1B = 0b00011101; // 1024 prescaler
    PORTD |= (1<<PD4);
    while(1);
    return 0; 
}