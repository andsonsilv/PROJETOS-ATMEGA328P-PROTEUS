/*
 * 02. BLK-BUTTON.c
 *
 * Created: 06/04/2018 01:00:46
 * Author : Antonio
 *
 */ 

#include <avr/io.h>
#include <util/delay.h>
   
#define LED_ON PORTB |= (1<<PORTB5)
#define LED_OFF PORTB &= ~(1<<PORTB5)
#define  LED_TOGGLE PINB ^= (1<<PINB5)

int main(void){
	
	/* Replace with your application code */
	
	DDRB |= (1<<DDB5);
	DDRB &= ~(1<<DDB7);
	
	while(1){
		
		if(!(PINB & (1<<PINB7)))
			LED_ON;
		else
			LED_OFF;
		
	}

}

