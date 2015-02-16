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


	Timer Clock;

public: //Used in all classes

	Stacker()


{
		 Flaps = new Relay(STACKER_FLAPS, Relay::Direction::kForwardOnly);
		 LiftRight = new Victor (STACKER_LIFT_RIGHT);
		 LiftLeft = new Victor (STACKER_LIFT_LEFT);
		 Extend = new Talon (STACKER_EXTEND);
		 SwitchIn = new DigitalInput(STACKER_IN_SWITCH);
		 SwitchOut = new DigitalInput(STACKER_OUT_SWITCH);
		 LiftPotRight = new AnalogInput(STACKER_LIFT_POT_RIGHT);
		 LiftPotLeft = new AnalogInput(STACKER_LIFT_POT_LEFT);
		elevatorrampspeed           = 0.1;
		extendrampspeed				= 0.1;
		lastreleasedpressed = 0;
		deadband            = 0.1;
		AutoLiftPIDRight->SetAbsoluteTolerance(20);
		AutoLiftPIDRight->SetOutputRange(1,360);
		AutoLiftPIDRight = new PIDController(.04, 0.01, 0.01, LiftPotRight, LiftRight);
		AutoLiftPIDLeft->SetAbsoluteTolerance(20);
		AutoLiftPIDLeft->SetOutputRange(1,360);
		AutoLiftPIDLeft = new PIDController(.04, 0.01, 0.01, LiftPotLeft, LiftLeft);
		oldelevatorspd = 0;
		oldextendspeed = 0;
		// Give this a value
		setpoint = 0;
		//
		rightcurrentlevel = 0;
		leftcurrentlevel = 0;
		righttargetlevel = 0;
		lefttargetlevel = 0;
		rightelevatormax = 900;
		leftelevatormax = 900;
		rightelevatormin = 15;
		leftelevatormin = 15;
		lastpov = -1;
}
	//Declare master function
	void Run(bool btngrab, bool autobtn, float pov, int up, int down, int extend, int retract);

private: //Only used in this class

	//Declare variables
	bool   lastreleasedpressed;
	float oldelevatorspd, oldextendspeed;
	float elevatorrampspeed, extendrampspeed,deadband;
	float setpoint;
	int state = 0;
	float rightcurrentlevel, leftcurrentlevel;
	float righttargetlevel, lefttargetlevel;
	float rightelevatormax, leftelevatormax;
	float rightelevatormin, leftelevatormin;
	float lastpov;

	//Declare functions
	void Grab(bool button);
	void AutoStacker(bool autobtn, float pov);
	void ManualStacker(int up, int down);
	void Extender(int extend, int retract);
	Relay* Flaps;
	Victor*   LiftRight, *LiftLeft;
	Talon*   Extend;
	DigitalInput* SwitchIn;
	DigitalInput* SwitchOut;
	AnalogInput* LiftPotRight, *LiftPotLeft;
	PIDController* AutoLiftPIDRight, *AutoLiftPIDLeft;

};

#endif
