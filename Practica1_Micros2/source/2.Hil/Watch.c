/*
 * Watch.c
 *
 *  Created on: 19/11/2019
 *      Author: Poncho
 */
#include "Watch.h"
#include "MKL25Z4.h"

uint8_t FlagPit=0;
uint8_t Segundos=0;
uint8_t Min=0;
uint8_t Hour=0;




void Clock_vfnClock(void){
	FlagPit++;

	if(FlagPit==OneSec){
		FlagPit=0;
		Segundos ++;
			/*If(ChronoBotton==1){
					SegundosChrono++;
				}else if(Alarm!=0){
						SegundosAlarm--;
						if(Alarm==0){
							u8StatusFlag=AlarmSet;
							ON=1;
						}
					}else if(Timer!=0){
						SegundosTimer++
					}*/
	}else if(Segundos==OneMin){
		vfMin_Hour();
	}

}

void Chrono_vfnClock(void){
	//Display Chrono Clock
	//ChronoBotton=1;
	//SegundosChrono++;
}

void Alarm_vfnClock(void){
	//SetAlarm
	//Display AlarmClock
	/* if(ON=1){
	 	 UART_bfnSend (AlarmOn);
	 }Else{
	 	 UART_bfnSend (AlarmOff);
	 }
	 */
}

void Timer_vfnClock(void){
	//Display TimerClock
	/*if()
	 *
	 */
}

void vfMin_Hour(void){
	Min++;
	if(Min==OneHour){
		Min=0;
		Segundos=0;
		Hour++;
	}else if(Hour==FullHour){
		Hour=0;
		Min=0;
		Segundos=0;
	}

}
