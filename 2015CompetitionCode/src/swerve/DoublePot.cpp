#include "DoublePot.h"
#include "WPILib.h"
#include "cmath"

DoublePot::DoublePot(int channel, double fullRange, double offset, float min, float max, float Offset, std::string name) : AnalogPotentiometer(channel, fullRange, offset) {
	Min = min;
	Max = max;
	OFFSet = Offset;
	counter = 0;
	lastval = 0;
	lastdeltasign = false;
	accum = 0;
	alternater = false;
	oversampleAcc = 0;
	Name = name;

	for (int i = 0; i < OVERSAMPLE; i++) {
		data[i] = 0;
	}
};

double DoublePot::PIDGet() {
	double originalreading = AnalogPotentiometer::PIDGet();
	double delta = originalreading - lastval;
	double range = Max - Min;
	double tmpIntPart, tmpAccum;
	bool deltaIsPositive = delta > 0;
	double sum = 0;

	if (delta > 300) { // Makes sure that when looping past reset point it doesn't go backwards.
		// return lastval;
		originalreading = lastval;
	}

	lastval = originalreading;
	originalreading += OFFSet;

	if (originalreading > Max) {
		originalreading -= range;
	}

	if (originalreading < Min) {
		originalreading += range;
	}

	// Insert oversample code
	for (int i = OVERSAMPLE - 1; i > 0; i--) {
		data[i - 1] = data[i];
	}

	data[OVERSAMPLE - 1] = originalreading;
	oversampleAcc++;
	char buff[1024];
	char temp[32];
	sprintf(buff, "Oversample");

	if (oversampleAcc >= OVERSAMPLE) {
		for (int i = 0; i < OVERSAMPLE; i++) {
			sum += data[i];
			sprintf(temp, "[%i]=%f,", i, data[i]);
			strcat(buff, temp);
		}

		SmartDashboard::PutString(Name + "Oversample", buff);

		return sum / OVERSAMPLE;
	}

	return originalreading;

	SmartDashboard::PutBoolean("Alternater", alternater);
	SmartDashboard::PutNumber("originalreading", originalreading);
	SmartDashboard::PutNumber("accum", accum);

	// Update the accumulator with the current change in angle.
	//accum += delta;

	// If we've seen a big jump in angle (half range or more) adjust the accumulator for the sawtooth step.
	/*if(fabs(delta) > range/2) {
		 if (deltaIsPositive) {
			 accum -= range;
		 } else {
			 accum += range;
		 }
	 }
	 
	 lastdeltasign = deltaIsPositive;
	 lastval = originalreading;*/

	// At this point the accumulator could be a very large absolute value use a modulus operation to get back to the expected range of values
	// Note that we divide by (range*2) to compensate for 2:1 pot to motor ratio then we multiply the fractional part by the range to get back to the expected range of values.
	//tmpAccum = modf(accum/(range*2), &tmpIntPart) * range;
	// We want to always return positive values, so if we're currently negative, add the range value to the output value before returning.
	/* if (tmpAccum < 0)
	 tmpAccum += range;
	 tmpAccum += Min;
	 tmpAccum -= OFFSet;
	 if (tmpAccum < Min)
	 tmpAccum +=range;

	 return(tmpAccum);*/
}

double DoublePot::getAverage() {
	double sum = 0;

	for (int i = 0; i < OVERSAMPLE; i++) {
		sum += data[i];
	}

	return sum / OVERSAMPLE;
}
