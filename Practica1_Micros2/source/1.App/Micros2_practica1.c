
#include "MKL25Z4.h"
#include "GPIODriver.h"
#include "ShiftDriver.h"
//Esto se va a comodar despues
typedef unsigned short uint16;
void vfnWhile(void);
static uint16 u16Clk=32500;
uint16 u8Seg=0;	//Esta tal ves la borre
uint8 au8CountersValues[4];
uint8 *pu8Pointer=&au8CountersValues[0];
uint8 borrar=8; //Esto sera un arreglo de 4
uint8 u8DsplyOn=1;//Esto tendra un nombre para hacer el siempre jarioso
//Hasta aqui

int main(void){
	GPIO_vfnDriverInit();
	GPIO_vfnLEDriverInit();

	while(1){
		vfnWhile();
		u8Seg++;
		if(u8Seg==400){
			u8Seg=0;
			GPIO_vfnToggleLEd();
			au8CountersValues[0]++;
			//Esto es de prueba

			if(au8CountersValues[0]>9){
				au8CountersValues[0]=0;
				au8CountersValues[1]++;
			}
			else if(au8CountersValues[1]>5){
				au8CountersValues[1]=0;
				au8CountersValues[2]++;
			}
			else if(au8CountersValues[2]>9){
				au8CountersValues[2]=0;
				au8CountersValues[3]++;
			}
			else if(au8CountersValues[3]>5){
				au8CountersValues[3]=0;
			}
			//Hasta aqui
			//Lo que tenga que hacer cuando se logre 1s.
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
	return 0;
}

void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=4062; //32500 será una macro
}
