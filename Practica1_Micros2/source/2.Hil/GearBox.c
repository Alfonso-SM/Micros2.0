/*
 * GearBox.c
 *
 *  Created on: 2 oct. 2019
 *      Author: lucky
 */

#include "Micros2_practica1.h"
#include "GearBox.h"
#include "Debouncer.h"
#include "Timer.h"
#include "PWMDriver.h"
#include "UART_DriverInt.h"
#include "GPIODriver.h"


extern uint16 u8Seg;
uint16 u8Speed=0;
static uint8 y=0;
uint16 vel;
uint16 vel1;
uint16 a[6][3]={
		{10,0,0},
		{1,62,0},
		{2,124,62},
		{3,186,124},
		{4,250,186},
		{11,50,0}
};

void Gear_vfnParkGear(void);
void Gear_vfnGearDrive(void);
void Gear_vfnFastBreak(void);

tstGearInfo astGearsData[enTotalGears];
static tenGearConf u8Index=enParkGear;
static uint8 u8Delay=0;
uint8 Setvel(uint8 x){
	if(y==0){
		UART_bfnSend(x);
		vel=((x-48)*100);
		y++;
	}else if (y==1){
		UART_bfnSend(x);
		vel+=((x-48)*10);
		y++;
	}else{
		UART_bfnSend(x);
		vel+=(x-48);
		y=0;
		vel1=vel;
		vel=vel/4;
		for (uint8 i=1;i<5;i++){
			for(uint8 j=1;j<3;j++){
				if(y==0){
					a[i][j]=vel;
					y++;
				}else if(y==1){
					a[i][j]=0;
					y++;
				}else if(y==2){
					a[i][j]=vel*2;
					y++;
				}else if(y==3){
					a[i][j]=vel;
					y++;
				}else if(y==4){
					a[i][j]=vel*3;
					y++;
				}else if(y==5){
					a[i][j]=vel*2;
					y++;
				}
				else if(y==6){
					a[i][j]=vel1;
					y++;
				}else if(y==7){
					a[i][j]=vel*3;
					y=0;
					Gear_InitSt();
				}

			}
		}
		return SUCCESS;
	}
	return ERROR;
}

void Gear_InitSt(void){
	for (uint8 i=0;i<6;i++){
		for(uint8 j=0;j<3;j++){
			if(j==0){
				astGearsData[i].u8GearName=a[i][j];
			}else if(j==1){
				astGearsData[i].u8MaxVal=a[i][j];
			}else{
				astGearsData[i].u8MinVal=a[i][j];
			}
		}
	}
}

void Gear_vfnParkGear(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if(Dbncr_u8fnCheckStableState(enBrake)){
		if(Dbncr_u8fnCheckStableState(enClutch)){
			Dbncr_vfnDbncr(enGearUp);
			if(Dbncr_u8fnRisingEdge(enGearUp)){
				u8Index=enFirstGear;
				vfnDriveState();
			}else{
				Dbncr_vfnDbncr(enGearDwn);
				if(Dbncr_u8fnRisingEdge(enGearDwn)){
					u8Index=enReverseGear;
					vfnReverseState();
				}
			}
		}
	}
}

void Gear_vfnGearDrive(void){
	u8Delay++;
	if(Dbncr_u8fnCheckStableState(enAcc)){
				if((u8Speed<astGearsData[u8Index].u8MaxVal)&&(u8Speed>=astGearsData[u8Index].u8MinVal-10)){
					vfnTMR();
					u8Speed++;
				}else{
					if(u8Speed<astGearsData[u8Index].u8MinVal-10){
						if(u8Delay==3){
							vfnTMR();
							u8Speed++;
						}
					}
				}
		}else if(u8Speed){
			if(u8Speed>astGearsData[u8Index].u8MaxVal){
				Gear_vfnFastBreak();
			}else{
				vfnTMRLess();
				u8Speed--;
			}
		}
	PWM_Acc_or_Dec(u8Speed,astGearsData[4].u8MaxVal);
		if(u8Delay==3){
			u8Delay=0;
		}
}

void Gear_vfnBrake(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if(u8Speed){
		Gear_vfnFastBreak();
		if((u8Speed<astGearsData[u8Index].u8MinVal)&&(!Dbncr_u8fnCheckStableState(enClutch))){
			u8Index--;
		}
	}else{
		if(!Dbncr_u8fnCheckStableState(enClutch)){
			vfnParkState();
			u8Index=enParkGear;
		}
	}
	PWM_Acc_or_Dec(u8Speed,astGearsData[4].u8MaxVal);
}

void Gear_vfnFastBreak(void){
	vfnTMRLess();
	u8Speed--;
}


void Gear_vfCheckBttns4Parking(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if(Dbncr_u8fnCheckStableState(enBrake)){
		Dbncr_vfnDbncr(enClutch);
		Dbncr_vfnDbncr(enAcc);
		Gear_vfnParkGear();
	}else{
		Dbncr_vfnDbncr(enBrake);
	}
}

void Gear_vfCheckBttns4Drive(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	Dbncr_vfnDbncr(enBrake);
	Dbncr_vfnDbncr(enClutch);
	if(Dbncr_u8fnCheckStableState(enBrake)){
		Gear_vfnBrake();
	}else{
		Dbncr_vfnDbncr(enGearUp);
		Dbncr_vfnDbncr(enGearDwn);
		if (Dbncr_u8fnCheckStableState(enClutch)){
			if(u8Index!=enReverseGear){
				if(Dbncr_u8fnRisingEdge(enGearUp)){
					if((u8Index!=4)){
					u8Index++;
					}
				}else{
					if(Dbncr_u8fnRisingEdge(enGearDwn)){
						if(u8Index>1){
							u8Index--;

						}
					}
				}
			}
			if(u8Speed&&(u8Seg==160)){
				vfnTMRLess();
				u8Speed--;
			}
		}
		if(u8Speed>=astGearsData[u8Index].u8MaxVal){
			vfnTMRLess();
			u8Speed--;
		}else{
			Dbncr_vfnDbncr(enAcc);
			if(u8Seg==160){
			Gear_vfnGearDrive();
			}
		}
	}
}

void printvel(void){
	uint8 vel=0;
	uint8 print[18]=Velocidad;
				for(int i=0;i<18;i++){
					while(UART_bfnSend(print[i])==ERROR){
						}
					}
		vel=(u8Speed/100)+48;
		while(UART_bfnSend(vel)==ERROR){

		}


		vel=((u8Speed%100)/10)+48;
		while(UART_bfnSend(vel)==ERROR){
										}
		vel=((u8Speed%10))+48;
				while(UART_bfnSend(vel)==ERROR){
												}


}
void onlyacc(void){
	if(u8Speed==0||u8Speed>=astGearsData[u8Index].u8MaxVal){
		if(u8Index<4){
		GPIO_vfnDrive();
		u8Index++;
		}
	}
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if((u8Speed<astGearsData[u8Index].u8MaxVal)&&(u8Speed>=astGearsData[u8Index].u8MinVal-10)){
		vfnTMR();
		u8Speed++;
	}else{
		if(u8Speed<astGearsData[u8Index].u8MinVal-10){
			if(u8Delay==3){
				vfnTMR();
				u8Speed++;
			}
		}
	}
	PWM_Acc_or_Dec(u8Speed,astGearsData[4].u8MaxVal);
}
uint8 check(void){
	if(u8Speed!=0){
		return ERROR;
	}
	else{
		u8Index=enParkGear;
		return SUCCESS;
	}


}
