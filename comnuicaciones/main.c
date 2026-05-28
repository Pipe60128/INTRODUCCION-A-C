#define __AVR_ATmega16__
#include <avr/io.h>
char datos[]= {'A','E','I','O','U'};
int i;
void usart_init(void) //INICIALIZAR USART
{
    UCSRC=0b10000110;
    UCSRB=0b00001000;
    UBRRL=51; //9600 BAUDIOS
    UBRRH=0;
}
void usart_send(char datos) //escribirle al UDR el dato a transmitir
{
    while((UCSRA & (1<<UDRE))==0); //ESPERAR HASTA QUE EL BUFFER ESTE VACIO POLL a la bandera
    UDR=datos; //ENVIAR EL DATO
}
int main(void){
    DDRD |= (1<<PD1); //TX
    while (1){
        usart_init();
        for(i=0;i<5;i++) //TRANSMITIR LOS DATOS
        {
        usart_send(datos[i]);
        }
    }
    return 0;
}