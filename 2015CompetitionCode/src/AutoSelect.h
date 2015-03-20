#ifndef AUTOSELECT_H
#define AUTOSELECT_H

#include <WPILib.h>
#include "Schematic.h"
#include "swerve/Swerve.h"
#include "Collector.h"
#include "Stacker.h"
#include "Hoarder.h"

class AutoSelect {

public:
	virtual void Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard) = 0;
	virtual void Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard) = 0;
	virtual void End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard) = 0;
	virtual ~AutoSelect() {};

};
#endif
