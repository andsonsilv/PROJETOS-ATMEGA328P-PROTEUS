/*
 * 03. BLK-BUTTON-INTERRUPTION.c
 *
 * Created: 06/04/2018 01:15:10
 * Author : Antonio
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

/* Replace with your application code */

#define LED_ON		PORTB |= (1<<PORTB5)
#define LED_OFF		PORTB &= ~(1<<PORTB5)
#define LED_TOGGLE	PINB |= (1<<PINB5)
#define  SWITCH_PRESSED !(PINB & (1<<PINB7))

ISR(PCINT0_vect){
	if(SWITCH_PRESSED)
		LED_ON;
	else
		LED_OFF;
}

int main(void){
	
	DDRB |= (1<<DDB5);
	DDRB &= ~(1<<DDB7);
	
	
	PCMSK0 |= (1<<PCINT7);
	PCICR |= (1<<PCIE0);
	
	sei();
	
	while(1){
		
	}
	
}


