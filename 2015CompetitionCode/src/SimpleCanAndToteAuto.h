#ifndef SIMPLECANANDTOTEAUTO_H
#define SIMPLECANANDTOTEAUTO_H

#include <WPILib.h>
#include "Schematic.h"
#include "Stacker.h"
#include "swerve/Swerve.h"

class SimpleCanAndToteAutonomous{

private:
	Swerve *DriveTrain;
	Stacker *Elevator;
	Timer *Autotime;
	int SimpleAutoSwitch;

public:

	SimpleCanAndToteAutonomous (Swerve *SwerveDrive, Stacker *Stack)
{
		DriveTrain = SwerveDrive;
		Elevator = Stack;
		SimpleAutoSwitch = 0;
		Autotime = new Timer;

}
	void Run();
};

#endif
