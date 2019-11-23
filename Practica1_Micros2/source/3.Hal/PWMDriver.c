/*
 * TPWDriver.c
 *
 *  Created on: 4 jul. 2019
 *      Author: lucky
 */


/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------PWM Functions-----------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

#include "MKL25Z4.h"
#include "PWMDriver.h"

static uint16_t u16ModVal=0;
uint16_t i=0;
uint_8 x=0;

void PWM_vfnDriverInit (void){
	//---PWM Initialization---
		SIM->SOPT2|=SIM_SOPT2_TPMSRC(1); 										//SELECT THE CLOCK
		SIM->SOPT2|=SIM_SOPT2_PLLFLLSEL(0);										//PLL OR FLL
		SIM->SCGC6|=SIM_SCGC6_TPM0_MASK;										//TPM0 activation
		TPM0->SC|=TPM_SC_PS(6);													//Division of CLK
		TPM0->SC|=TPM_SC_CMOD(1);												//CLK
		TPM0->SC|=TPM_SC_CPWMS(0);												//Up counting
		TPM0->MOD= 6562;
		TPM0->CONTROLS[0].CnSC|=TPM_CnSC_ELSB_MASK|TPM_CnSC_MSB_MASK;			//HIGH TRUE
		TPM0->CONF|=TPM_CONF_DBGMODE_MASK;										//Debug ON
		//---Initialization oPWM---
		SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;										//PortD Activation
		PORTD->PCR[0]|=PORT_PCR_MUX(4);
	}

void PWM_bAlarm (void){
		if(i<6561&&x==0){
			i++;
			if(i==6561){
				x=1;
			}
		}else if(i>40&&x==1){
			i--;
		}else{
			x=0;
		}
		TPM0->CONTROLS[0].CnV=i;
}

void PWM_bTimer (void){
	if(i<6561&&x==0){
				i++;
				TPM0->CONTROLS[0].CnV=40;
				if(i==6561){
					x=1;
				}
			}else if(i>40&&x==1){
				i--;
				TPM0->CONTROLS[0].CnV=6562;
			}else{
				x=0;
			}
	}



void PWM_bOff (void){

	TPM0->CONTROLS[0].CnV=0;
	i=0;
	x=0;

}

