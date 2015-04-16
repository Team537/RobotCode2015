#ifndef NOAUTO_H
#define NOAUTO_H

#include <WPILib.h>
#include "Schematic.h"
#include "swerve/Swerve.h"
#include "Collector.h"
#include "Stacker.h"
#include "Hoarder.h"
#include "AutoSelect.h"

class NoAutonomous : public AutoSelect{


public:
	NoAutonomous(){
		GyroOffset = 0;
		}
	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);

private:
	float GyroOffset;
};

#endif
