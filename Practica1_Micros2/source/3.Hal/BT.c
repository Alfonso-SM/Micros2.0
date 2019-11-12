/*
 * BT.c
 *
 *  Created on: 02/08/2019
 *      Author: Poncho
 */
#include "BT.h"
#include "UART_DriverInt.h"
void fnCheck(void){
	unsigned char bpAt[3];
			unsigned char u=0;        //AT
				while(u<4){
				    	if(u==0){bpAt[u]='A';}
				    	else if(u==1){bpAt[u]='T';}
				     	else if(u==2){bpAt[u]='\r';}
				    	else if(u==3){bpAt[u]='\n';}
				    	UART_bfnSend (bpAt[u]);
				    	u++;
				    	}
}
void fnName_BT(void){
unsigned char bpAt[13];
unsigned char u=0;
	while(u<13){
	    	if(u==0){bpAt[u]='A';}
	    	else if(u==1){bpAt[u]='T';}
	    	else if(u==2){bpAt[u]='+';}
	    	else if(u==3){bpAt[u]='N';}
	    	else if(u==4){bpAt[u]='A';}
	    	else if(u==5){bpAt[u]='M';}
	    	else if(u==6){bpAt[u]='E';}
	    	else if(u==7){bpAt[u]='=';}
	    	else if(u==8){bpAt[u]='B';}
	    	else if(u==9){bpAt[u]='T';}
	    	else if(u==10){bpAt[u]='4';}
	    	else if(u==11){bpAt[u]='\r';}
	    	else if(u==12){bpAt[u]='\n';}
	    	UART_bfnSend (bpAt[u]);
	    	u++;
	    	}
}
void fnPswd_BT(void){
	unsigned char bpAt[11];
	unsigned char u=0;
		while(u<11){
		    	if(u==0){bpAt[u]='A';}
		    	else if(u==1){bpAt[u]='T';}
		    	else if(u==2){bpAt[u]='+';}
		    	else if(u==3){bpAt[u]='P';}
		    	else if(u==4){bpAt[u]='S';}
		    	else if(u==5){bpAt[u]='W';}
		    	else if(u==6){bpAt[u]='D';}
		    	else if(u==7){bpAt[u]='=';}
		    	else if(u==8){bpAt[u]='0';}
		    	else if(u==9){bpAt[u]='\r';}
		    	else if(u==10){bpAt[u]='\n';}
		    	UART_bfnSend (bpAt[u]);
		    	u++;
		    	}
}
void fnAskAddress_BT(void){
	unsigned char bpAt[10];
		unsigned char j=0;        //AT+ADDR?
			while(j<10){
			    	if(j==0){bpAt[j]='A';}
			    	else if(j==1){bpAt[j]='T';}
			    	else if(j==2){bpAt[j]='+';}
			    	else if(j==3){bpAt[j]='A';}
			    	else if(j==4){bpAt[j]='D';}
			    	else if(j==5){bpAt[j]='D';}
			    	else if(j==6){bpAt[j]='R';}
			    	else if(j==7){bpAt[j]='?';}
			    	else if(j==8){bpAt[j]='\r';}
			    	else if(j==9){bpAt[j]='\n';}
			    	UART_bfnSend (bpAt[j]);
			    	j++;
			    	}

}
void fnMaster_BT(void){
	unsigned char bpAt[11];
		unsigned char a=0;    //AT+ROLE=   esclavo=0 maestro=1
			while(a<11){
			    	if(a==0){bpAt[a]='A';}
			    	else if(a==1){bpAt[a]='T';}
			    	else if(a==2){bpAt[a]='+';}
			    	else if(a==3){bpAt[a]='R';}
			    	else if(a==4){bpAt[a]='O';}
			    	else if(a==5){bpAt[a]='L';}
			    	else if(a==6){bpAt[a]='E';}
			    	else if(a==7){bpAt[a]='=';}
			    	else if(a==8){bpAt[a]='1';}
			    	else if(a==9){bpAt[a]='\r';}
			    	else if(a==10){bpAt[a]='\n';}
			    	UART_bfnSend (bpAt[a]);
			    	a++;
			    	}
}
void fnMode_BT(void){
	unsigned char bpAt[12];
			unsigned char u=0;    //AT+CMODE=  libre=1 especifico=0
				while(u<12){
				    	if(u==0){bpAt[u]='A';}
				    	else if(u==1){bpAt[u]='T';}
				    	else if(u==2){bpAt[u]='+';}
				    	else if(u==3){bpAt[u]='C';}
				    	else if(u==4){bpAt[u]='M';}
				    	else if(u==5){bpAt[u]='O';}
				    	else if(u==6){bpAt[u]='D';}
				    	else if(u==7){bpAt[u]='E';}
				    	else if(u==8){bpAt[u]='=';}
				    	else if(u==9){bpAt[u]='0';}
				    	else if(u==10){bpAt[u]='\r';}
				    	else if(u==11){bpAt[u]='\n';}
				    	UART_bfnSend (bpAt[u]);
				    	u++;
				    	}
}
void fnAddress_BT(void){
	unsigned char bpAt[20];
				unsigned char u=0;    //AT+BIND=<Address>
					while(u<20){
					    	if(u==0){bpAt[u]='A';}
					    	else if(u==1){bpAt[u]='T';}
					    	else if(u==2){bpAt[u]='+';}
					    	else if(u==3){bpAt[u]='B';}
					    	else if(u==4){bpAt[u]='I';}
					    	else if(u==5){bpAt[u]='N';}
					    	else if(u==6){bpAt[u]='D';}
					    	else if(u==7){bpAt[u]='=';}
					    	else if(u==8){bpAt[u]='1';}
					    	else if(u==9){bpAt[u]='3';}
					    	else if(u==10){bpAt[u]='E';}
					    	else if(u==11){bpAt[u]='F';}
					    	else if(u==12){bpAt[u]=',';}
					    	else if(u==13){bpAt[u]='D';}
					    	else if(u==14){bpAt[u]='D';}
					    	else if(u==15){bpAt[u]=',';}
					    	else if(u==16){bpAt[u]='6';}
					    	else if(u==17){bpAt[u]='9';}
					    	else if(u==18){bpAt[u]='\r';}
					    	else if(u==19){bpAt[u]='\n';}
					    	UART_bfnSend (bpAt[u]);
					    	u++;
					    	}

}
