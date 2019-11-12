
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "UART_DriverInt.h"




uint8 au8Pins2Use[Pins2Use]={enPin0,enPin1,enPin2,enPin3,enPin4};
uint8 StateMachineVal=0;

int main(void)
{

	UART0_vfnCallbackReg(UART0_Callback);
	GPIO_vfnDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));
	PWM_vfnDriverInit ();
	UART_DriverInt();


	while(1)
	{

	}

	return 0;
}
void UART0_Callback(uint_8 UARTVal)
{

}


