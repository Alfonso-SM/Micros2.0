/*
 * Micros2_practica1.h
 *
 *  Created on: 22 sep. 2019
 *      Author: lucky
 */

#ifndef MICROS2_PRACTICA1_H_
#define MICROS2_PRACTICA1_H_

typedef unsigned short uint16;

#define idle		 	0
#define Off				1
#define Drive 			2
#define Reverse			3
#define Pins2Use 		5
#define ClkVal 			1538
#define OneSeg 			790
#define HalfSeg			396
#define TriggerBttn 	16
#define BrakeFlag		(1<<0)
#define ClutchFlag		(1<<1)
#define Ingrese			{73,110,103,114,101,115,101,32,108,97,32,118,101,108,111,99,105,100,97,100,32,109,97,120,105,109,97,32,58}
#define Velocidad		{76,97,32,118,101,108,111,99,105,100,97,100,32,101,115,32,58,32}
#define Velocidad2		{"La velocidad maxima es: "}
#define Gobernar        '1'
#define MostrarVel		'2'
#define ModoLibreIn		'3'
#define ModoLibreOut	'4'
#define UpVel			's'
#define DownVel			'w'
typedef enum{
	enPin0=20,
	enPin1,
	enPin2,
	enPin3,
	enPin4=29,
}enPinsNum;

void vfnParkState(void);
void vfnDriveState(void);
void vfnReverseState(void);
void vfnWhile(void);
void Stopmotor(void);


#endif /* 1_APP_MICROS2_PRACTICA1_H_ */
