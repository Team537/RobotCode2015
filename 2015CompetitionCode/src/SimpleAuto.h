#ifndef SIMPLEAUTO_H
#define SIMPLEAUTO_H

#include <WPILib.h>
#include "Schematic.h"
#include "swerve/Swerve.h"
#include "Collector.h"
#include "Stacker.h"
#include "Hoarder.h"
#include "AutoSelect.h"

class SimpleAutonomous : public AutoSelect{

private:
	Timer *Autotime;
	int SimpleAutoSwitch;

public:
	SimpleAutonomous ()
{
		Autotime = new Timer;
		SimpleAutoSwitch = 0;
}
	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
};

#endif
