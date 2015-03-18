#ifndef AUTONOMOUSTOTE_H
#define AUTONOMOUSTOTE_H

#include <WPILib.h>
#include "Schematic.h"
#include "Stacker.h"
#include "Collector.h"
#include "swerve/Swerve.h"

class AutonomousTote{

public:
	AutonomousTote(Swerve *Swerve, Collector *Grabber, Stacker *Elevator)
{
		DriveTrain = Swerve;
		Collect = Grabber;
		Stack = Elevator;
		repetition = 0;
		Autotime = new Timer;
}
	void ToteRun();
private:
	Swerve *DriveTrain;
	Collector *Collect;
	Stacker *Stack;
	Timer *Autotime;
	int AutoState = 0;
	int repetition;

};

#endif
