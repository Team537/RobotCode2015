#ifndef PIDDISTANCE_H
#define PIDDISTANCE_H

#include "schematic.h"
#include "wpilib.h"

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
