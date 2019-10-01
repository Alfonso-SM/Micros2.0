/*
 * Micros2_practica1.h
 *
 *  Created on: 22 sep. 2019
 *      Author: lucky
 */

#ifndef MICROS2_PRACTICA1_H_
#define MICROS2_PRACTICA1_H_

#define idle		 	0
#define Off				1
#define Drive 			2
#define Reverse			3
#define Pins2Use 		5
#define ClkVal 			1538
#define OneSeg 			790
#define TriggerBttn 	8

typedef enum{
	Clutch=20,
	Brake,
	Acc,
	Gear_Up,
	Gear_Dwn=29,
}enPinConf;


void vfnWhile(void);

#endif /* 1_APP_MICROS2_PRACTICA1_H_ */
