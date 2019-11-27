
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "UART_DriverInt.h"
#include "PIT.h"
#include "PWMDriver.h"
#include "Watch.h"
#include "Chrono.h"
#include "Timer.h"
#include "MKL25Z4.h"
#include "I2CDrive.h"
#include "Debouncer.h"


uint8 au8Pins2Use[Pins2Use]={enStart,enStop,enMode,enPic};
enClockStates u8StateMachineVal = enClock;
static uint8_t u8StatusFlag = 0;

int main(void)
{

	 void (*array[]) (void) = {Clock_vfnMasterClock, Timer_vfnInit};

	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<2);
	PORTD->PCR[3] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<3);

	PIT_vfnSetPit(0, 1000, 1);
	PIT_vfnSetPit(1, 20, 1);
	UART0_vfnCallbackReg(UART0_Callback);
	GPIO_vfnDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));
	UART_DriverInt();
	PWM_vfnDriverInit ();
	I2C_vfnDriverInit();
	Clock_vfnInit();
	PIT_vfnStartPit(0, 1);
	PIT_vfnStartPit(1, 1);

//	u8StateMachineVal = enChronometer;
	u8StateMachineVal=enTimer;
	while(1)
	{
		array[u8StateMachineVal]();

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
	Dbncr_vfnDbncr(enModeBttn);
	Dbncr_vfnDbncr(enStartBttn);
	Dbncr_vfnDbncr(enStopBttn);
	Dbncr_vfnDbncr(enPicBttn);
	if(u8StatusFlag == ChronoSet)
	{
		Chrono_vfnClock();
	}else if(u8StatusFlag == TimerSet){
		Timer_vfnClock();
	}

}

void MasterClock(void)
{
	Clock_vfnClock();
}

void ChangeScreen (void)
{
	u8StateMachineVal++;
	if(u8StateMachineVal == enAlarm )
	{
		u8StateMachineVal = enClock;
	}
}

void ChronometerEnable ( void )
{
	u8StatusFlag |= ChronoSet;
}
void TimerEnable ( void )
{
	u8StatusFlag = TimerSet;
}

