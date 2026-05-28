#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>
char datos[]= {'A','E','I','O','U'};
int i;
void usart_init(void) //INICIALIZAR USART
{
    UCSRC=0b10000110;
    UCSRB=0b00001000;
    UBRRL=51; //9600 BAUDIOS
    UBRRH=0;
}

ISR(USART_TXC_vect) //INTERRUPCION DE TRANSMISION COMPLETA
{
    UDR = datos[i++];
    if (i == 5){
        i = 0;
        UCSRB = 0b00001000;
    }
}
int main(void){
    DDRD |= (1<<PD1); //TX
    sei();
    usart_init();
    while (1);
    return 0;
}