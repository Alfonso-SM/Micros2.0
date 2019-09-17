

#include <3.Hal/GPIODriver.h>
#include "MKL25Z4.h"

void DElAY(void);

void GPIO_vfnDriverInit (void){
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTE_MASK;

	PORTC->PCR[enSegA]|=ActGPIO;
	PORTC->PCR[enSegB]|=ActGPIO;
	PORTC->PCR[enSegC]|=ActGPIO;
	PORTC->PCR[enSegD]|=ActGPIO;
	PORTC->PCR[enSegE]|=ActGPIO;
	PORTC->PCR[enSegF]|=ActGPIO;
	PORTC->PCR[enSegG]|=ActGPIO;
	PORTC->PCR[enDis1]|=ActGPIO;
	PORTC->PCR[enDis2]|=ActGPIO;
	PORTC->PCR[enDis3]|=ActGPIO;
	PORTC->PCR[enDis4]|=ActGPIO;

	GPIOC->PDDR|=(1<<enSegA);
	GPIOC->PDDR|=(1<<enSegB);
	GPIOC->PDDR|=(1<<enSegC);
	GPIOC->PDDR|=(1<<enSegD);
	GPIOC->PDDR|=(1<<enSegE);
	GPIOC->PDDR|=(1<<enSegF);
	GPIOC->PDDR|=(1<<enSegG);
	GPIOC->PDDR|=(1<<enDis1);
	GPIOC->PDDR|=(1<<enDis2);
	GPIOC->PDDR|=(1<<enDis3);
	GPIOC->PDDR|=(1<<enDis4);

	GPIOC->PSOR|=(1<<enSegA);
	GPIOC->PSOR|=(1<<enSegB);
	GPIOC->PSOR|=(1<<enSegC);
	GPIOC->PSOR|=(1<<enSegD);
	//GPIOC->PSOR|=(1<<enSegE);
	//GPIOC->PSOR|=(1<<enSegF);
	GPIOC->PSOR|=(1<<enSegG);
}



void GPIO_vfnShiftDispl(uint8 *u8DispFlag, uint8 *u8DispVal){
		GPIOC->PCOR|=127;
		GPIOC->PSOR|=*u8DispVal;
		GPIOC->PSOR|=(15<<enDis1);
		GPIOC->PCOR|=((*u8DispFlag)<<enDis1);
}

void GPIO_vfnLEDriverInit(void){
	SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[Blue_LDB]|=ActGPIO;
	GPIOD->PDDR|=Blue;
	GPIOD->PSOR=Blue;
}

void GPIO_vfnToggleLEd(void){
	GPIOD->PTOR=Blue;
}

void DELAY (void){
	uint8 de=255;
	while(de){
		de--;
	}
}


