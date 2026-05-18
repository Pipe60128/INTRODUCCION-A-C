/*
Usando el T1 en modo CTC generar un DELAY de  1s que permita cambiar el
estado de un led conectado a PC4 cada ese tiempo. Freq=8MHZ
*/

#define __AVR_ATmega16__
#include <avr/io.h> 

void Delay1s(){
    OCR1A = 31249;
    TCCR1A = 0; 
    TCCR1B = 0b00001100;
    while((TIFR & (1 << OCF1A)) == 0);
    TCCR1B = 0; // Detener el temporizador
    TIFR |= (1 << OCF1A); // Limpiar la bandera de desbordamiento
}

int main(void) {
    DDRC |= (1<<PC4); // Configurar PC4 como salida
    while(1) {
        PORTC ^= (1<<PC4); // Cambiar el estado de PC4
        Delay1s();   
    }
    return 0;
}
