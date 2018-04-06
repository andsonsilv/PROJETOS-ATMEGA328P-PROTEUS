/*
 * 04. BLKS-RANDOMS.c
 *
 * Created: 06/04/2018 09:33:10
 * Author : Antonio
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>


#define  SWITCH_PRESSED !(PINC & (1<<PINC0))

unsigned int aux = 0;

void randomico(unsigned int numero){
	switch(numero){
		
		case 0:
		PORTB = 0b00000010;
		break;
		case 1:
		PORTB = 0b00000110;
		break;
		case 2:
		PORTB = 0b00001110;
		break;
		case 3:
		PORTB = 0b00011110;
		break;
		case 4:
		PORTB = 0b00111110;
		break;
		case 5:
		PORTB = 0b01111110;
		break;
		case 6:
		PORTB = 0b11111110;
		break;
		default:
		break;
		
	}
}

ISR(PCINT1_vect){
	
	if(SWITCH_PRESSED) randomico(aux);
	
}

int main(void){
	
	/* Replace with your application code */
	
	DDRB = 0b11111111;
	DDRC &= ~(1<<PORTC0);
	
	PCMSK1 |= (1<<PCINT8);
	PCICR |= (1<<PCIE1);
	
	sei();
	
	while(1){
		
		PORTC |= (1<<PORTC0);
		
		aux++;
		if(aux == 6) aux = 0;
		
	}
	
	return 0;
	
}
