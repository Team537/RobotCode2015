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

	void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard);
	void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard);
	void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard);
private:

	Timer *Autotime;
	int Autostate = 0;
	int count 	  = 0;
	int cannumber;
	bool armout   = false;

};

#endif
