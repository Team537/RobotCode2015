#ifndef PIDDISTANCE_H
#define PIDDISTANCE_H

#include <Schematic.h>
#include "WPILib.h"

class PIDDistance {
private:

public:
	PIDDistance(float p, float i, float d) {
		P = p;
		I = i;
		D = d;
	}

	float P;
	float I;
	float D;
};

#endif
