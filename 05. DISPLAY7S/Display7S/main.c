/*
 * Display7S.c
 *
 * Created: 08/04/2018 00:35:23
 * Author : Antonio
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

char aux = 0;

char DS7[] = {  //-gfedcba
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
};

ISR(INT0_vect){
	aux++;
	PORTC = DS7[aux%10];
}

ISR(INT1_vect){
	aux--;
	PORTC = DS7[aux%10];
}

ISR(PCINT0_vect){
	if(PINB & 1)
		PORTB ^= (1<<PORTB2);
}

ISR(PCINT2_vect){
	if(PIND & 1)
		PORTB ^= (1<<PORTB3);
}


void setup_uc(void){
	
	//SET all PORTB as output, except B0
	DDRB = 0xFE; 
	//SET B0 Pull UP
	PORTB = 0x01;
	
	//SET all PORTC as output
	DDRC  = 0xFF;
	PORTC = 0b00111111;		//initialize display with '0'
	
	//SET D0, D1, D2 and D3 as input, all others are output
	DDRD = 0xF0;
	//SET D0, D1, D2 and D3 Pull UP
	PORTD = 0x0F;

	//Config INT0 and INT1 active on falling edge
	EICRA = 0b00001010;
	//Enable INT0 and INT1
	EIMSK = 0x03;
		
		
	//Enable Pin Change INT[0] and Pin Change INT[2]
	//PCICR = 0b00000101;
	PCICR |= (1<<PCIE0);
	PCICR |= (1<<PCIE2);
	
	/*Pin Change Interrupt MASK*/
	/*bits 23 to 16*/
	PCMSK2 = 0x01;
	/*bits 14 to 08*//*Doesnt exist PCINT15*/
	PCMSK1 = 0x00;
	/*bits 07 to 00*/
	PCMSK0 = 0x01;
	
	//Turn on all interrupts
	sei();
	
}

int main(void){
    
	setup_uc();
    
	while(1){
	
	    if(PIND & (1<<1))
		    PORTB |= (1<<PORTB1);
	    else
		    PORTB &= ~(1<<PORTB1);
    
	}
	return 0;
}

