/*
 * Debouncer.h
 *
 *  Created on: 19/09/2019
 *      Author: Poncho
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_
typedef char uint_8 ;

typedef struct{
	uint_8 Port;
	uint_8 Pin;
	uint_8 LastStableState;
	uint_8 u8Shots[3];
	uint_8 u8Cntr;
	uint_8 u8Stablestate ;
}DbncrInfo;

typedef enum{
	Left=20,
	Right,
	Up,
	Down,
	Conf=29,
	Start
}enPinConf;




#endif /* 3_HAL_DEBOUNCER_H_ */
