#define __AVR_ATmega16__
#define F_CPU 8000000UL;
#include <avr/io.h>
#include <util/delay.h>

//teclado y valor
int cont_filas;
char codigo_barrido;
int valor_tecla;
int temp;
//display
char RAMP_Display [4] = {0,0,0,0};
int cont_lamp =4;
char codigo_barrido = 0b11101111;
int i = 0;
int tempD;

void INIT_TIMER0(){
    TIMSK = 0b00000010; //tc0 comapre
    OCR0 = 38;
    TCCR0 = 0b00001101; //t0 ctc 1024
    SEI();
}

ISR(TIMER0_COMP_vect){
    tempD= codigo_barrido & 0xF0;
    PORTB = RAMP_Display[i++] + tempD;
    codigo_barrido = codigo_barrido << 1;
    cont_lamp--;
    if(cont_lamp == 0 ){
        cont_lamp = 4;
        codigo_barrido = 0b11101111;
        i = 0;
    } 
}

void teclado(void) {
    cont_filas=4;
    codigo_barrido=0b11111110;
    valor_tecla=03;
    while(cont_filas!=0) {
        PORTC=codigo_barrido;
        temp=PINC & 0xF0;
        if (temp==0xF0) {
            codigo_barrido=(codigo_barrido<<1)|1; 
            valor_tecla=valor_tecla+4;
            cont_filas--;

            if (cont_filas==0) {
                valor_tecla=0xFF;
                break;
            }
        }
        
        else {
            _delay_ms(10); //eliminas el rebote de la tecla
            temp=PINC & 0xF0;
            if (temp==0xF0) {
                valor_tecla=0xFF;
                break;
            }

            else if (temp==0b01110000) valor_tecla=valor_tecla;
            else if (temp==0b10110000) valor_tecla=valor_tecla-1;
            else if (temp==0b11010000) valor_tecla=valor_tecla-2;
            else if (temp==0b11100000) valor_tecla=valor_tecla-3;

            while ((PINC & 0xF0)!=0xF0);
            _delay_ms(10);
            cont_filas=0;
        }
    }
}

void rotar_display(){
    RAMP_Display[0] = RAMP_Display[1];
    RAMP_Display[1] = RAMP_Display[2];
    RAMP_Display[2] = RAMP_Display[3];
    RAMP_Display[3] = valor_tecla;
}
int main(void)
{
    DDRB = 0xFF;
    DDRC = 0x0F; //filas como salida y columnas como entrada
    INIT_TIMER0();
    while(valor_tecla != 10){ //start
        teclado();
    }
    while(valor_tecla != 11 ){ // end by enter
        teclado();
        if (valor_tecla < 10 ){
            rotar_display();
        }
    }
    return 0;
}