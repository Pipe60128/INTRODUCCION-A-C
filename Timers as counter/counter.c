/*
Realice un programa que cuente la cantidad de personas que entran a una sala de
Espectáculos. Se dispone de un sensor que entrega un pulso por cada persona que 
entre. Cuando hayan entrado 100 personas activar un buzzer conectado a PC4
( 1seg ON y 1seg OFF)
*/
#define __AVR_ATmega16__
#include <avr/io.h> 

void conteo(){
    OCR0 = 99;
    TCCR0 = 0b00001110; // congigurar modo contador falling edge
    while((TIFR & (1 << OCF0)) == 0);
    TCCR0 = 0; // Detener el contador
    TIFR |= (1 << OCF0); // Limpiar la bandera de desbordamiento
}

void Delay1s(){
    OCR1A = 31249;
    TCCR1A = 0; 
    TCCR1B = 0b00001100;
    while((TIFR & (1 << OCF1A)) == 0);
    TCCR1B = 0; // Detener el temporizador
    TIFR |= (1 << OCF1A); // Limpiar la bandera de desbordamiento
}

int main(){
    DDRC |= (1<<PC4);
    conteo();
    while(1) {
        PORTC ^= (1<<PC4); // Cambiar el estado de PC4
        Delay1s();
    }
    return 0;
}