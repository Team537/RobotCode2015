#ifndef WHIPAUTO_H
#define WHIPAUTO_H

#include <WPILib.h>
#include "Schematic.h"
#include "Hoarder.h"
#include "Stacker.h"
#include "Collector.h"
#include "swerve/Swerve.h"
#include "Whips.h"

#include "AutoSelect.h"

class WhipAuto : public AutoSelect
{
	public:
		WhipAuto(Whips *Burgerler)
	{
			CanStealer = Burgerler;
			Deployed = 85;
			EngageDriveTrain = 20;
			Stowed = 0;
			AutoState = 0;
			AutoTimer = new Timer();
	}
		void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
		void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);
		void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro);

	private:
		Timer *AutoTimer;
		Whips *CanStealer;
		int AutoState;
		double Deployed;
		double EngageDriveTrain;
		double Stowed;
};
#endif
