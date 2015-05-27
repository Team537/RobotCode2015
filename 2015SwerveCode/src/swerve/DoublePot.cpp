#include <swerve/DoublePot.h>

// Might need another offset value for AnalogPotentiometer to use.
DoublePot::DoublePot(int channel, double fullrange, float min, float max, float offset, std::string name) : AnalogPotentiometer(channel, fullrange, offset) {
	ALTERNATER = false;
	LASTDELTASIGN = false;
	LASTVALUE = 0;
	MIN = min;
	MAX = max;
	COUNTER = 0;
	ACCUM = 0;
	OFFSET = offset;
	NAME = name;
	OVERSAMPLEACC = 0;

	for (int i = 0; i < OVERSAMPLE; i++) {
		DATA[i] = 0;
	}
};

double DoublePot::PIDGet() {
	double OriginalReading = AnalogPotentiometer::PIDGet();
	double Delta = OriginalReading - LASTVALUE;
	//bool DeltaIsPositive = Delta > 0;
	double Range = MAX - MIN;
	//double TempIntPart, TempAccum;
	double Sum = 0;

	if (Delta > 300) { // Makes sure that when looping past reset point it doesn't go backwards.
		//return lastval;
		OriginalReading = LASTVALUE;
	}

	LASTVALUE = OriginalReading;
	OriginalReading += OFFSET;

	if (OriginalReading > MAX) {
		OriginalReading -= Range;
	}

	if (OriginalReading < MIN) {
		OriginalReading += Range;
	}

	for (int i = OVERSAMPLE - 1; i > 0; i--) {
		// Insert oversample code.
		DATA[i - 1] = DATA[i];
	}

	DATA[OVERSAMPLE - 1] = OriginalReading;
	OVERSAMPLEACC++;

	char Buff[1024];
	char Temp[32];
	sprintf(Buff, "Oversample");

	if (OVERSAMPLEACC >= OVERSAMPLE) {
		for (int i = 0; i < OVERSAMPLE; i++) {
			Sum += DATA[i];
			sprintf(Temp, "[%i]=%f,", i, DATA[i]);
			strcat(Buff, Temp);
		}

		SmartDashboard::PutString(NAME + "Oversample", Buff);

		return (Sum / OVERSAMPLE);
	}

	return OriginalReading;

	SmartDashboard::PutBoolean("Alternater", ALTERNATER);
	SmartDashboard::PutNumber("Original Reading", OriginalReading);
	SmartDashboard::PutNumber("Accumulator", ACCUM);

	/*// Update the accumulator with the current change in angle.
	 ACCUM += Delta;

	 // If we've seen a big jump in angle (half range or more) adjust the accumulator for the sawtooth step.
	 if(fabs(Delta) > Range / 2) {
	 	 if (DeltaIsPositive) {
		 	 ACCUM -= Range;
	 	 } else {
		 	 ACCUM += Range;
		 }
	 }
	 
	 LASTDELTASIGN = DeltaIsPositive;
	 LASTVALUE = OriginalReading;

	 // At this point the accumulator could be a very large absolute value use a modulus operation to get back to the expected range of values
	 // Note that we divide by (range * 2) to compensate for 2:1 pot to motor ratio then we multiply the fractional part by the range to get back to the expected range of values.
	 TempAccum = modf(ACCUM / (Range * 2), & TempIntPart) * Range;

	 // We want to always return positive values, so if we're currently negative, add the range value to the output value before returning.
	 if (TempAccum < 0) {
		 TempAccum += Range;

		 // Should these steps be in this if?
		 TempAccum += MIN;
		 TempAccum -= OFFSET;
	 }

	 if (TempAccum < MIN) {
		 TempAccum += Range;
	 }

	 return(TempAccum);*/
}

double DoublePot::GetAverage() {
	double sum = 0;

	for (int i = 0; i < OVERSAMPLE; i++) {
		sum += DATA[i];
	}

	return (sum / OVERSAMPLE);
}
