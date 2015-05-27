#ifndef PIDVALUE_H
#define PIDVALUE_H

#include <WPILib.h>
#include <Schematic.h>

class PIDValue {
public:
	float P, I, D, MININPUT, MAXINPUT, MINOUTPUT, MaxOUTPUT;

	/**
	 * PIDValue Constructor. Needs to be given these arguments:
	 * (p, i, d, mininput, maxinput, minoutput, maxoutput)
	 */
	PIDValue(float p, float i, float d, float mininput, float maxinput, float minoutput, float maxoutput) {
		P = p;
		I = i;
		D = d;
		MININPUT = mininput;
		MAXINPUT = maxinput;
		MINOUTPUT = minoutput;
		MaxOUTPUT = maxoutput;
	}
};

#endif
