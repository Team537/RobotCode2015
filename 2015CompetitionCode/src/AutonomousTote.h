#ifndef AUTONOMOUSTOTE_H
#define AUTONOMOUSTOTE_H

#include <WPILib.h>
#include "Schematic.h"
#include "Stacker.h"
#include "Collector.h"
#include "swerve/Swerve.h"
#include "Hoarder.h"
#include "AutoSelect.h"

class AutonomousTote : public AutoSelect {

public:
	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
private:
	Timer *Autotime;
	int AutoState = 0;
	int repetition = 0;

};

#endif
