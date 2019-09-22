#include "Debouncer.h"
#include "MKL25Z4.h"

static uint_32 Stable_Value=0;
static uint_8 Cnt=0;
static uint_32 Shots_Value[3];
static uint_32 NewStable_Val=0;

uint_32 fnDbncr(uint_32 Value){
	Shots_Value[Cnt]=Value;
	if(Shots_Value[Cnt]!=Stable_Value){
		Cnt++;
		if(Shots_Value[0]==Shots_Value[2]){
			Stable_Value=Shots_Value[2];
			Cnt=0;
		}
	}
	else{
		Cnt=0;
	}
if(Stable_Value==(1<<Up)||Stable_Value==(1<<Down)||Stable_Value==(1<<Left)||Stable_Value==(1<<Right)||Stable_Value==(1<<Conf)||Stable_Value==(1<<Start)){
	NewStable_Val|=Stable_Value;
	Stable_Value=0;
}else if(Stable_Value==Start){
	NewStable_Val=Stable_Value;
}
	return NewStable_Val;
}





