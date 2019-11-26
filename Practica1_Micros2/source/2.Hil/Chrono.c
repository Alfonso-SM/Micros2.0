/*
 * Chrono.c
 *
 *  Created on: 24 nov. 2019
 *      Author: lucky
 */

#include "Micros2_practica1.h"
#include "Chrono.h"
#include "OLED_Screen_Driver.h"
#include "Debouncer.h"
#include "MKL25Z4.h"

#define NULL ((void *)0)


_Bool bEnable = 0;
_Bool bRefresh = 0;
_Bool bBusy = 1;
_Bool bOnScreen = 0;
tenChronoStates ChronoStates = enCIdle;
uint8_t u8Pit = 0;
uint8_t u8CSec = 0;
uint8_t u8CMin = 0;
uint8_t u8CHrs = 0;
signed char u8LapSec = 0;
signed char u8LapMin = 0;
char u8CLap[] = {"Lap: 00:00"};
char u8CTime[] = {"00:00:00"};

void Chrono_vfnSet_Seg(void);
void Chrono_vfnSet_Min (void);
void Chrono_vfnSet_Hrs (void);
void Chrono_vfnMaster(void);
void Chrono_Enable (void);
void Chrono_vfnStopBttn (void);
void Chrono_vfnBttns( void );




void Chrono_vfnInit(void)
{

	Chrono_vfnBttns();

	if( bOnScreen )
	{
		Chrono_vfnMaster();
	}else{

		bOnScreen = 1;

		SSD1306_ClearDisplay();

		SSD1306_DrawRect( 56, 0, 72, 11);

		SSD1306_DrawFastHLine(0,12,128, 1);

		SSD1306_DrawText(10, 2, "Chrono", 1);

		SSD1306_DrawText(62, 2, u8CLap, 1);

		SSD1306_DrawText(18, 17, u8CTime , 2);

		SSD1306_Display();
	}
}

void Chrono_vfnClock(void){
	if ( bEnable )
	{
		u8Pit++;
	}

	if ( u8Pit >= dOneSec )
	{
		u8Pit = 0;
		bBusy = 1;

		if ( bOnScreen )
		{
			bRefresh = 1;
		}
	}
}

void Chrono_vfnMaster (void)
{

	if( bRefresh )
	{
		SSD1306_Page2Page(2,3);
		bRefresh = 0;
	}

	if( bBusy )
	{
		u8CSec++;
		ChronoStates = enSet_CSeg;
		if ( u8CSec == dOneMin )
		{
			u8CSec = 0;
			u8CMin++;
			ChronoStates = enSet_CMin;
			if (u8CMin == dOneHr )
			{
				u8CMin = 0;
				u8CHrs++;
				ChronoStates = enSet_CHrs;
			}
		}
	}

	switch (ChronoStates)
	{
	case enCIdle:		break;
	case enSet_CSeg:	Chrono_vfnSet_Seg();	break;
	case enSet_CMin:	Chrono_vfnSet_Min(); 	break;
	case enSet_CHrs:	Chrono_vfnSet_Hrs();	break;
	default:			break;
	}
}

void Chrono_vfnSet_Seg(void)
{
	u8CTime [7] = u8CSec % dDecVal + dAsciiNum;
	u8CTime [6] = u8CSec / dDecVal + dAsciiNum;

	SSD1306_DrawText(18, 17, u8CTime , 2);

	bBusy = 0;

	ChronoStates = enCIdle;
}

void Chrono_vfnSet_Min(void)
{
	  u8CTime[4] = u8CMin % dDecVal + dAsciiNum;
	  u8CTime[3] = u8CMin / dDecVal + dAsciiNum;

	  Chrono_vfnSet_Seg();
}

void Chrono_vfnSet_Hrs(void)
{
	  u8CTime[1] = u8CHrs % dDecVal + dAsciiNum;
	  u8CTime[0] = u8CHrs / dDecVal + dAsciiNum;

	  Chrono_vfnSet_Min();
}

void Chrono_OffScreen (void)
{
	bOnScreen = 0;
}

void Chrono_Enable (void)
{
	bEnable ^= 1;
	ChronometerEnable ();
}

void Chrono_vfnStopBttn (void)
{
	if( bEnable )
	{

		u8LapSec = u8CSec - u8LapSec;
		u8LapMin = u8CMin - u8LapMin;

		if(u8LapSec < 0){
			u8LapSec += 60;
			u8LapMin -= 1;
		}

		u8CLap [9] = (u8LapSec) % dDecVal + dAsciiNum;
		u8CLap [8] = ( u8LapSec) / dDecVal + dAsciiNum;

		u8CLap[6] = (u8LapMin) % dDecVal + dAsciiNum;
		u8CLap[5] = (u8LapMin) / dDecVal + dAsciiNum;

		u8LapSec = u8CSec;
		u8LapMin = u8CMin;

		SSD1306_DrawText(62, 2, u8CLap, 1);

		SSD1306_Page2Page(0,0);
	}else{
		u8CSec = 0;
		u8CMin = 0;
		u8CHrs = 0;
		u8LapSec = 0;
		u8LapMin = 0;
		bEnable = 0;

		Chrono_vfnSet_Hrs();

		SSD1306_DrawText(18, 17, u8CTime , 2);

		u8CLap [9] = dAsciiNum;
		u8CLap [8] = dAsciiNum;

		u8CLap[6] = dAsciiNum;
		u8CLap[5] = dAsciiNum;

		SSD1306_DrawText(62, 2, u8CLap, 1);

		SSD1306_Display();
	}
}

void Chrono_vfnBttns( void )
{
	if( Dbncr_u8fnRisingEdge ( enModeBttn ) )
	{
		bOnScreen = 0;
		ChangeScreen();
	}else
	{

		if( Dbncr_u8fnRisingEdge ( enStartBttn ) )
		{
			Chrono_Enable();
		}

		if( Dbncr_u8fnRisingEdge ( enStopBttn ) )
		{
			Chrono_vfnStopBttn();
		}
	}
}
