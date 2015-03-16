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

}
	void Run();
private:
	int AutoState = 0;

};

#endif
