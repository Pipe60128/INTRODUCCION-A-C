/*
Realice un programa que atienda un sensor conectado al bit 5 del puerto B y un
led conectado al bit 7 del puerto C. Cuando el sensor se active en “1” se debe
encender el LED.

ENTRDAS:    SALIDAS:
-PB5        -PC7
*/

#define __AVR_ATmega16__
#include <avr/io.h>
int main(void)
{
    DDRB &= 0b11011111; //PB5 COMO ENTRADA
    DDRC |= 0b10000000; //PC7 COMO SALIDA
    while(1) 
    {
        if (PINC & 0b00100000)
            PORTC |= 0b10000000; //PRENDER LE LED
        else
            PORTC &= 0b01111111; //APGAR EL LED
    }
    return 0;
}