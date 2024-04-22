/* -----------------------------------------------
 Universidad del Valle de Guatemala
 IE2023: Programacion de Microcontroladores
 PWManual.c
 Autor: Ian Anleu Rivera
 Proyecto: Lab 5
 Hardware: ATMEGA328P
 Creado: 17/04/2024
 Ultima modificacion: 17/04/2024
    -----------------------------------------------
*/

#include "PWManual.h"

uint8_t contador_pwm = 0;
uint8_t limite_contador = 0;

ISR(TIMER2_OVF_vect){
	//Cuando llega al tope pasan .5ms entonces se actualiza la señal en PD6
	//dependiendo de la comparación de contadores
	if (contador_pwm >= limite_contador){
		PORTD = 0;
	}
	else{
		PORTD = 0b01000000;
	}
	contador_pwm += 1;
	TCNT2 = TIMERLIMIT;
}

void setupTIMER2(void){
	//Interrupciones
	TIMSK2 = 0;
	TIMSK2 = (1<<TOIE2); //Overflow
	
	//Forma, modo, prescaler
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20); //Operación temporizador | Prescaler 1024 
	
	//Inicial en el valor límite
	TCNT2 = TIMERLIMIT;
}

void actualizar_counterlimit(uint8_t limiteadch){
	limite_contador = limiteadch;
}