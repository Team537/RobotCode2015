#ifndef PIDVALUE_H
#define PIDVALUE_H

#include "schematic.h"
#include "wpilib.h"

class PIDValue
{
private:
	
	
public:
	PIDValue(float p,float i, float d, float mininput, float maxinput, float minoutput, float maxoutput){
		P = p;
		I = i;
		D = d;
		MINInput = mininput;
		MAXInput = maxinput;
		MINOutput = minoutput;
		MaxOutput = maxoutput;
		
	}

	float P;
	float I;
	float D;
	float MINInput;
	float MAXInput;
	float MINOutput;
	float MaxOutput;
};

#endif
