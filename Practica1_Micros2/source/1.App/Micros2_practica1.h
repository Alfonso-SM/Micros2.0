/*
 * Micros2_practica1.h
 *
 *  Created on: 22 sep. 2019
 *      Author: lucky
 */

#ifndef MICROS2_PRACTICA1_H_
#define MICROS2_PRACTICA1_H_

typedef unsigned short uint16;

#define Pins2Use 		5
#define ChronoSet		(1<<0)
#define AlarmSet		(1<<1)
#define TimerSet		(1<<2)
typedef enum{
	enPin0=20,
	enPin1,
	enPin2,
	enPin3,
	enPin4=29,
}enPinsNum;

typedef enum{
	enClock = 0,
	enChronometer,
	enAlarm,
	enTimer
}enClockStates;

void AddClock(void);


#endif /* 1_APP_MICROS2_PRACTICA1_H_ */
