#ifndef AUTONOMOUSTOTE_H
#define AUTONOMOUSTOTE_h

#include <WPILib.h>
#include "Schematic.h"
#include "Stacker.h"
#include "swerve/Swerve.h"

class AutonomousTote{

public:
	AutonomousTote()
{
	Drive = new Swerve(0);
	Stack = new Stacker();
}
	Swerve *Drive;
	Stacker *Stack;
	void Run();
private:
	int AutoState = 0;

};

#endif
