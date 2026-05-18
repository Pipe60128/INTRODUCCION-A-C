//Uso de un ciclo for retardo
#define __AVR_ATmega16__
#include <avr/io.h>
#include <util/delay.h>

//delay for 10ms
void delay10ms(void)
{
    unsigned int i;
    for (i = 0 ; i <44450; i++);
    
}

//Uso de funciones predefinidas de C
void delay100_ms(int d) 
    {
        _delay_ms(d);
    }

int main(void)
{
    DDRB=0xFF;
    while (1) {
    PORTB=0xAA;
    delay100ms();
    PORTB=0x55;
    delay100ms();
    }

    
    DDRB=0xFF;
    while (1)
    {
    PORTB=0xAA;
    delay_ms(100);
    PORTB=0x55;
    delay_ms(100);
    }
    return 0;
}
//Uso de timers