#ifndef SIMPLEAUTO_H
#define SIMPLEAUTO_H

#include <WPILib.h>
#include "Schematic.h"
#include "swerve/Swerve.h"

class SimpleAutonomous{

private:
	Swerve *DriveTrain;
	Timer *Autotime;
	int SimpleAutoSwitch;

public:

	SimpleAutonomous (Swerve *SwerveDrive)
{
		DriveTrain = SwerveDrive;
		SimpleAutoSwitch = 0;
		Autotime = new Timer;

}
	void Run();
};

#endif
