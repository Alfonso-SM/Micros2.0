
#include "MKL25Z4.h"
#include "GPIODriver.h"
#include "ShiftDriver.h"
//Esto se va a comodar despues
typedef unsigned short uint16;
void vfnWhile(void);
static uint16 u16Clk=32500;
uint8 u8Seg=0;	//Esta tal ves la borre
uint8 borrar=8; //Esto sera un arreglo de 4
uint8 borrar2=2;//Esto tendra un nombre para hacer el siempre jarioso
//Hasta aqui

int main(void){
	GPIO_vfnDriverInit();
	GPIO_vfnLEDriverInit();

	while(1){
		vfnWhile();
		u8Seg++;
		if(u8Seg==50){
			u8Seg=0;
			GPIO_vfnToggleLEd();
			//Esto es de prueba
			borrar++;
			if(borrar==10){
				borrar=0;
			}
			//Hasta aqui
			//Lo que tenga que hacer cuando se logre 1s.
		}
		else{
			//Lo que tiene que checar cada 20ms.
			Shift_vfnDecode(&borrar,&borrar2); //esta funcion si va ir
		}
	}
	return 0;
}

void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=32500; //32500 será una macro
}
