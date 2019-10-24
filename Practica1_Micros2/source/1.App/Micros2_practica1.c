
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "GearBox.h"
#include "PWMDriver.h"
#include "Timer.h"
#include "UART_DriverInt.h"


static uint16 u16Clk=ClkVal;
uint16 u8Seg=0;
uint8  u8_20mS=0;
uint8 au8Pins2Use[Pins2Use]={enPin0,enPin1,enPin2,enPin3,enPin4};
uint8 StateMachineVal=0;
static uint8 Aux=0;
uint8 fullbrake=0;
uint8 acc=0;
uint8 brake=0;

int main(void){

	UART0_vfnCallbackReg(UART0_Callback);
	GPIO_vfnDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));
	PWM_vfnDriverInit ();
	//PWM_vfnDriverInitServo();
	Gear_InitSt();
	UART_DriverInt();


	while(1){
		if(acc==1&&u8Seg==16){
			onlyacc();
		}
		if(brake==1&&u8Seg==16){
			Gear_vfnBrake();
		}
		if(fullbrake){
			Stopmotor();
		}
		vfnWhile();
		u8Seg++;
		u8_20mS++;
		if(acc==0&&brake==0){
		if (StateMachineVal==idle){
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				Gear_vfCheckBttns4Parking();
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Off){
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				/*Apagar y checar, creo*/
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Drive){
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				Gear_vfCheckBttns4Drive();
			}
		}
		else if(StateMachineVal==Reverse){
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				Gear_vfCheckBttns4Drive();
				/*Checar Pines*/
			}
		}
		}
		if(u8Seg==160){
			u8Seg=0;
		}
		Timer_vfnIdle();
	}

	return 0;
}
void UART0_Callback(uint_8 UARTVal){
	if(Aux==0){
		if(UARTVal==Gobernar){
			//Setacc
			uint8 print[29]=Ingrese;
			for(int i=0;i<29;i++){
				while(UART_bfnSend(print[i])==ERROR){

				}

			}
			Aux=1;
		}
		else if(UARTVal==MostrarVel){
			//sendvel
			printvel();
		}
		else if(UARTVal==ModoLibreIn){
			//Wait w or s to move
			Aux=2;
		}
	}else if(Aux==1){
		//Wait 3 numbers to set
		if(Setvel(UARTVal)==SUCCESS){
			Aux=0;
		}
	}
	else if(Aux==2){
		if(UARTVal==UpVel){
			//up acc
			acc=1;
			brake=0;
				}
		else if(UARTVal==DownVel){
			//down acc
			acc=0;
			brake=1;
		}else if(UARTVal==ModoLibreOut){
			//stop motor
			fullbrake=1;
			Stopmotor();
		}
		else if(UARTVal==MostrarVel){
					//sendvel
			printvel();
		}

	}
}


void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=ClkVal;
}

void vfnDriveState(void){
	GPIO_vfnDrive();
	StateMachineVal=Drive;
}

void vfnParkState(void){
	StateMachineVal=idle;
}

void vfnReverseState(void){
	GPIO_vfnReverse();
	StateMachineVal=Reverse;
}

void Stopmotor(void){
	if(check()==1){
				acc=0;
				brake=0;
				Aux=0;
				u8_20mS=0;
				u8Seg=0;
				fullbrake=0;
				}else{
					Gear_vfnBrake();
					brake=1;
					acc=0;
				}
}

