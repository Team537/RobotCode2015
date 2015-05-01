#ifndef DOUBLEPOT_H
#define DOUBLEPOT_H

#include "Schematic.h"
#include "WPILib.h"

#define OVERSAMPLE 2

class DoublePot: public AnalogPotentiometer {
public:
	explicit DoublePot(int channel, double fullRange, double offset, float min, float max, float Offset, std::string name);
	double PIDGet();
	double getAverage();
	void addData(double);

private:
	bool alternater;
	bool lastdeltasign;
	double lastval;
	float Min;
	float Max;
	int counter;
	double accum;
	double OFFSet;
	std::string Name;
	int oversampleAcc;
	double data[OVERSAMPLE];
};

#endif
