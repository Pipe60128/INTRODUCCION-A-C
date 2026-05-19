/*
Realice un programa que permita controlar el nivel de agua en un tanque. Se dispone
de un sensor que entrega un “0” cuando se alcanza determinado nivel. El sistema 
debe abrir una válvula de escape de agua y activar una alarma sonora ( buzzer) 1seg
ON y 1 seg OFF. La desactivación de la alarma se hará con un switch ON/OFF
El sensor y el switch se atenderán por interrupciones externas y la alarma por 
Interrupción de timer 

-> gicr = 1100 0000
-> mcucr = 0000 0010
-> timsk = 0000 0010
-> tccr0 = 0000 1101
*/

#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>  
uint8_t cont;

ISR(INT0_vect){
    PORTB |= (1<<PB0) | (1<<PB1);
    OCR0 = 77;
    TCCR0 = 0b00001101;
    cont = 100;
}
ISR(INT1_vect){

}
ISR(TIMER0_COMP_vect){

}

int main() {
    DDRB |= (1<<PB0) | (1<<PB1); 
    GICR |= 0b11000000;
    MCUCR |= 0b00001010;
    TIMSK |= 0b00000010;
    SEI();
    while(1);
}