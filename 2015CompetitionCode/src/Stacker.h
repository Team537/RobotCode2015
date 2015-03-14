//Define the header file
#ifndef STACKER_H
#define STACKER_H

//Dependencies
#include <WPILib.h>
#include "Schematic.h"
#include "Collector.h"
#include "cmath"


//Stacker class constructor
class Stacker
{


	Timer Clock;

public: //Used in all classes

	int currentlevel;

	Stacker()
{
		Flaps = new Relay(STACKER_FLAPS, Relay::Direction::kForwardOnly);
		LiftRight = new Victor (STACKER_LIFT_RIGHT);
		LiftLeft = new Victor (STACKER_LIFT_LEFT);
		ExtendLeft = new Talon (STACKER_EXTEND_LEFT);
		ExtendRight = new Talon (STACKER_EXTEND_RIGHT);
		SwitchLeft = new DigitalInput(STACKER_SWITCH_LEFT);
		SwitchRight = new DigitalInput(STACKER_SWITCH_RIGHT);

		LiftPotRight = new AnalogPotentiometer(STACKER_LIFT_POT_RIGHT,1024,0);
		LiftPotLeft = new AnalogPotentiometer(STACKER_LIFT_POT_LEFT,-1024,1024);

		AutoLiftPIDLeft = new PIDController(-.02, -0.000151, -0.054, LiftPotLeft, LiftLeft);
		AutoLiftPIDRight = new PIDController(-.02, -0.000151, -0.054, LiftPotRight, LiftRight);
		Righttime = new Timer;
		Lefttime = new Timer;
		extendlefttimer = new Timer;
		extendrighttimer = new Timer;

		AutoLiftPIDRight->SetAbsoluteTolerance(5);
		AutoLiftPIDRight->SetInputRange(1,1024);
		AutoLiftPIDRight->SetOutputRange(-1,.45);
		AutoLiftPIDLeft->SetAbsoluteTolerance(5);
		AutoLiftPIDLeft->SetInputRange(1,1024);
		AutoLiftPIDLeft->SetOutputRange(-.75,.4);

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
		ExtendStateLeft = 0;
		ExtendStateRight = 0;
		level = 1;
		lastleveldownpressed = 0;
		lastleveluppressed = 0;
		currentlevel = 1;
}
	//Declare master function
	void Run(bool btngrab, bool autobtn, float pov, int up, int down, int extend, int retract);
	void StackLeft(int lup, int ldown);
	void StackRight(int rup, int rdown);
	void Tune(int pup, int pdown, int biup, int bidown, int iup, int idown, int dup, int ddown, int toggle, int otoggle);
	void init();
	void Extender(int extend, int retract, int limitswitch, int manual);
	void Grab(int button);
	void ManualStacker(int up, int down);
	void AutoStacker(bool autobtn, int levelup, int leveldown);
	bool DangerLevel();
	bool CollectorDanger(bool left, bool right);


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
	float p = -.02;
	float i = -.000151;
	float d = -.054;
	float LeftOffset = 0;
	int ExtendStateLeft, ExtendStateRight;
	float extensionspeedleft, extensionspeedright;
	int level;
	int lastleveldownpressed;
	int lastleveluppressed;
	bool danger;

	//Declare function
	void SetLevel(float);
	void SwitchLevel(int);
	void CurrentLevel();
	Relay* Flaps;
	Victor*   LiftRight, *LiftLeft;
	Talon*   ExtendLeft, *ExtendRight;
	DigitalInput* SwitchLeft, *SwitchRight;
	AnalogPotentiometer* LiftPotRight, *LiftPotLeft;
	PIDController* AutoLiftPIDRight, *AutoLiftPIDLeft;
	Timer *Lefttime, *Righttime, *extendlefttimer, *extendrighttimer;

};

#endif
