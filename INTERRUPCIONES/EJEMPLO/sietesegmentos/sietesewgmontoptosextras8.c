#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>

char RAMP_Display [8] = {0,0,0,0,0,0,0,0};
int cont_lamp =8;
int i =0;
int temp;

ISR(TIMER0_COMP_vect){
    temp = (i<<4) & 0b11110000;
    PORTB = RAMP_Display[i++] + temp;
    cont_lamp--;
    if(cont_lamp == 0 ){
        cont_lamp = 8;
        i = 0;
    } 
}

int main() {
    DDRB = 0xFF;
    TIMSK = 0b00000010; //tc0 comapre
    SEI();
    OCR0 = 38;
    TCCR0 = 0b00001101; //t0 ctc 1024
}