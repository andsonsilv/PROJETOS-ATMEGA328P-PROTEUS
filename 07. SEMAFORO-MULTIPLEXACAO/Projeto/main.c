/*
 * Projeto.c
 *
 * Created: 09/04/2018 12:58:24
 * Author : Antonio
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

/************************************************************************/
/* VAR CONTROLE: serve para controlar o tempo, 1 segundos é mais        */
/*  ou menos controle = 3                                               */
/************************************************************************/
volatile unsigned int controle;

/************************************************************************/
/* VAR ESTADO: serve para manipular os estados possíveis                */
/************************************************************************/
unsigned int estado = 0;

/************************************************************************/
/*	VAR CONTADOR: serve para contar os estados                          */
/************************************************************************/
unsigned int contador = 0;

/************************************************************************/
/*  VAR controleBotaoPedreste: se = 0, não foi acionado, senão, foi!    */
/************************************************************************/
unsigned int controleBotaoPedreste = 0;

/************************************************************************/
/* VAR digitoDisplayEsquerda: Equivalente ao display 7S à esquerda      */
/************************************************************************/
unsigned int digitoDisplayEsquerda = 0;

/************************************************************************/
/* VAR digitoDisplayDireita: Equivalente ao display 7S à direita        */
/************************************************************************/
unsigned int digitoDisplayDireita = 0;

/************************************************************************/
/*  VAR flagDisplayContadorDe1A30: como o nome já referencia, tem a     */
/*  função de uma flag em relação a contagem do tempo do pedreste       */
/************************************************************************/
unsigned int flagDisplayContadorDe1A30 = 0;

/************************************************************************/
/*   VAR flagDisplayPArE: controle em relação ao display PAre           */
/************************************************************************/
unsigned int flagDisplayPArE = 0;


/************************************************************************/
/*					DESCRIÇÃO displayPare 							    */
/*		Parametros:														*/
/*			0 - Escreve P												*/
/*			1 - Escreve A												*/
/*			2 - Escreve r												*/	
/*			3 - Escreve E                                               */
/************************************************************************/

void displayPArE(unsigned int chave){
	switch(chave){
		case 0:
			PORTD = 0b11100011;
			break;
		case 1:
			PORTD = 0b11101011;
			break;
		case 2:
			PORTD = 0b10100000;
			break;
		case 3:
			PORTD = 0b11110001;
			break;
	}
}

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


void setup_up(void){

	
	DDRB  = 0xFF;;
	PORTB = 0b00111111;
	
	DDRC  = 0xFF;
	PORTC = 0b00000111;
	
	DDRD  = 0xFB;
	PORTD = 0b00000000;
	
	/* INTERRUPÇÃO BOTÃO */
	PCICR = 0b00000100;
	PCMSK2 |= (1<<PCINT18);
	
	/* INTERRUPÇÂO TIMER */
	TCCR0A=0b00000000;
	TCCR0B=0b00000101;
	TIMSK0=0b00000001;
	
	sei();	
	
}


