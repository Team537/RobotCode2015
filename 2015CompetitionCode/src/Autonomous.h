#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include <WPILib.h>
#include "Schematic.h"
#include "Hoarder.h"

class Autonomous
{
	Hoarder hoarder;
private:
	int AutoState = 0;
	int count 	  = 0;
	bool armout   = false;
public:
	void Run();
};

#endif
