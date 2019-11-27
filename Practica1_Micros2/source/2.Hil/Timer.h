/*
 * Timer.h
 *
 *  Created on: 26/11/2019
 *      Author: Poncho
 */

#ifndef TIMER_H_
#define TIMER_H_

#define dOneSec 	50
#define dOneMin 	60
#define dOneHr		60
#define dDecVal		10
#define dAsciiNum	48


typedef enum{
	enTIdle = 0,
	enSet_TMin,
	enSet_THrs,
	enTConf
}tenTimerStates;

void Timer_vfnInit (void);
void Timer_vfnClock(void);
void Timer_OffScreen (void);
void Timer_vfnMaster(void);



#endif /* 2_HIL_TIMER_H_ */
