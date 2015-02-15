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
				targetlevel += 250;
			}
			if (pov == 180)
			{
				targetlevel -= 250;
			}
		}
		if (targetlevel >= elevatormax)
		{
			targetlevel = elevatormax;
		}
		if (targetlevel <= elevatormin)
		{
			targetlevel = elevatormin;
		}
		if((targetlevel - currentlevel) >= 0)
		{
			AutoLiftPID->SetPID(PID_LIFT_UP);
		}
		if((targetlevel - currentlevel) < 0)
		{
			AutoLiftPID->SetPID(PID_LIFT_DOWN);
		}
		AutoLiftPID->SetSetpoint(targetlevel);

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
		AutoLiftPID->SetPID(PID_LIFT_UP);
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
			AutoLiftPID->SetPID(PID_LIFT_DOWN);
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
void Stacker::ManualStacker(int up, int down) {
	if (state == 0)
	{
		if (down)
		{
			AutoLiftPID->SetPID(PID_LIFT_DOWN);
			setpoint -= 1;
		}
		if (up)
		{
			AutoLiftPID->SetPID(PID_LIFT_UP);
			setpoint += 1;
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
