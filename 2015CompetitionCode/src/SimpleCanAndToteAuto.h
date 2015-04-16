#ifndef SIMPLECANANDTOTEAUTO_H
#define SIMPLECANANDTOTEAUTO_H

#include <WPILib.h>
#include "Schematic.h"
#include "Stacker.h"
#include "swerve/Swerve.h"
#include "Hoarder.h"
#include "AutoSelect.h"


class SimpleCanAndToteAutonomous : public AutoSelect{

private:
	Timer *Autotime;
	int SimpleAutoSwitch;

public:

	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
};

#endif
