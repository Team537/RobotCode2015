//Define the header file
#ifndef STACKER_H
#define STACKER_H

//Dependencies
#include <WPILib.h>
#include "Schematic.h"
#include "cmath"


//Stacker class constructor
class Stacker
{
	Solenoid* Flaps;
	Victor*   Lift;
	Victor*   Extend;
	DigitalInput* SwitchIn;
	DigitalInput* SwitchOut;
	AnalogInput* LiftPot;
	PIDController* AutoLiftPID;
	Timer Clock;

public: //Used in all classes

	Stacker():
		Flaps(STACKER_FLAPS),
		Lift (STACKER_LIFT),
		Extend(STACKER_EXTEND),
		SwitchIn(STACKER_IN_SWITCH),
		SwitchOut(STACKER_OUT_SWITCH),
		LiftPot(STACKER_LIFT_POT)

{
		elevatorrampspeed           = 0.1;
		extendrampspeed				= 0.1;
		lastreleasedpressed = 0;
		deadband            = 0.1;
		AutoLiftPID->SetAbsoluteTolerance(20);
		AutoLiftPID->SetOutputRange(1,360);
		AutoLiftPID = new PIDController(.04, 0.01, 0.01, LiftPot, Lift);
		oldelevatorspd = 0;
		oldextendspeed = 0;
}
	//Declare master function
	void Run(bool btngrab, bool autobtn, float leftjoy, float rightjoy);

private: //Only used in this class

	//Declare variables
	bool   lastreleasedpressed;
	float oldelevatorspd, oldextendspeed;
	float elevatorrampspeed, extendrampspeed,deadband;
	int state = 0;

	//Declare functions
	void Grab(bool button);
	void AutoStacker(bool autobtn);
	void ManualStacker(float rightjoy);
	void Extender(int extend, int retract);

};

#endif
