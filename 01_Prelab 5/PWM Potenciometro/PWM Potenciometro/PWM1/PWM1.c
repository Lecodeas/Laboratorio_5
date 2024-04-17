/* -----------------------------------------------
 Universidad del Valle de Guatemala
 IE2023: Programacion de Microcontroladores
 PWM1.c
 Autor: Ian Anleu Rivera
 Proyecto: Prelab 5
 Hardware: ATMEGA328P
 Creado: 14/04/2024
 Ultima modificacion: 14/04/2024
    -----------------------------------------------
*/

#include "PWM1.h"

uint8_t listo_actualizar_pwm = 0;

ISR(TIMER1_OVF_vect){
	//Regresa a los 20ms
	listo_actualizar_pwm = 0;
}

ISR(TIMER1_COMPA_vect){
	//Probando si hace los ms necesarios
}

void setupPWM1(void){
	//Interrupciones
	TIMSK1 = 0;
	TIMSK1 = (1<<OCIE1A) | (1<<TOIE1); //Compare A, Overflow
	
	//Top en ICR1
	ICR1H = (PWMTOP & 0xFF00) >> 8;
	ICR1L = (PWMTOP & 0x00FF);
	
	//Inicializar servo al minimo
	OCR1AH = (SERVOMIN & 0xFF00) >> 8;
	OCR1AL = (SERVOMIN & 0x00FF);
	
	//Forma, modo, prescaler
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1A |= (1<<COM1A1) | (1<<WGM11); //A1 No inverted | Fast con ICR1 Top
	TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11); //Fast con ICR1 Top | Prescaler 8 
}

static void actualizar_pwm(uint16_t i){
	listo_actualizar_pwm = 1;
	while (listo_actualizar_pwm != 0){
		//El valor del pulso depende del leído en ADCH
		OCR1AH = (i & 0xFF00) >> 8;
		OCR1AL = (i & 0x00FF);
	}
}

void actualizar_servo(uint16_t adchleido){
	//Conversión de lectura de ADC a pulso en PWM
	float razon = (float)adchleido/(float)256;
	razon = (((float)SERVOMAX - (float)SERVOMIN)*razon) + (float)SERVOMIN;
	uint16_t valorservo = (uint16_t)razon;
	actualizar_pwm(valorservo);
}