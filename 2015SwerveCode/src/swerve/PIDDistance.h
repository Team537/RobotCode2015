#ifndef PIDDISTANCE_H
#define PIDDISTANCE_H

#include <WPILib.h>
#include <Schematic.h>

class PIDDistance {
public:
	float P, I, D;

	/**
	 * PIDDistance Constructor. Needs to be given these arguments:
	 * (p, i, d)
	 */
	PIDDistance(float p, float i, float d) {
		P = p;
		I = i;
		D = d;
	}
};

#endif
