/*
===========================
CON CORRIMINIENTOS DE BITS
===========================
Realice un programa que atienda un sensor conectado al bit 5 del puerto B y un
led conectado al bit 7 del puerto C. Cuando el sensor se active en “1” se debe
encender el LED.

ENTRDAS:   
-SENSOR     
-PB5        

SALIDAS:
-LED    
-PC7
*/

#define __AVR_ATmega16__
#include <avr/io.h>
int main(void)
{
    DDRB &= 0b11011111;
    DDRC |= 0b10000000;
    while(1) 
    {
        if (PINC & (1<<5))
            PORTC |= (1<<7); //PRENDER LE LED
        else
            PORTC &= ~(1<<7); //APGAR EL LED
    }
    return 0;
}

/*

============================================================================================
SE MANDA UN 0 A PTO 
~(1<<7) = 0b01111111 PORQUE ENTRAN UNOS Y LEUGO SE USA UN INVERSOR PARA HACER EL SEPTIMO 0
ENTRAN = 10000000
SALEN = 01111111
============================================================================================
*/