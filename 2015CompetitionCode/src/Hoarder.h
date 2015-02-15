//Define header file
#ifndef HOARDER_H
#define HOARDER_H

//Dependencies
#include "WPILib.h"
#include "Schematic.h"

//Hoarder class constructor
class Hoarder {

public: //Used in all classes
	Hoarder()
{
		pistonextend = new Solenoid(HOARDER);
		lastpressed = 0;
}
	//Declare functions
	void hoard(int btnhoard);
	void initialize();

private: //Only used in this class

	//Declare variables
	Solenoid *pistonextend;
	bool lastpressed;

};

#endif
