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
		if(Shots_Value[1]==Shots_Value[2]){
			Stable_Value=Shots_Value[2];
			Cnt=0;
		}
	}
	else{
		Cnt=0;
	}
if(Stable_Value==(Up|Down|Left|Right|Conf)){
	NewStable_Val+=Stable_Value;
}else if(Stable_Value==Start){
	NewStable_Val=Stable_Value;
}
	return NewStable_Val;
}





