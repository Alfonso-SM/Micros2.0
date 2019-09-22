/*
 * GPIODriver.h
 *
 *  Created on: 13 sep. 2019
 *      Author: lucky
 */

#ifndef GPIODRIVER_H_
#define GPIODRIVER_H_

typedef unsigned char uint8;

typedef enum{
	enSegA=0,
	enSegB,
	enSegC,
	enSegD,
	enSegE,
	enSegF,
	enSegG,
	enDP,
	enDis1,
	enDis2,
	enDis3,
	enDis4
}tenMySgmnts;

#define ActGPIO 	256
#define ActGPIO_PullDown 258
#define Blue_LDB	1
#define Blue 		(1<<1)


void GPIO_vfnDriverInit (void);
void GPIO_vfnShiftDispl(uint8 *u8DispFlag, uint8 *u8DispVal);
void GPIO_vfnSetVal(uint8 *u8DispVal);
void GPIO_vfnSetDisplay(uint8 *u8DispFlag);
void GPIO_vfnLEDriverInit(void);
void GPIO_vfnToggleLEd(void);


#endif /* GPIODRIVER_H_ */
