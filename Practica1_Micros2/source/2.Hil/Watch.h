/*
 * Watch.h
 *
 *  Created on: 19/11/2019
 *      Author: Poncho
 */

#ifndef WATCH_H_
#define WATCH_H_

#define OneSec 5
#define OneMin 60
#define OneHour 60
#define FullHour 24
#define ChronoSet		(1<<0)
#define AlarmSet		(1<<1)
#define TimerSet		(1<<2)
#define AlarmOn 		'A'
#define AlarmOff 		'O'
#define TimerOn			'T'
#define TimerOff		'D'

void AddClock(void);

void Clock_vfnClock(void);

void Chrono_vfnClock(void);

void Alarm_vfnClock(void);

void Timer_vfnClock(void);

void vfMin_Hour(void);

void Clock_vfnMasterClock (void);




#endif /* 2_HIL_WATCH_H_ */
