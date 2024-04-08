//*****************************************************************************
//Universidad del Valle de Guatemala
//IE2023 Programacionde Microcontroladores
//Author : Nicole Navas
//Proyecto: laboratorio 4: Programacion en C 
//IDescripcion: Codigo de contador de 8 bits y manejo de display con 
//				potenciometro
//Hardware: ATMega328P
//Created: 4/9/2024 10:08:47 PM
// Actualizado: 2/5/2024
//*****************************************************************************
// Encabezado
//*****************************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t contador = 0; //iniciar el contador en 0



void setup() {
	
	DDRC &= ~((1 << PC4) | (1 << PC5)); // Configurar PC4 y PC5 como entradas

	PORTC |= (1 << PC4) | (1 << PC5); // Habilitar resistencias pull-up en PC4 y PC5

	PCICR |= (1 << PCIE1); // Habilitar interrupciones por cambio de estado en PC4 y PC5
	PCMSK1 |= (1 << PCINT12) | (1 << PCINT13);

	sei(); // Habilitar interrupciones globales
}


ISR(PCINT1_vect) { //Interrupcion de botones
	
	_delay_ms(20);
	
	if (!(PINC & (1 << PC4))) { // comprobar si boton de incremento esta presionado
		contador++;
	}
	
	
	if (!(PINC & (1 << PC5))) { // comprobar si boton de decremento esta presionado
		contador--;
	}

}

int main() {
	setup();

	while (1) {
		
		//actualizacion de LEDS
		PORTC = (PORTC & 0xF0) | (contador & 0x0F); // poner los primeros 4 bits en el PORTC
		PORTB = (PORTB & 0xF0) | ((contador & 0xF0) >> 4); // poner los ultimos leds en el PORTB
	}

	return 0; //retorno 
}