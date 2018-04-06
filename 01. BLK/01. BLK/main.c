/*
 * 01. BLK.c
 *
 * Created: 06/04/2018 00:38:27
 * Author : Antonio
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	
	/* Replace with your application code */
	
	DDRB |= (1 << DDB2);
	
	while(1){
		
		PORTB ^= (1 << PORTB2);
		_delay_ms(2000);
		
	}
	
}

