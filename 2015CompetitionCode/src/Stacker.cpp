
//Dependencies
#include "Stacker.h"
#include <cmath>
#include <ctime>

void Stacker::init()
{
	AutoLiftPIDRight->Disable();
	AutoLiftPIDLeft->Disable();
	Clock.Start();
	state = 0;
	targetPoint = LiftPotLeft->Get();
	ExtendState = 0;
}

//When a button is pressed, grab a tote
void Stacker::Grab(int button)
{
	if (button == 0 && lastreleasedpressed == 1)
	{
		if (Flaps->Get() == Relay::Value::kOff)
		{
			Flaps->Set(Relay::Value::kOn);
		}
		else
		{
			Flaps->Set(Relay::Value::kOff);
		}
	}

	lastreleasedpressed = button;
}

//When a button is pressed, automatically move the stacker down and back up
void Stacker::AutoStacker(bool autobtn, int levelup, int leveldown)
{
	switch (state)
	{
		case 0:
			if(levelup && lastleveluppressed == 0)
			{
				level ++;
				if (level > 3)
				{
					level = 3;
				}
				SwitchLevel(level);
			}
			if(leveldown && lastleveldownpressed == 0)
			{
				level --;
				if (level < 0)
				{
					level = 0;
				}
				SwitchLevel(level);
			}
			lastleveluppressed = levelup;
			lastleveldownpressed = leveldown;
			if (autobtn)
			{
				state = 1;
			}
			SetLevel(targetPoint);
			break;
		case 1:
			if(ExtendState != 2)
			{
				Stacker::Extender(1,0,0,0);
			}
			if(ExtendState == 2)
			{
				state = 2;
			}
			break;
		case 2:
			targetPoint = ZERO;
			SetLevel(targetPoint);
			if (AutoLiftPIDLeft->OnTarget() && AutoLiftPIDRight->OnTarget())
			{
				Clock.Start();
				state = 3;
			}
			break;
		case 3:
			if (Clock.Get() >= .25)
			{
				targetPoint = ONE;
				SetLevel(targetPoint);
				if (AutoLiftPIDLeft->OnTarget() && AutoLiftPIDRight->OnTarget())
				{
					Clock.Stop();
					Clock.Reset();
					state = 0;
					level = 1;
				}
			}
			break;
		default:
			break;
	}
	SmartDashboard::PutNumber("Automatic Stacker State", state);
	SmartDashboard::PutNumber("level", level);
}

void  Stacker::SwitchLevel(int totelevel)
{
	switch(totelevel)
	{
		case 0:
			targetPoint = ZERO;
			break;
		case 1:
			targetPoint = ONE;
			break;
		case 2:
			targetPoint = TWO;
			break;
		case 3:
			targetPoint = THREE;
			break;
	}
}

void Stacker::CurrentLevel()
{
	if (LiftPotLeft->Get() < ONE)
	{
		currentlevel = 0;
	}
	else if (LiftPotLeft->Get() > ONE && LiftPotLeft->Get() < TWO)
	{
		currentlevel = 1;
	}
	else if (LiftPotLeft->Get() > TWO && LiftPotLeft->Get() < THREE)
	{
		currentlevel = 2;
	}
	else
	{
		currentlevel = 3;
	}
	SmartDashboard::PutNumber("Current Stacker Level", currentlevel);
}

bool Stacker::DangerLevel()
{
	return (currentlevel < 1);
}

//When a joystick is moved, move the stacker accordingly
void Stacker::ManualStacker(int up, int down) {
		if (down)
		{
			level = 4;
//			AutoLiftPIDLeft->SetPID(PID_LIFT_DOWN_LEFT);
//			AutoLiftPIDRight->SetPID(PID_LIFT_DOWN_RIGHT);
			targetPoint -= 5;
			level = 4;
		}
		if (up)
		{
			level = 4;
//			AutoLiftPIDLeft->SetPID(PID_LIFT_UP_LEFT);
//			AutoLiftPIDRight->SetPID(PID_LIFT_UP_RIGHT);
			targetPoint += 5;
		}
	SetLevel(targetPoint);
}


//When a joystick is moved, extend or retract the stacker accordingly
void Stacker::Extender(int extend, int retract, int limitswitch, int manual)
{
	switch (ExtendState){
	case 0:
		extendtimer->Start();
		extensionspeed = -.25;
		if (extendtimer->Get() > .5)
		{
			extensionspeed = .25;
			if(Switch->Get() == 0)
			{
				extendtimer->Stop();
				extendtimer->Reset();
				ExtendState = 2;
			}
		}
		break;
	case 1:
		if(extend)
		{
			extensionspeed = .25;
			if (Switch->Get() == 0)
			{
				ExtendState = 2;
			}
		}
		else if (retract)
		{
			extensionspeed = -.25;
			if (Switch->Get() == 0)
			{
				ExtendState = 3;
			}
		}
		else{
			extensionspeed = 0;
		}
		if (manual)
		{
			ExtendState = 4;
		}
		break;
	case 2:
		if (retract)
		{
			extensionspeed = -.25;
			if (Switch->Get() == 1)
			{
				ExtendState = 1;
			}
		}
		else
		{
			extensionspeed = 0;
		}
		if (manual)
		{
			ExtendState = 4;
		}
		break;
	case 3:
		if(extend)
		{
			extensionspeed = .25;
			if (Switch->Get() == 1)
			{
				ExtendState = 1;
			}
		}
		else
		{
			extensionspeed = 0;
		}
		if (manual)
		{
			ExtendState = 4;
		}
		break;
	case 4:
		if (extend)
		{
			extensionspeed = .25;
		}
		else if (retract)
		{
			extensionspeed = -.25;
		}
		else
		{
			extensionspeed = 0;
		}
		if(limitswitch)
		{
			ExtendState = 1;
		}
		break;
	}
	ExtendLeft->Set(extensionspeed);
	ExtendRight->Set(-extensionspeed);
	SmartDashboard::PutNumber("Limit Switch", Switch->Get());
	SmartDashboard::PutNumber("ExtendState", ExtendState);
}


