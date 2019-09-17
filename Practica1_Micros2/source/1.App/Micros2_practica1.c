
#include "MKL25Z4.h"
#include "GPIODriver.h"
//Esto se va a comodar despues
typedef unsigned short uint16;
void vfnWhile(void);
static uint16 u16Clk=32500;
uint8 u8Seg=0;
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
			//Lo que tenga que hacer cuando se logre 1s.
		}
		else{
			//Lo que tiene que checar cada 20ms.
		}
	}
	return 0;
}

void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=32500;
}
