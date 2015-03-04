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
		ExtendLeft = new Talon (STACKER_EXTEND_LEFT);
		ExtendRight = new Talon (STACKER_EXTEND_RIGHT);
		Switch = new DigitalInput(STACKER_SWITCH);

		LiftPotRight = new AnalogPotentiometer(STACKER_LIFT_POT_RIGHT,1024,0);
		LiftPotLeft = new AnalogPotentiometer(STACKER_LIFT_POT_LEFT,-1024,1024);

		AutoLiftPIDLeft = new PIDController(-.02, -0.000151, -0.03, LiftPotLeft, LiftLeft);
		AutoLiftPIDRight = new PIDController(-.02, -0.000151, -0.03, LiftPotRight, LiftRight);
		Righttime = new Timer;
		Lefttime = new Timer;

		AutoLiftPIDRight->SetAbsoluteTolerance(10);
		AutoLiftPIDRight->SetInputRange(1,1024);
		AutoLiftPIDRight->SetOutputRange(-1,.2);
		AutoLiftPIDLeft->SetAbsoluteTolerance(10);
		AutoLiftPIDLeft->SetInputRange(1,1024);
		AutoLiftPIDLeft->SetOutputRange(-.75,.2);

		elevatorrampspeed           = 0.1;
		extendrampspeed				= 0.1;
		lastreleasedpressed = 0;
		deadband            = 0.1;


		oldelevatorspd = 0;
		oldextendspeed = 0;
		// Give this a value
		targetPoint = 100;

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
		lastswitch = false;
		ExtendState = 0;
}
	//Declare master function
	void Run(bool btngrab, bool autobtn, float pov, int up, int down, int extend, int retract);
	void StackLeft(int lup, int ldown);
	void StackRight(int rup, int rdown);
	void Tune(int pup, int pdown, int biup, int bidown, int iup, int idown, int dup, int ddown, int toggle);
	void init();
	void Extender(int extend, int retract);
	void Grab(int button);
	void ManualStacker(int up, int down);

private: //Only used in this class

	//Declare variables
	bool   lastreleasedpressed;
	float oldelevatorspd, oldextendspeed;
	float elevatorrampspeed, extendrampspeed,deadband;
	float targetPoint;
	int state = 0;
	float rightcurrentlevel, leftcurrentlevel;
	float righttargetlevel, lefttargetlevel;
	float rightelevatormax, leftelevatormax;
	float rightelevatormin, leftelevatormin;
	float lastpov;
	bool lastswitch;
	float p = -.017;
	float i = -.0001;
	float d = .0;
	float LeftOffset = 6;
	int ExtendState;
	float extensionspeed;

	//Declare functions
	void AutoStacker(bool autobtn, float pov);
	void SetLevel(float);
	Relay* Flaps;
	Victor*   LiftRight, *LiftLeft;
	Talon*   ExtendLeft, *ExtendRight;
	DigitalInput* Switch;
	AnalogPotentiometer* LiftPotRight, *LiftPotLeft;
	PIDController* AutoLiftPIDRight, *AutoLiftPIDLeft;
	Timer *Lefttime, *Righttime;

};

#endif
