/*
 * Debouncer.h
 *
 *  Created on: 19/09/2019
 *      Author: Poncho
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_
//typedef unsigned char uint_8 ;
typedef unsigned long uint_32;

#define LastValue 2
#define ShootCapture 3

typedef enum{
	enStartBttn = 0,
	enStopBttn,
	enModeBttn,
	enPicBttn,
	enTotalPins
}tenPinInputs;

typedef struct{
	unsigned char Pin;
	unsigned char LastStableState;
	unsigned char u8Shots[ShootCapture];
	unsigned char u8Cntr;
	unsigned char u8Stablestate ;
}tstDbncrInfo;


void Dbncr_vfnInit(unsigned char PinVal);
void Dbncr_vfnDbncr(unsigned char u8Pin2Check);
unsigned char Dbncr_u8fnRisingEdge(unsigned char u8Pin2Check);
unsigned char Dbncr_u8fnCheckStableState(unsigned char u8Pin2Check);
void Dbncr_vfCheckBttns4Parking(void);





#endif /* 3_HAL_DEBOUNCER_H_ */
