//Generar usando el Timer “0” del ATMEGA 16 un retardo de 10μs

#define __AVR_ATmega16__
#include <avr/io.h> 


void Delay10micros(){
    TCNT0 = 176;
    TCCR0 = 0b00000001; // Configurar el temporizador con un prescaler de 1
    while((TIFR & (1 << TOV0)) == 0);
    TCCR0 = 0b00000000; // Detener el temporizador
    TIFR |= (1 << TOV0); // Limpiar la bandera de desbordamiento
}



int main(void) {
    while(1) {
        Delay10micros();    
    }
    return 0;
}