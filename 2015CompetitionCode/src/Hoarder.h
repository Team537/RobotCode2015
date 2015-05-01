#ifndef HOARDER_H
#define HOARDER_H

#include "WPILib.h"
#include "Schematic.h"

class Hoarder {
public:
	Hoarder() {
		pistonextend = new Solenoid(HOARDER);
		lastpressed = 0;
	}

	void hoard(int btnhoard);
	void initialize();
	void Extend();
	void Retract();

private:
	Solenoid *pistonextend;
	bool lastpressed;
};

#endif
