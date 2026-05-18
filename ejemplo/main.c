#include <avr/io.h>

int main(void)
{
    // PB0 como entrada
    DDRB &= ~(1 << PB0);

    // PA0 como salida
    DDRA |= (1 << PA0);

    while (1)
    {
        if (PINB & (1 << PB0)) {
            // Si PB0 = 1 → PA0 = 1
            PORTA |= (1 << PA0);
        } else {
            // Si PB0 = 0 → PA0 = 0
            PORTA &= ~(1 << PA0);
        }
    }
}
