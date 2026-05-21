/*
realice el segmeto de main que lea el ptoA un valor entre 0 y 9 y lo visualice ne la lamp de extrema derecha lamp 4;
dispone de nua tabla en flash que se llama digitos 
*/

/*
realice el segmeto del main que visualice en el display 7 segmentos con el cartel hola
*/

#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

//Constantes
char RAMP_Display [4] = {0b01000000,0b01000000,0b01000000,0b01000000};
int cont_lamp =4;
char codigo_barrido = 0b11111110;
int i =0;

//FUNCIONES

//INTERRUPCIONES
ISR(TIMER0_COMP_vect){
    PORTC = (PORTC | 0b00001111) & codigo_barrido;
    PORTB = RAMP_Display[i++];
    codigo_barrido = (codigo_barrido << 1) | 1;
    cont_lamp--;
    if(cont_lamp == 0 ){
        cont_lamp = 4;
        codigo_barrido = 0b11111110;
        i = 0;
    } 
}



//CREAR TABLA EN FLASH
const char digitos[] PROGMEM = {0,1,2,3,4,5,6,7,8,9};
//MAIN
int main() {
    DDRB |= 0xFF;
    DDRC |= 0xFF;
    TIMSK = 0b00000010; //tc0 comapre
    SEI();
    OCR0 = 38;
    TCCR0 = 0b00001101; //t0 ctc 1024
    int num = PINA;
    RAMP_Display[3] = pgm_read_byte(&digitos[num]);
}