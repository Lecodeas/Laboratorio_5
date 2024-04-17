/* -----------------------------------------------
 Universidad del Valle de Guatemala
 IE2023: Programacion de Microcontroladores
 PWM1.h
 Autor: Ian Anleu Rivera
 Proyecto: Prelab 5
 Hardware: ATMEGA328P
 Creado: 14/04/2024
 Ultima modificacion: 14/04/2024
    -----------------------------------------------
*/


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h> //IO registros
#include <stdint.h> //Lib para enteros
#include <avr/interrupt.h> //Lib para interrupciones

//Constantes
#define PWMTOP 39999 
#define SERVOMAX 3999
#define SERVOMIN 1999

void setupPWM1(void);
void actualizar_servo(uint16_t adchleido);

#endif /* PWM1_H_ */