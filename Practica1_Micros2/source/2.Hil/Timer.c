/*
 * Timer.c
 *
 *  Created on: 26/11/2019
 *      Author: Poncho
 */
#include "Micros2_practica1.h"
#include "Timer.h"
#include "OLED_Screen_Driver.h"
#include "Debouncer.h"
#include "MKL25Z4.h"

_Bool bEnable1 = 0;
_Bool bRefresh1 = 0;
_Bool bBusy1 = 1;
_Bool bOnScreen1 = 0;
_Bool bEnableSet=0;
_Bool bFlag=0;
tenTimerStates TimerStates = enTIdle;
uint8_t u8TPit = 0;
uint8_t u8TSec = 0;
uint8_t u8TMin = 0;
uint8_t u8THrs = 0;
static uint8_t Stable=0;
signed char u8SetMin = 0;
signed char u8SetHrs = 0;
char u8TSet[] = {"Set: 00:00"};
char u8TTime[] = {"00:00"};

void Timer_vfnSet_Seg(void);
void Timer_vfnSet_Min (void);
void Timer_vfnSet_Hrs (void);
void Timer_Enable (void);
void Timer_EnableSet (void);
void Timer_vfnStopBttn (void);
void Timer_vfnBttns( void );
void vfn_TimerSet (void);


void Timer_vfnInit(void)
{

		Timer_vfnBttns();

		if( bOnScreen1 )
		{
			Timer_vfnMaster();
		}else{

			bOnScreen1 = 1;

			SSD1306_ClearDisplay();

				SSD1306_DrawRect( 56, 0, 72, 11);

				SSD1306_DrawFastHLine(0,12,128, 1);

				SSD1306_DrawText(14, 2, "Timer", 1);

				SSD1306_DrawText(62, 2, u8TSet, 1);

				SSD1306_DrawText(35, 17, u8TTime , 2);

				SSD1306_Display();
			}
		}




void Timer_vfnClock(void){
	if ( bEnable1 )
	{
		u8TPit++;
	}

	if ( u8TPit >= dOneSec )
	{
		u8TPit = 0;
		bBusy1 = 1;

		if ( bOnScreen1 )
		{
			bRefresh1 = 1;
		}
	}
	if(bEnableSet)
	{
		vfn_TimerSet ();
	}
}

void Timer_vfnMaster (void)
{

	if( bRefresh1 )
	{
		SSD1306_Page2Page(2,3);
		bRefresh1 = 0;
	}

	if( bBusy1 )
	{
		u8TSec--;
		if ( u8TSec == 0 )
		{
			u8TSec = dOneMin;
			u8TMin--;
			TimerStates = enSet_TMin;
			if (u8TMin == 0 )
			{
				u8TMin = dOneHr;
				u8THrs--;
				TimerStates = enSet_THrs;
			}
		}
	}

	switch (TimerStates)
	{
	case enTIdle:		break;
	case enSet_TMin:	Timer_vfnSet_Min(); 	break;
	case enSet_THrs:	Timer_vfnSet_Hrs();	break;
	default:			break;
	}
}



void Timer_vfnSet_Min(void)
{
	u8TTime[4] = u8TMin + dAsciiNum;
	u8TTime[3] = u8TMin / dDecVal + dAsciiNum;

}

void Timer_vfnSet_Hrs(void)
{
	  u8TTime[1] = u8THrs % dDecVal + dAsciiNum;
	  u8TTime[0] = u8THrs / dDecVal + dAsciiNum;

	  Timer_vfnSet_Min();
}

void Timer_OffScreen (void)
{
	bOnScreen1 = 0;
}

void Timer_Enable (void)
{
	bEnable1 ^= 1;
	TimerEnable ();
}
void Timer_EnableSet (void)
{
	bEnableSet ^=1 ;
	if(bEnableSet==0){
		vfn_TimerSet ();
	}
	TimerEnable();
}

void Timer_vfnStopBttn (void)
{
		u8TSec = 0;
		u8TMin = 0;
		u8THrs = 0;
		u8SetMin = 0;
		u8SetHrs = 0;
		bEnable1 = 0;

		Timer_vfnSet_Hrs();

		SSD1306_DrawText(18, 17, u8TTime , 2);

		u8TSet [9] = dAsciiNum;
		u8TSet [8] = dAsciiNum;

		u8TSet[6] = dAsciiNum;
		u8TSet[5] = dAsciiNum;

		SSD1306_DrawText(62, 2, u8TSet, 1);

		SSD1306_Display();
}

void Timer_vfnBttns( void )
{
	if( Dbncr_u8fnRisingEdge ( enModeBttn ) )
	{
		bOnScreen1 = 0;
		Stable=0;
		ChangeScreen();
	}else
	{

		if( Dbncr_u8fnCheckStableState ( enStopBttn ) )
		{
			Stable++;
			if(Stable==50){
			Timer_EnableSet();
			Stable=0;
			}
		}
		if( Dbncr_u8fnRisingEdge ( enStartBttn ) && bEnableSet == 0 )
				{
					Stable=0;
					Timer_Enable();
				}

		if( Dbncr_u8fnRisingEdge ( enStopBttn ) && bEnable1==0 )
		{
			Stable=0;
			Timer_vfnStopBttn();
		}
	}
}
void vfn_TimerSet (void){
	if(bEnableSet!=0){
	if(Dbncr_u8fnRisingEdge ( enStopBttn ) ){
		bFlag^=1;
	}
	if(bFlag){
		if(Dbncr_u8fnRisingEdge ( enStartBttn )){
			u8TMin++;
			Timer_vfnSet_Min();
		}}else{
			if(Dbncr_u8fnRisingEdge ( enStartBttn )){
						u8THrs++;
						Timer_vfnSet_Hrs();
					}
		}}else{
			u8SetMin = u8TMin;
					u8SetHrs = u8THrs;

					u8TSet [9] = (u8SetMin) % dDecVal + dAsciiNum;
					u8TSet [8] = ( u8SetMin) / dDecVal + dAsciiNum;

					u8TSet[6] = (u8SetHrs) % dDecVal + dAsciiNum;
					u8TSet[5] = (u8SetHrs) / dDecVal + dAsciiNum;

					u8SetMin = u8TMin;
					u8SetHrs = u8THrs;

					SSD1306_DrawText(62, 2, u8TSet, 1);

					SSD1306_Page2Page(0,0);

		}
}
