#ifndef AUTONOMOUSCAN_H
#define AUTONOMOUSCAN_H

#include <WPILib.h>
#include "Schematic.h"
#include "Hoarder.h"
#include "Stacker.h"
#include "Collector.h"
#include "swerve/Swerve.h"

#include "AutoSelect.h"

class AutonomousCan : public AutoSelect
{
	public:
		AutonomousCan(int can)
	{
			Autotime = new Timer;
			Hoardtime = new Timer;
			Autostate = 0;
			count = 0;
			cannumber = can;
			GyroOffset = 0;
	}
	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
private:

	Timer *Autotime;
	Timer *Hoardtime;
	int Autostate;
	int count;
	int cannumber;
	bool armout   = false;
	float GyroOffset;

};

#endif
