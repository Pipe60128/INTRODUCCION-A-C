//Usando el T0 en modo CTC generar un DELAY de 1ms que permita cambiar el
//estado del pin PB5 cada ese tiempo. Freq=8MHZ

#define __AVR_ATmega16__
#include <avr/io.h> 

void Delay1ms(){
    OCR0 = 124;
    TCCR0 = 0b00001011; // Configurar el temporizador en modo CTC con un prescaler de 64
    while((TIFR & (1 << OCF0)) == 0);
    TCCR0 = 0b00000000; // Detener el temporizador
    TIFR |= (1 << OCF0); // Limpiar la bandera de desbordamiento
}

int main(void) {
    DDRB |= (1<<PB5); // Configurar PB5 como salida
    while(1) {
        Delay1ms();   
        PORTB ^= (1<<PB5); // Cambiar el estado de PB5
    }
    return 0;
}