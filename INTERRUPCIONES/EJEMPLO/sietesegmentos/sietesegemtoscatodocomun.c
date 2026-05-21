#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>

char RAMP_Display [4] = {0,0,0,0};
int cont_lamp =4;
char codigo_barrido = 0b00010000;
int i =0;
int temp;

ISR(TIMER0_COMP_vect){
    temp = codigo_barrido & 0b11110000;
    PORTB = RAMP_Display[i++] + temp;
    codigo_barrido = codigo_barrido << 1;
    cont_lamp--;
    if(cont_lamp == 0 ){
        cont_lamp = 4;
        codigo_barrido = 0b00010000;
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