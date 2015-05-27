#ifndef DOUBLEPOT_H
#define DOUBLEPOT_H

#include <cmath>
#include <WPIlib.h>
#include <Schematic.h>

#define OVERSAMPLE 2

class DoublePot: public AnalogPotentiometer {
private:
	bool ALTERNATER, LASTDELTASIGN;
	double LASTVALUE;
	float MIN, MAX;
	int COUNTER;
	double ACCUM, OFFSET;
	std::string NAME;
	int OVERSAMPLEACC;
	double DATA[OVERSAMPLE];

public:
	explicit DoublePot(int channel, double fullrange, float min, float max, float offset, std::string name);
	double PIDGet();
	double GetAverage();
};

#endif
