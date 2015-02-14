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
void Stacker::AutoStacker(bool autobtn)
{
	if (autobtn)
	{
		state = 1;
	}
	switch (state)
	{
	case 0:
		break;
	case 1:
		AutoLiftPID->Enable();
		AutoLiftPID->SetSetpoint(1);
		if (AutoLiftPID->OnTarget())
		{
			Clock.Start();
			state = 2;
		}
		break;
	case 2:
		if (Clock.Get() >= .5)
		{
			Clock.Stop();
			Clock.Reset();
			AutoLiftPID->SetSetpoint(2);
			if (AutoLiftPID->OnTarget())
			{
				AutoLiftPID->Disable();
				state = 0;
			}
		}
		break;
	default:
		break;
	}
}

//When a joystick is moved, move the stacker accordingly
void Stacker::ManualStacker(float rightjoy) {
	rightjoy = -1*rightjoy;
	if (fabs(rightjoy) < .1)
		rightjoy = 0;
	if (fabs(rightjoy) > 1)
	{
		if (rightjoy < 0)
		{
			rightjoy = -1;
		}
		if (rightjoy > 0)
		{
			rightjoy = 1;
		}
	}
	float RightJoydiferrance = rightjoy - oldelevatorspd;
	if (fabs(RightJoydiferrance) >= elevatorrampspeed)
		rightjoy += elevatorrampspeed * (RightJoydiferrance / fabs(RightJoydiferrance));
	Lift->Set(rightjoy);
}


//When a joystick is moved, extend or retract the stacker accordingly
void Stacker::Extender(float leftjoy)
{
	if (fabs(leftjoy) < .1)
	{
		leftjoy = 0;
	}
	if (fabs(leftjoy) > 1)
	{
		if (leftjoy < 0)
		{
			leftjoy = -1;
		}
		if (leftjoy > 0)
		{
			leftjoy = 1;
		}
	}
	float LeftJoydiferrance = leftjoy - oldextendspeed;
	if (fabs(LeftJoydiferrance) >= extendrampspeed)
		leftjoy += extendrampspeed * (LeftJoydiferrance / fabs(LeftJoydiferrance));
	if (!SwitchIn && !SwitchOut)
	{
		Extend->Set(leftjoy);
	}
}


//Master function: Runs all functions
void Stacker::Run(bool btngrab, bool autobtn, float leftjoy, float rightjoy)
{
	Grab(btngrab);
	AutoStacker(autobtn);
	ManualStacker(rightjoy);
	Extender(leftjoy);
}