int main(void){
	
    /* Replace with your application code */
    
	setup_up();
	
	controle = 3;
	
	while(1){
		if(controle == 3){
			controle = 0;
			if(contador < 8)
				estado = 0;
			else if((contador > 7) && (contador < 10))
				estado = 1;
			else if(contador == 10)
				estado = 2;
			else if((contador > 10) && (contador < 19))
				estado = 3;
			else if((contador > 18) && (contador < 21))
				estado = 4;
			else if(contador == 21)
				estado = 5;
			else{
			}
			
			
			if((estado == 2) || (estado == 5)){
				if(estado == 2){
					if(controleBotaoPedreste == 0){
						contador++;
					}	
				}else{
					if(controleBotaoPedreste == 0){
						contador = 0;
					}
				}
			}else{
				contador++;
			}
			
			
			if(flagDisplayContadorDe1A30 == 0){
				if(flagDisplayPArE == 0){
					displayPArE(1);
					PORTC |= (1<<PORTC0);
					PORTC &= ~(1<<PORTC1);
					//DELAY: NA PRATICA NAO HA NECESSIDADE
					for(int i = 0; i < 30000; i++){
						
					}
					displayPArE(0);
					PORTC &= ~(1<<PORTC0);
					PORTC |= (1<<PORTC1);
					//DELAY: NA PRATICA NAO HA NECESSIDADE
					for(int i = 0; i < 30000; i++){
						
					}
					flagDisplayPArE = 1;
				}else{
					displayPArE(3);
					PORTC |= (1<<PORTC0);
					PORTC &= ~(1<<PORTC1);
					//DELAY: NA PRATICA NAO HA NECESSIDADE
					for(int i = 0; i < 30000; i++){
						
					}
					displayPArE(2);
					PORTC &= ~(1<<PORTC0);
					PORTC |= (1<<PORTC1);
					//DELAY: NA PRATICA NAO HA NECESSIDADE
					for(int i = 0; i < 30000; i++){
						
					}
					flagDisplayPArE = 0;
				}
			}
			
			
			
			switch(estado){
				case 0:
					PORTB = 0b00100001;
					PORTC |= (1<<PORTC2);
					break;
				case 1:
					PORTB = 0b00010001;
					PORTC |= (1<<PORTC2);
					break;
				case 2:
					PORTB = 0b00010001;
					if(controleBotaoPedreste == 1){
						flagDisplayContadorDe1A30 = 1;
							PORTB = 0b00001001;
							PORTC &= ~(1<<PORTC2);
							for(int i = 0; i < 1; i++){
								display7S(digitoDisplayEsquerda);
								PORTC |= (1<<PORTC0);
								PORTC &= ~(1<<PORTC1);
								//DELAY: NA PRATICA NAO HA NECESSIDADE
								for(int i = 0; i < 30000; i++){
									
								}
								display7S(digitoDisplayDireita);
								PORTC &= ~(1<<PORTC0);
								PORTC |= (1<<PORTC1);
								//DELAY: NA PRATICA NAO HA NECESSIDADE
								for(int i = 0; i < 30000; i++){
									
								}
								if(digitoDisplayDireita == 2){
									PORTC |= (1<<PORTC2);
								}
								if(digitoDisplayDireita == 3){
									controleBotaoPedreste = 0;
									digitoDisplayEsquerda = 0;
									digitoDisplayDireita = 0;
									PORTD = 0b00000000;
									estado = 3;
									contador = 11;
									flagDisplayContadorDe1A30 = 0;
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
					break;
				case 3:
					PORTB = 0b00001100;
					PORTC |= (1<<PORTC2);
					break;
				case 4:
					PORTB = 0b00001010;
					PORTC |= (1<<PORTC2);
					break;
				case 5:
					PORTB = 0b00001010;
					if(controleBotaoPedreste == 1){
						flagDisplayContadorDe1A30 = 1;
						PORTB = 0b00001001;
						PORTC &= ~(1<<PORTC2);
						for(int i = 0; i < 1; i++){
							display7S(digitoDisplayEsquerda);
							PORTC |= (1<<PORTC0);
							PORTC &= ~(1<<PORTC1);
							//DELAY: NA PRATICA NAO HA NECESSIDADE
							for(int i = 0; i < 30000; i++){
								
							}
							display7S(digitoDisplayDireita);
							PORTC &= ~(1<<PORTC0);
							PORTC |= (1<<PORTC1);
							//DELAY: NA PRATICA NAO HA NECESSIDADE
							for(int i = 0; i < 30000; i++){
								
							}
							if(digitoDisplayDireita == 2){
								PORTC |= (1<<PORTC2);
							}
							if(digitoDisplayDireita == 3){
								controleBotaoPedreste = 0;
								digitoDisplayEsquerda = 0;
								digitoDisplayDireita = 0;
								PORTD = 0b00000000;
								estado = 0;
								contador = 0;
								flagDisplayContadorDe1A30 = 0;
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
					break;
			}		
		}	
	}
}
ISR(PCINT2_vect){
	if(controleBotaoPedreste == 0){
		controleBotaoPedreste = 1;
	}
}

ISR(TIMER0_OVF_vect){
	controle++;
}