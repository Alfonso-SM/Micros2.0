
#include "MKL25Z4.h"
#include "GPIODriver.h"
#include "ShiftDriver.h"
#include "Debouncer.h"
//Esto se va a comodar despues
typedef unsigned short uint16;
#define idle 0
#define Configuration 1
#define Run 2
void vfnWhile(void);
void vfnTMR(void);
static uint16 u16Clk=4062;
uint16 u8Seg=0;	//Esta tal ves la borre
uint8 au8CountersValues[4]={0,1,3,1};
uint8  u8_20mS=0;
uint8 *pu8Pointer=&au8CountersValues[0];
uint8 u8DsplyOn=1;//Esto tendra un nombre para hacer el siempre jarioso
uint8 StateMachineVal=0;
//Hasta aqui

int main(void){
	GPIO_vfnDriverInit();
	GPIO_vfnLEDriverInit();

	while(1){
		vfnWhile();
		u8Seg++;
		u8_20mS++;
		if(u8Seg==400){
			u8Seg=0;
			GPIO_vfnToggleLEd();
		}
		if (StateMachineVal==idle)
		{
			//Esto sera una funcion
			if(u8DsplyOn==8){
				u8DsplyOn=1;
				pu8Pointer=&au8CountersValues[0];
			}else{
				u8DsplyOn=u8DsplyOn<<1;
				pu8Pointer++;
			}
			Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
			//Hasta aquí
			if (u8_20mS==8)
			{
				u8_20mS=0;
				/*Check_Conf_Bttn();
				Check_Conf_Run();*/
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Configuration)
		{
			if (u8_20mS==8){
				u8_20mS=0;
				/*Check_Conf_Bttn();
				Check_Conf_Run();
				Check_Conf_Left();
				Check_Conf_Right();
				Check_Conf_Up();
				Check_Conf_Down();*/
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Run)
		{
			if (u8_20mS==8)
			{
				u8_20mS=0;
				/*Check_Conf_Bttn();
				Check_Conf_Run();*/
			}else{
				/*No Used*/
			}
			vfnTMR();
		}

	}
	return 0;
}


void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=4062; //32500 será una macro
}

void vfnTMR(void){
	while((au8CountersValues[0]&au8CountersValues[1]&au8CountersValues[2]&au8CountersValues[3])!=0){
	vfnWhile();
	u8Seg++;
	if(u8Seg==400){
				u8Seg=0;
				GPIO_vfnToggleLEd();
				au8CountersValues[0]--;
	if(au8CountersValues[0]==0){
				au8CountersValues[0]=9;
				au8CountersValues[1]--;
			}
			else if(au8CountersValues[1]==0){
				au8CountersValues[1]=5;
				au8CountersValues[2]--;
			}
			else if(au8CountersValues[2]==0){
				au8CountersValues[2]=9;
				au8CountersValues[3]--;
			}
			else if(au8CountersValues[3]==0){
				au8CountersValues[3]=0;
			}
	}
	else{
				//Lo que tiene que checar cada 2.5ms.
				if(u8DsplyOn==8){
					u8DsplyOn=1;
					pu8Pointer=&au8CountersValues[0];
				}else{
					u8DsplyOn=u8DsplyOn<<1;
					pu8Pointer++;
				}
				Shift_vfnDecode(pu8Pointer,&u8DsplyOn); //esta funcion si va ir
			}
	}
}
