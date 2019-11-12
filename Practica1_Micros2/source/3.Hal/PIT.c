#include "MKL25Z4.h"
#include "PIT.h"
#include "core_cm0plus.h"

void PIT_vfnDriverInit(void){
	NVIC->ISER[0]|=(1<<PIT_IRQn);
	SIM->SCGC6|=SIM_SCGC6_PIT_MASK;
	PIT->MCR&=~(PIT_MCR_FRZ_MASK);
	PIT->MCR&=~(PIT_MCR_MDIS_MASK);
	PIT->CHANNEL[0].LDVAL=105;						//10us De duracion
	PIT->CHANNEL[0].TCTRL|=PIT_TCTRL_TIE_MASK;
}

void PIT_vfnTimerEnable(void){
	PIT->CHANNEL[0].TCTRL|=PIT_TCTRL_TEN_MASK;
}
void PIT_vfnTimerDisable(void){
	PIT->CHANNEL[0].TCTRL&=~(PIT_TCTRL_TEN_MASK);
}
volatile static uint8_t CNT = 0;
extern uint8_t Flag;
void PIT_IRQ(void){
	PIT_vfnTimerDisable();
	PIT->CHANNEL[0].TFLG|=(1<<31);					//Bajar la bandera
	GPIOD->PCOR = 1<<2;
	Flag = 1;
	PIT_vfnTimerEnable();
}

