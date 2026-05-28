/*
Realice un programa que haga un toggle del Puerto PC3 cuando un switch conectado
 a INT0 (PD2) vaya a “0”
*/
#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>    
ISR(INT0_vect) {
    PORTC ^= (1<<PC3);
}

int main( ) {
    DDRC |= (1<<PC3);
    GICR |= 0b01000000;
    MCUCR |= 0b00000010;
    sei();
    while(1);
    return 0;
}