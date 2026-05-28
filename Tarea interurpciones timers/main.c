/*
Diseñar usando un ATMEGA16 un sistema que permita monitorear el flujo de agua en una turbina y en base al mismo controlar la apertura de una válvula proporcional
La medición de flujo se realizará a través de un dispositivo que entrega un valor de 8 bits entre 0 y 180 litros/seg. 
La medición comenzará con un interruptor ON/OFF. El sistema debe realizar mediciones de flujo cada 200ms.
El sistema realizará el control de una válvula proporcional utilizando PWM. Cada vez que se obtenga una medición 
se debe generar un pulso de periodo igual a 60ms cuyo ciclo útil permitirá la apertura de la válvula de la siguiente forma:
        • Cuando el flujo medido esté entre 0 y 40 litros/seg el ciclo útil será del 25%.
        • Cuando el flujo medido esté entre 41 y 80 litros/seg el ciclo útil será del 50%.
        • Cuando el flujo medido esté entre 81 y 130 litros/seg el ciclo útil será del 75%.
        • Cuando el flujo medido esté entre 131 y 180 litros/seg el ciclo útil será del 90%.
El sistema debe generar los pulsos con el ciclo útil adecuado hasta que se reciba una nueva medición.
El sistema permanecerá midiendo flujo y controlando la válvula (generando los pulsos PWM) hasta que se reciba una señal de STOP activa en “0” que debe detener la medición de flujo 
y la generación de PWM (frec- cristal =8 Mhz).
1-Realice el diseño completo del Hardware y software del sistema. Realice la atención al interruptor ON/OFF
y a la señal de STOP por interrupción externa y las mediciones de tiempo por interrupción de Timer. Utilice los Timers para todos los requerimientos de tiempo del sistema.

PTOA = sensor
PTOD2 = ON/OFF
PTOD3 = STOP
PTOD4 = Salida PWM
*/
 

#define __AVR_ATmega16__
#include <avr/io.h>
#include <avr/interrupt.h>  

volatile uint8_t sensor = 0;
volatile uint8_t cont;
volatile uint8_t flag_ONOFF = 0;
volatile uint8_t flag_STOP = 0;

ISR(INT0_vect){
    //ON
    flag_ONOFF = 1;
    flag_STOP = 0;
    OCR0 = 77;
    TCCR0 = 0b00001101;

    OCR1A = 468; 
    TCCR1A = 0b00100011;
    cont = 20;
}
ISR(INT1_vect){ 
    //STOP 
    flag_STOP = 1;
    flag_ONOFF = 0;
    TCCR0 = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    PORTD &= ~(1<<PD4);
}

ISR(TIMER0_COMP_vect){
    cont--;
    if(cont == 0){
        sensor = PINA;
        cont = 20;
    }
}

int main() {
    DDRD |= (1<<PD4); // OUT PWM
    DDRA = 0x00;
    DDRD &= ~((1<<PD2) | (1<<PD3));
    PORTD |= (1<<PD2) | (1<<PD3); // Pull-up en los botones
    GICR |= 0b11000000;
    MCUCR |= 0b00001010;
    TIMSK |= 0b00000010;
    SEI();
    while(1) {
        if ( (flag_ONOFF == 1) && (flag_STOP == 0)){
            if (sensor <= 40) {
                // 25% duty cycle
                OCR1B = 116;    
                TCCR1B = 0b00011101;

            } else if ((sensor >= 41) && (sensor <= 80)) {
                // 50% duty cycle
                OCR1B = 234;
                TCCR1B = 0b00011101;
            } else if ((sensor >= 81) && (sensor <= 130)) {
                // 75% duty cycle
                OCR1B = 351;
                TCCR1B = 0b00011101;
            } else if ((sensor >= 131) && (sensor <= 180)){
                // 90% duty cycle
                OCR1B = 421;
                TCCR1B = 0b00011101;
            } else {
                OCR1B = 0;
            }
        }
    }
    return 0;
}   