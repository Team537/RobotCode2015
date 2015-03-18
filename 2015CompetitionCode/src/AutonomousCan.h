#ifndef AUTONOMOUSCAN_H
#define AUTONOMOUSCAN_H

#include <WPILib.h>
#include "Schematic.h"
#include "Hoarder.h"
#include "swerve/Swerve.h"

class AutonomousCan
{
	public:

	AutonomousCan(Hoarder * Hoard, Swerve *Swerve){
		hoarder =  Hoard;
		Drive =  Swerve;
		Autotime = new Timer;

	}
	void Run(int cannumber);
private:
	Hoarder *hoarder;
	Swerve *Drive;
	Timer *Autotime;
	int Autostate = 0;
	int count 	  = 0;
	bool armout   = false;

};

#endif
