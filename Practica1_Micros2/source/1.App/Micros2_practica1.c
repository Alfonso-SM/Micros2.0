
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "Debouncer.h"
#include "PWMDriver.h"
#include "Timer.h"

typedef unsigned short uint16;

static uint16 u16Clk=ClkVal;
uint16 u8Seg=0;
uint8  u8_20mS=0;
uint8 au8Pins2Use[Pins2Use]={Clutch,Brake,Acc,Gear_Up,Gear_Dwn};
uint8 StateMachineVal=0;
uint8 u8FlagReg=0;
uint8 u8Speed=0;

int main(void){

	GPIO_vfnDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));
	PWM_vfnDriverInit ();

	while(1){
		vfnWhile();
		u8Seg++;
		u8_20mS++;
		if(u8Seg==OneSeg){
			vfnTMR();
		}else{
			/*Nothing to do*/
		}
		if (StateMachineVal==idle){
			//Timer_vfnIdle();
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				/*Checar Pines*/
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Off){
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				/*Apagar y checar, creo*/
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Drive){
			if (u8_20mS==TriggerBttn)
			{
				u8_20mS=0;
				/*Checar Pines*/
			}else{
				/*No used*/
			}
		}
		else if(StateMachineVal==Reverse){
			if (u8_20mS==TriggerBttn)
			{
				u8_20mS=0;
				/*Checar Pines*/
			}else{
				/*No used*/
			}
		}
		if(u8Seg==OneSeg){
			u8Seg=0;
		}else{
			/*No used*/
		}
		Timer_vfnIdle();
	}
	return 0;
}


void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=ClkVal;
}



