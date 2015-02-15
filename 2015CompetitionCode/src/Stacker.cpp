//Dependencies
#include "Stacker.h"
#include <cmath>
#include <ctime>

//When a button is pressed, grab a tote
void Stacker::Grab(bool button)
{
	if (button == 1 && lastreleasedpressed == 0)
	{
		Flaps->Set(!Flaps->Get());
	}
	lastreleasedpressed = button;
}

//When a button is pressed, automatically move the stacker down and back up
void Stacker::AutoStacker(bool autobtn, float pov)
{
	if (state == 0)
	{
		if(pov != -1 && lastpov == -1)
		{
			if (pov == 0)
			{
				righttargetlevel += 250;
				lefttargetlevel += 250;
			}
			if (pov == 180)
			{
				righttargetlevel -= 250;
				lefttargetlevel -= 250;
			}
		}
		//right constraints
		if (righttargetlevel >= rightelevatormax)
		{
			righttargetlevel = rightelevatormax;
		}
		if (righttargetlevel <= rightelevatormin)
		{
			righttargetlevel = rightelevatormin;
		}
		//Right PID Selection (up or down values)
		if((righttargetlevel - rightcurrentlevel) >= 0)
		{
			AutoLiftPIDRight->SetPID(PID_LIFT_UP_RIGHT);
		}
		if((righttargetlevel - rightcurrentlevel) < 0)
		{
			AutoLiftPIDRight->SetPID(PID_LIFT_DOWN_RIGHT);
		}
		//left constraints
		if (lefttargetlevel >= leftelevatormax)
		{
			lefttargetlevel = leftelevatormax;
		}
		if (lefttargetlevel <= leftelevatormin)
		{
			lefttargetlevel = leftelevatormin;
		}
		//left PID selection (up or down)
		if((lefttargetlevel - leftcurrentlevel) >= 0)
		{
			AutoLiftPIDLeft->SetPID(PID_LIFT_UP_LEFT);
		}
		if((lefttargetlevel - leftcurrentlevel) < 0)
		{
			AutoLiftPIDLeft->SetPID(PID_LIFT_DOWN_LEFT);
		}
		// setting target values
		AutoLiftPIDLeft->SetSetpoint(lefttargetlevel);
		AutoLiftPIDRight->SetSetpoint(righttargetlevel);
		rightcurrentlevel = AutoLiftPIDRight->Get();
		leftcurrentlevel = AutoLiftPIDLeft->Get();
	}
	if (autobtn && state == 0)
	{
		state = 1;
	}
	switch (state)
	{
	case 0:
		break;
	case 1:
		AutoLiftPIDLeft->SetPID(PID_LIFT_UP_LEFT);
		AutoLiftPIDRight->SetPID(PID_LIFT_UP_RIGHT);
		AutoLiftPIDLeft->Enable();
		AutoLiftPIDRight->Enable();
		AutoLiftPIDLeft->SetSetpoint(1);
		AutoLiftPIDRight->SetSetpoint(1);
		if (AutoLiftPIDLeft->OnTarget() && AutoLiftPIDRight->OnTarget())
		{
			Clock.Start();
			state = 2;
		}
		break;
	case 2:
		if (Clock.Get() >= .5)
		{
			AutoLiftPIDLeft->SetPID(PID_LIFT_DOWN_LEFT);
			AutoLiftPIDRight->SetPID(PID_LIFT_DOWN_RIGHT);
			Clock.Stop();
			Clock.Reset();
			AutoLiftPIDLeft->SetSetpoint(0);
			AutoLiftPIDRight->SetSetpoint(0);
			if (AutoLiftPIDLeft->OnTarget() && AutoLiftPIDRight->OnTarget())
			{
				state = 0;
			}
		}
		break;
	default:
		break;
	}
}

//When a joystick is moved, move the stacker accordingly
void Stacker::ManualStacker(int up, int down) {
	if (state == 0)
	{
		if (down)
		{
			AutoLiftPIDLeft->SetPID(PID_LIFT_DOWN_LEFT);
			AutoLiftPIDRight->SetPID(PID_LIFT_DOWN_RIGHT);
			righttargetlevel -= 1;
			lefttargetlevel -= 1;
		}
		if (up)
		{
			AutoLiftPIDLeft->SetPID(PID_LIFT_UP_LEFT);
			AutoLiftPIDRight->SetPID(PID_LIFT_UP_RIGHT);
			righttargetlevel += 1;
			lefttargetlevel += 1;
		}
	}


}


//When a joystick is moved, extend or retract the stacker accordingly
void Stacker::Extender(int extend, int retract)
{

	float spd;
	if (extend)
	{
		spd = 1;
	}
	if (retract)
	{
		spd = -1;
	}
	float LeftJoydiferrance = spd - oldextendspeed;
	if (fabs(LeftJoydiferrance) >= extendrampspeed)
		oldextendspeed += extendrampspeed * (LeftJoydiferrance / fabs(LeftJoydiferrance));
	if (!SwitchIn && !SwitchOut)
	{
		Extend->Set(oldextendspeed);
	}
}


//Master function: Runs all functions
void Stacker::Run(bool btngrab, bool autobtn, float pov,int up, int down, int extend, int retract)
{
	Grab(btngrab);
	AutoStacker( autobtn,  pov);
	ManualStacker( up,  down);
	Extender( extend,  retract);

}