//Master function: Runs all functions
/*void Stacker::Run(bool btngrab, bool autobtn, float pov,int up, int down, int extend, int retract)
{
	Grab(btngrab);
	AutoStacker( autobtn,  pov);
	ManualStacker( up,  down);
	Extender( extend,  retract, limitswitch, manual);

}*/

void Stacker::StackLeft(int lup, int ldown)
{
	if(lup)
	{
		LiftLeft->Set(-.5);
	}
	else if(ldown)
	{
		LiftLeft->Set(.25);
	}
	else
	{
		LiftLeft->Set(0);
	}
	SmartDashboard::PutNumber("Stacker Left Pot Value", LiftPotLeft->Get());
}

void Stacker::StackRight(int rup, int rdown)
{
	if(rup)
	{
		LiftRight->Set(-.5);
	}
	else if(rdown)
	{
		LiftRight->Set(.25);
	}
	else
	{
		LiftRight->Set(0);
	}
	SmartDashboard::PutNumber("Stacker Right Pot Value", LiftPotRight->Get());
}
void Stacker::Tune(int pup, int pdown, int biup, int bidown, int iup, int idown, int dup, int ddown, int toggle, int otoggle)
{
	AutoLiftPIDLeft->Enable();
	AutoLiftPIDRight->Enable();

	int setPoint = 100;
	if(toggle)
	{
		setPoint = 500;
	}
	else if (otoggle)
	{
		setPoint = 5;
	}
	else
	{
		setPoint = 300;
	}

	SetLevel(setPoint);

	if(Clock.Get() > .25)
	{
		if (pup == 1)
		{
			p += 0.001;
		}
		if (pdown == 1)
		{
			p -= 0.001;
		}
		if (biup == 1)
		{
			i += 0.0001;
		}
		if (bidown == 1)
		{
			i -= 0.0001;
		}
		if (iup == 1)
		{
			i += 0.000001;
		}
		if (idown == 1)
		{
			i -= 0.000001;
		}
		if (dup == 1)
		{
			d += 0.001;
		}
		if (ddown == 1)
		{
			d -= 0.001;
		}
		Clock.Reset();
		Clock.Start();
	}
	//AutoLiftPIDLeft->SetPID(p,i,d);
	AutoLiftPIDRight->SetPID(p,i,d);
}

void Stacker::SetLevel(float SetPoint, bool leftarm, bool rightarm)
{
	if (SetPoint < ONE)
	{
		{
			if (SetPoint < 10)
			{
				AutoLiftPIDLeft->SetSetpoint(15);
				AutoLiftPIDRight->SetSetpoint(26);
			}
			if (SetPoint > 10)
			{
				AutoLiftPIDLeft->SetSetpoint(SetPoint+LeftOffset);
				AutoLiftPIDRight->SetSetpoint(SetPoint);
			}
		}
	}
	else
	{
		AutoLiftPIDLeft->SetSetpoint(SetPoint+LeftOffset);
		AutoLiftPIDRight->SetSetpoint(SetPoint);
	}
	if (AutoLiftPIDLeft->OnTarget())
	{
		Lefttime->Start();
		if(Lefttime->Get() > 1)
		{
			Lefttime->Stop();
			AutoLiftPIDLeft->Disable();
		}
	}
	else
	{
		Lefttime->Stop();
		Lefttime->Reset();
		AutoLiftPIDLeft->Enable();
	}
	if (AutoLiftPIDRight->OnTarget())
	{
		Righttime->Start();
		if(Righttime->Get() > 1)
		{
			Righttime->Stop();
			AutoLiftPIDRight->Disable();
		}
	}
	else
	{
		Righttime->Stop();
		Righttime->Reset();
		AutoLiftPIDRight->Enable();
	}
	SmartDashboard::PutNumber("Right time", Righttime->Get());
	SmartDashboard::PutNumber("Left time", Lefttime->Get());
	SmartDashboard::PutNumber("Stacker P", p);
	SmartDashboard::PutNumber("Stacker I", i * 1000);
	SmartDashboard::PutNumber("Stacker D", d);
	SmartDashboard::PutNumber("Stacker Left Error", AutoLiftPIDLeft->GetError());
	SmartDashboard::PutNumber("Stacker Right Error", AutoLiftPIDRight->GetError());
	SmartDashboard::PutNumber("Stacker Left Error2", AutoLiftPIDLeft->GetError());
	SmartDashboard::PutNumber("Stacker Right Error2", AutoLiftPIDRight->GetError());
	SmartDashboard::PutNumber("Stacker Left Pot Value", LiftPotLeft->Get());
	SmartDashboard::PutNumber("Stacker Right Pot Value", LiftPotRight->Get());
	SmartDashboard::PutNumber("Stacker Left Setpoint", AutoLiftPIDLeft->GetSetpoint());
	SmartDashboard::PutNumber("Stacker Right Setpoint", AutoLiftPIDRight->GetSetpoint());
	CurrentLevel();
}
