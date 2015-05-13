#ifndef PIDDRIVEVALUE_H
#define PIDDRIVEVALUE_H

#include <Schematic.h>
#include "WPILib.h"

class PIDDriveValue {
private:

public:
	PIDDriveValue(float p, float i, float d, float f, float rate) {
		P = p;
		I = i;
		D = d;
		F = f;
		Rate = rate;
	}

	float P;
	float I;
	float D;
	float F;
	float Rate;
};

#endif
