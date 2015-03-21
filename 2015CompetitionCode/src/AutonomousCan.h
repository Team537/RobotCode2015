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
		AutonomousCan()
	{
			Autotime = new Timer;
			Hoardtime = new Timer;
			Autostate = 0;
			count = 0;
			cannumber = 0;
	}
	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard);
private:

	Timer *Autotime;
	Timer *Hoardtime;
	int Autostate;
	int count;
	int cannumber;
	bool armout   = false;

};

#endif
