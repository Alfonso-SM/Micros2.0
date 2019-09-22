
#include "MKL25Z4.h"
#include "GPIODriver.h"
#include "ShiftDriver.h"
#include "Debouncer.h"
//Esto se va a comodar despues
typedef unsigned short uint16;
void vfnWhile(void);
void vfnTMR(void);
static uint16 u16Clk=32500;
static uint_8 Control=0;
uint16 u8Seg=0;	//Esta tal ves la borre
uint8  u8_20mS=0;
uint_32 u32Pin;
uint_32 u32Returnfun;
uint8 au8CountersValues[4];
uint8 *pu8Pointer=&au8CountersValues[0];
uint8 u8DsplyOn=1;//Esto tendra un nombre para hacer el siempre jarioso
//Hasta aqui

int main(void){
	GPIO_vfnDriverInit();
	GPIO_vfnLEDriverInit();

	while(1){
		vfnWhile();
		u8_20mS++;
		if(u8_20mS==8){
			u8_20mS=0;
			//De aqui esto yo lo pondria en una funcion en el debouncer para poder hacer el boton de pausa
			if(GPIOE->PDIR==(1<<Conf)||GPIOE->PDIR==(1<<Start)||GPIOE->PDIR==(1<<Left)||GPIOE->PDIR==(1<<Right)||GPIOE->PDIR==(1<<Down)||GPIOE->PDIR==(1<<Up)){
				u32Pin=GPIOE->PDIR;
				u32Returnfun=fnDbncr(u32Pin);
				if(u32Returnfun&(1<<Conf)){
					u8DsplyOn=1;
					uint8 *pu8Pointer=&au8CountersValues[0];
					Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
					if(u32Returnfun&(1<<Left)){
						Control++;
						if(u8DsplyOn==8){
							u8DsplyOn=1;
						}else{
							u8DsplyOn=u8DsplyOn<<1;
							pu8Pointer++;
						}
						Shift_vfnDecode(pu8Pointer,&u8DsplyOn); //esta funcion si va ir
					}
					else if(u32Returnfun&(1<<Right)){
						Control--;
						if(u8DsplyOn==8){
							u8DsplyOn=1;
						}else{
							u8DsplyOn=u8DsplyOn>>1;
							pu8Pointer--;
						}
						Shift_vfnDecode(pu8Pointer,&u8DsplyOn); //esta funcion si va ir
					}

					else if(u32Returnfun&(1<<Up)){
						au8CountersValues[Control]++;
						if(Control==1||Control==3){
							if(au8CountersValues[Control]>5){
								au8CountersValues[Control]=5;
							}
						}
						else if(au8CountersValues[Control]>9){
								au8CountersValues[Control]=9;
							}
						Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
						u32Returnfun&=~(1<<Up);
					}else if(u32Returnfun&(1<<Down)){
						au8CountersValues[Control]--;
						if(au8CountersValues[Control]<0){
							au8CountersValues[Control]=0;
							}
						Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
						u32Returnfun&=~(1<<Down);
					}
				}
				else if(u32Returnfun&(1<<Start)){
					vfnTMR();
				}
			}
		}
		else{
			if((u32Returnfun&(1<<Conf))==0){
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
			// Hasta aqui
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

