//Define header file
#ifndef HOARDER_H
#define HOARDER_H

//Dependencies
#include "WPILib.h"

//Hoarder class constructor
class Hoarder {

public: //Used in all classes
	Hoarder()
{
		pistonextend = new Solenoid(3);
		pistonretract = new Solenoid(4);
		lastpressed = 0;
}
	//Declare functions
	void hoard(int btnhoard);
	void initialize();

private: //Only used in this class

	//Declare variables
	Solenoid *pistonextend;
	Solenoid *pistonretract;
	bool lastpressed;

};

#endif
