/* -----------------------------------------------
 Universidad del Valle de Guatemala
 IE2023: Programacion de Microcontroladores
 PWMPotenciometro.c
 Autor: Ian Anleu Rivera
 Proyecto: Prelab 5
 Hardware: ATMEGA328P
 Creado: 14/04/2024
 Ultima modificacion: 14/04/2024
    -----------------------------------------------
*/

//HEADER FILES
#define F_CPU 16000000 //Frecuencia es 16Mhz
#include <avr/io.h> //IO registros
#include <util/delay.h> // Lib para delays
#include <stdint.h> //Lib para enteros
#include <avr/interrupt.h> //Lib para interrupciones
#include "PWM1/PWM1.h" //PWM1

//VARIABLES GLOBALES
//Otras variables
uint8_t servo = 0;
uint8_t valoradc = 0;

//PROTOTIPOS DE FUNCIÓN
void setup(void);
void setupADC(void);

//INTERRUPCIONES

//ADC
ISR(ADC_vect){
	valoradc = ADCH; // Almacenar valor
	ADCSRA |= (1<<ADIF); // Apagar bandera
	ADCSRA |= (1<<ADSC); //Volver a iniciar
}

//PRINCIPAL
int main(void)
{
	cli();
	setup();
	setupADC();
	setupPWM1();
	sei();
	
	actualizar_servo(0); //Primer inicio de Servo
	ADCSRA |= (1<<ADSC); //Primer inicio de ADC

	while (1)
	{
		actualizar_servo(valoradc);
	}// Fin Main Loop
}

// OTRAS FUNCIONES
void setup(void){
	//ENTRADAS Y SALIDAS -----------------------
	//Entradas
	// No hay digitales, solo ADC
	
	//Salidas
	//PB1 va al Servo 1 (OC1A)
	DDRB = 0;
	DDRB |= (1<<DDB1);
	//Otros servos
}

void setupADC(void){
	ADMUX = 0;
	ADMUX |= (1<<REFS0)|(1<<ADLAR)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0); //Vcc ref | Just. Izq. | Mux ADC7
	ADCSRA = 0;
	ADCSRA |= (1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Int. En | Presc. 128 (125kHz)
	ADCSRA |= (1<<ADEN); // Enable
}