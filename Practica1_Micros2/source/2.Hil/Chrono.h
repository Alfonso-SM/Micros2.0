/*
 * Chrono.h
 *
 *  Created on: 24 nov. 2019
 *      Author: lucky
 */

#ifndef CHRONO_H_
#define CHRONO_H_

#define dOneSec 	50
#define dOneMin 	60
#define dOneHr		60
#define dDecVal		10
#define dAsciiNum	48

typedef enum{
	enCIdle = 0,
	enSet_CSeg,
	enSet_CMin,
	enSet_CHrs,
	enCConf
}tenChronoStates;

void Chrono_vfnInit (void);
void Chrono_vfnClock(void);
void Chrono_OffScreen (void);

#endif /* 2_HIL_CHRONO_H_ */
