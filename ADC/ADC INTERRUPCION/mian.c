#define __AVR_ATmega16__
#include <avr/io.h>
void ADC_INIT(){
    ADCSRA = 0b10000111;
    ADMUX = 0b110000010; //CHANEL TWO
}

int main(){
    DDRB = 0xFF;
    DDRD = 0xFF;
    ADC_INIT();
    while(1){
        ADCSRA |= (1<<ADSC); // START CONVERSOIN
        while((ADCSRA & (1<<ADIF) == 0)); //awit to finish converison
        ADCSRA |= (1<<ADIF); // START CONVERSOIN
        PORTB = ADCL;
        PORTD = ADCH;
    }
    return 0;
}