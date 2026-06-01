#define __AVR_ATmega16__
#define F_CPU 8000000UL;
#include <avr/io.h>
#include <util/delay.h>

int cont_filas;// Variable para contar cuántas filas faltan por revisar
char codigo_barrido;// Variable que contiene el patrón de barrido para activar una fila a la vez
int valor_tecla;// Variable donde se almacenará el número de la tecla presionada
int temp;// Variable temporal para guardar la lectura de las columnas

void teclado(void) // Función encargada de detectar qué tecla fue presionada
{
    cont_filas=4; // Se tienen 4 filas por revisar
    codigo_barrido=0b11111110; // Se activa inicialmente la primera fila (PC0 en 0)
    valor_tecla=03; // Valor inicial correspondiente a la primera tecla posible
    while(cont_filas!=0) // Repite el proceso mientras aún existan filas por revisar
    {
        PORTC=codigo_barrido; // Envía el patrón de barrido al puerto C
        temp=PINC & 0xF0;  // Lee únicamente las columnas (bits altos PC4-PC7)
        if (temp==0xF0) // Si todas las columnas están en 1, no se detectó ninguna tecla
        {
        codigo_barrido=(codigo_barrido<<1)|1; // Activa la siguiente fila desplazando el cero hacia la izquierda
        valor_tecla=valor_tecla+4; // Ajusta el valor base para la siguiente fila
        cont_filas--;// Disminuye el contador de filas restantes

        if (cont_filas==0)  // Si ya se revisaron todas las filas
        {
            valor_tecla=0xFF; // Indica que no se encontró ninguna tecla
            break;
        }
        }

        // Si alguna columna cambió de estado, existe una tecla presionada
        else
        {
        _delay_ms(10); //eliminas el rebote de la tecla
        temp=PINC & 0xF0;  // Vuelve a leer las columnas para confirmar la pulsación
        if (temp==0xF0) // Si la tecla ya no está presionada después del rebote
        {
            valor_tecla=0xFF; // Se considera una lectura inválida
            break;
        }
// Dependiendo de la columna detectada,
// se calcula el número de tecla correspondiente
        //columna1
        else if (temp==0b01110000) valor_tecla=valor_tecla;
        //columna2
        else if (temp==0b10110000) valor_tecla=valor_tecla-1;
        //columna3
        else if (temp==0b11010000) valor_tecla=valor_tecla-2;
        //columna4
        else if (temp==0b11100000) valor_tecla=valor_tecla-3;

        while ((PINC & 0xF0)!=0xF0); // Espera hasta que la tecla sea liberada
        _delay_ms(10);
        cont_filas=0; // Fuerza la salida del ciclo porque ya se encontró una tecla
        }
    }
}

int main(void)
{
    DDRC=0x0F; //filas como salida y columnas como entrada
    teclado();
    //acción a realizar con la tecla oprimida
    return 0;
}