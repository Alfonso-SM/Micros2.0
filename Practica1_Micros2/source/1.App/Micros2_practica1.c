
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "UART_DriverInt.h"
#include "PIT.h"
#include "MKL25Z4.h"



uint8 au8Pins2Use[Pins2Use]={enPin0,enPin1,enPin2,enPin3,enPin4};
uint8 StateMachineVal=0;

int main(void)
{

	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<2);
	PORTD->PCR[3] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<3);

	PIT_vfnCallBackReg(PIT_vfnCallBack);

	PIT_vfnSetPit(0, 1000, 1);
	PIT_vfnSetPit(1, 20, 1);
	PIT_vfnStartPit(0, 1);
	PIT_vfnStartPit(1, 1);
	UART0_vfnCallbackReg(UART0_Callback);
	GPIO_vfnDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));
	UART_DriverInt();


	while(1)
	{

	}

	return 0;
}
void UART0_Callback(uint_8 UARTVal)
{

}

void PIT_vfnCallBack (void)
{
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK){
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
		GPIOD->PTOR |= 1<<2;
	}
	if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK){
		PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
		GPIOD->PTOR |= 1<<3;
	}
}


