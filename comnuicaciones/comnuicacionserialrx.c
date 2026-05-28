#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>

void usart_init(void) //INICIALIZAR USART
{
    UCSRC=0b10000110;
    UCSRB=0b00001000;
    UBRRL=51; //9600 BAUDIOS
    UBRRH=0;
}

ISR(USART_RXC_vect) //INTERRUPCION DE RECEPCION COMPLETA
{
    int valor = UDR; //LEER EL DATO RECIBIDO
    PORTD = valor; 
}
int main(void){
    DDRD |= 0xFF; //TX
    sei();
    usart_init();
    while (1);
    return 0;
}