
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "UART_DriverInt.h"
#include "PIT.h"
#include "PWMDriver.h"
#include "Watch.h"
#include "MKL25Z4.h"
#include "I2CDrive.h"



uint8 au8Pins2Use[Pins2Use]={enPin0,enPin1,enPin2,enPin3,enPin4};
enClockStates u8StateMachineVal=enClock;
static uint8_t u8StatusFlag = 0;

int main(void)
{

	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<2);
	PORTD->PCR[3] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<3);

	PIT_vfnSetPit(0, 1000, 1);
	PIT_vfnSetPit(1, 20, 1);
	PIT_vfnStartPit(0, 1);
	PIT_vfnStartPit(1, 1);
	UART0_vfnCallbackReg(UART0_Callback);
	GPIO_vfnDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));
	UART_DriverInt();
	PWM_vfnDriverInit ();
	I2C_vfnDriverInit();

	Clock_vfnMasterClock();

	while(1)
	{

	}

	return 0;
}

void UART0_Callback(uint_8 UARTVal)
{
	if(UARTVal==AlarmOn && UARTVal!=AlarmOff){
		PWM_bAlarm ();
	}else if(UARTVal==TimerOn && UARTVal!=TimerOff){
		PWM_bTimer();
	}else if(UARTVal==TimerOff || UARTVal==AlarmOff){
		PWM_bOff();
	}
}

void AddClock(void)
{
	Clock_vfnClock();
	if(u8StatusFlag == ChronoSet)
	{
		Chrono_vfnClock();
	}
	if(u8StatusFlag == AlarmSet)
	{
		Alarm_vfnClock();
	}
	if(u8StatusFlag == TimerSet)
	{
		Timer_vfnClock();
	}
}



