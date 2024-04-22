/* -----------------------------------------------
 Universidad del Valle de Guatemala
 IE2023: Programacion de Microcontroladores
 PWManual.h
 Autor: Ian Anleu Rivera
 Proyecto: Lab 5
 Hardware: ATMEGA328P
 Creado: 17/04/2024
 Ultima modificacion: 17/04/2024
    -----------------------------------------------
*/


#ifndef PWMANUAL_H_
#define PWMANUAL_H_

#include <avr/io.h> //IO registros
#include <stdint.h> //Lib para enteros
#include <avr/interrupt.h> //Lib para interrupciones

#define TIMERLIMIT 255 //.064 ms en tempo mode

void setupTIMER2(void);
void actualizar_counterlimit(uint8_t limiteadch);

#endif /* PWMANUAL_H_ */