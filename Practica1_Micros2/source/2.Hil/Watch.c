/*
 * Watch.c
 *
 *  Created on: 19/11/2019
 *      Author: Poncho
 */
#include "Watch.h"
#include "MKL25Z4.h"
#include "OLED_Screen_Driver.h"

uint8_t FlagPit=0;
uint8_t Segundos=0;
uint8_t Min=0;
uint8_t Hour=0;

void Clock_vfnDisplayMenu(void);

void Clock_vfnDisplayTime(void);

void Clock_vfnTimerIcon(void);

void Clock_vfnAlarmIcon(void);

void Clock_vfnMasterClock (void)
{
	SSD1306_Begin();

	SSD1306_ClearDisplay();

	Clock_vfnDisplayMenu();

	Clock_vfnDisplayTime();

	Clock_vfnTimerIcon();

	Clock_vfnAlarmIcon();

	SSD1306_Display();
}


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

void Clock_vfnDisplayMenu(void)
{
	SSD1306_DrawRect( 56, 0, 72, 11);

	SSD1306_DrawText(0, 2, "21/Nov/19", 1);

	SSD1306_DrawText(60, 2, "M Tu W Th F", 1);

	SSD1306_INVERSE (101, 1, 113, 9);

//	SSD1306_INVERSE (71, 1, 83, 9);

	SSD1306_DrawFastHLine(0,12,127, 1);
}

void Clock_vfnDisplayTime(void)
{
	SSD1306_DrawText(35, 15, "12:00", 2);
	SSD1306_DrawText(105, 24, "p.m.", 1);
}

void Clock_vfnTimerIcon(void)
{
	SSD1306_DrawTriangle( 18, 17, 24, 17, 21, 21);
	SSD1306_DrawTriangle( 18, 24, 24, 24, 21, 21);
}

void Clock_vfnAlarmIcon(void)
{
	SSD1306_DrawCircle(5, 21, 3);

	SSD1306_DrawPixel(2, 17, 1);
	SSD1306_DrawPixel(1, 18, 1);

	SSD1306_DrawPixel(8, 17, 1);
	SSD1306_DrawPixel(9, 18, 1);
}
