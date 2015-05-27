#ifndef PIDDRIVEVALUE_H
#define PIDDRIVEVALUE_H

#include <WPILib.h>
#include <Schematic.h>

class PIDDriveValue {
public:
	float P, I, D, F, RATE;

	/**
	 * PIDDriveValue Constructor. Needs to be given these arguments:
	 * (p, i, d, f, rate)
	 */
	PIDDriveValue(float p, float i, float d, float f, float rate) {
		P = p;
		I = i;
		D = d;
		F = f;
		RATE = rate;
	}
};

#endif
