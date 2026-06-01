#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_INIT() {
    ADCSRA = 0b10001111;
    ADMUX = 0b110000010; //CHANEL TWO
}
ISR(ADC_vect) {
    PORTB = ADCL;
    PORTD = ADCH;
}
int main() {
    DDRB = 0xFF;
    DDRD = 0xFF;
    ADC_INIT();
    SEI();
    while(1) {
        ADCSRA |= (1 << ADSC);
    }
}
