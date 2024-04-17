/* -----------------------------------------------
 Universidad del Valle de Guatemala
 IE2023: Programacion de Microcontroladores
 PWMServos_LED.c
 Autor: Ian Anleu Rivera
 Proyecto: Lab 5
 Hardware: ATMEGA328P
 Creado: 15/04/2024
 Ultima modificacion: 15/04/2024
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
uint8_t servo_a_modificar = 1;

//PROTOTIPOS DE FUNCIÓN
void setup(void);
void setupADC(void);

//INTERRUPCIONES

//ADC
ISR(ADC_vect){
	valoradc = ADCH; // Almacenar valor
	ADCSRA |= (1<<ADIF); // Apagar bandera
	if (servo_a_modificar == 1){
		servo_a_modificar = 2;
		//Remux ADC6
		ADMUX = 0; //Limpiar multiplexado
		ADMUX |= (1<<REFS0)|(1<<ADLAR)|(1<<MUX2)|(1<<MUX1); //Vcc ref | Just. Izq. | Mux ADC6	
	}
	else
	{
		servo_a_modificar = 1;
		//Remux ADC7
		ADMUX = 0; //Limpiar multiplexado
		ADMUX |= (1<<REFS0)|(1<<ADLAR)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0); //Vcc ref | Just. Izq. | Mux ADC7
	}
}

//PRINCIPAL
int main(void)
{
	cli();
	setup();
	setupADC();
	setupPWM1();
	sei();
	
	actualizar_servo(0,1); //Primer inicio de Servo1
	actualizar_servo(0,2); //Primer inicio de Servo2
	ADCSRA |= (1<<ADSC); //Primer inicio de ADC

	while (1)
	{
		_delay_ms(10);
		actualizar_servo(valoradc, 1);
		ADCSRA |= (1<<ADSC); //Volver a iniciar
		_delay_ms(10);
		actualizar_servo(valoradc, 2);
		ADCSRA |= (1<<ADSC); //Volver a iniciar
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
	DDRB |= (1<<DDB2)|(1<<DDB1);
	//Otros servos
}

void setupADC(void){
	ADMUX = 0;
	ADMUX |= (1<<REFS0)|(1<<ADLAR)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0); //Vcc ref | Just. Izq. | Mux ADC7
	ADCSRA = 0;
	ADCSRA |= (1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Int. En | Presc. 128 (125kHz)
	ADCSRA |= (1<<ADEN); // Enable
}