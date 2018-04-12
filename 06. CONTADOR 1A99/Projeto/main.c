/*
 * Projeto.c
 *
 * Created: 12/04/2018 15:14:56
 * Author : Antonio
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

/************************************************************************/
/*                 DESCRIÇÃO 7SEGMENTOS                                 */
/************************************************************************/

void display7S(unsigned int numero){
	switch(numero){
		case 0:
		PORTD = 0b01111011;
		break;
		case 1:
		PORTD = 0b00001010;
		break;
		case 2:
		PORTD = 0b10110011;
		break;
		case 3:
		PORTD = 0b10011011;
		break;
		case 4:
		PORTD = 0b11001010;
		break;
		case 5:
		PORTD = 0b11011001;
		break;
		case 6:
		PORTD = 0b11111001;
		break;
		case 7:
		PORTD = 0b00001011;
		break;
		case 8:
		PORTD = 0b11111011;
		break;
		case 9:
		PORTD = 0b11011011;
		break;
		default:
		PORTD |= (1<<PORTD7);
		break;
	}
}

void setup_uc(void){
	DDRD = 0xFF;
	PORTD = 0x00;
	
	DDRB = 0x03;
	PORTB = 0x00;
	
	/* INTERRUPÇÂO TIMER */
	TCCR0A=0b00000000;
	TCCR0B=0b00000101;
	TIMSK0=0b00000001;
	
	sei();
	
}

/************************************************************************/
/* VAR CONTROLE: serve para controlar o tempo, 1 segundos é mais        */
/*  ou menos controle = 3                                               */
/************************************************************************/
volatile unsigned int controle;

/************************************************************************/
/* VAR digitoDisplayEsquerda: Equivalente ao display 7S à esquerda      */
/************************************************************************/
unsigned int digitoDisplayEsquerda = 0;

/************************************************************************/
/* VAR digitoDisplayDireita: Equivalente ao display 7S à direita        */
/************************************************************************/
unsigned int digitoDisplayDireita = 0;

/************************************************************************/
/*  VAR flagDisplayContadorDe1A99: como o nome já referencia, tem a     */
/*  função de uma flag em relação a contagem do tempo do pedreste       */
/************************************************************************/
unsigned int flagDisplayContadorDe1A90 = 0;

int main(void){
	
    /* Replace with your application code */
	
	setup_uc();
	controle = 1;
	
    while(1){
		
		if(controle == 1){
			controle = 0;
			display7S(digitoDisplayDireita);
			PORTB |= (1<<PORTB0);
			PORTB &= ~(1<<PORTB1);
			//DELAY: NA PRATICA NAO HA NECESSIDADE
			for(int i = 0; i < 30000; i++){
				
			}
			display7S(digitoDisplayEsquerda);
			PORTB &= ~(1<<PORTB0);
			PORTB |= (1<<PORTB1);
			//DELAY: NA PRATICA NAO HA NECESSIDADE
			for(int i = 0; i < 30000; i++){
				
			}
			if((digitoDisplayDireita == 9) && (digitoDisplayEsquerda == 9)){
				digitoDisplayEsquerda = 0;
				digitoDisplayDireita = 0;
			}else{
				if(digitoDisplayEsquerda == 9){
					digitoDisplayEsquerda = 0;
					digitoDisplayDireita++;
				}else{
					digitoDisplayEsquerda++;
				}
			}
		}
	}
}

ISR(TIMER0_OVF_vect){
	controle++;
}