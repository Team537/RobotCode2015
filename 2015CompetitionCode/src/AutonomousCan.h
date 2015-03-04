#ifndef AUTONOMOUSCAN_H
#define AUTONOMOUSCAN_H

#include <WPILib.h>
#include "Schematic.h"
#include "Hoarder.h"
#include "swerve/Swerve.h"

class AutonomousCan
{
	AutonomousCan(){
		hoarder = new Hoarder();
		Drive = new Swerve(0);

	}
	Hoarder *hoarder;
	Swerve *Drive;
private:
	int AutoState = 0;
	int count 	  = 0;
	bool armout   = false;
public:
	void Run();
};

#endif
