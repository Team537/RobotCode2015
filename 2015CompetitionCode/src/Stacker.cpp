
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
	ExtendStateLeft = 3;
	ExtendStateRight = 3;
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
void Stacker::AutoStacker(bool autobtn, int levelup, int leveldown, bool buttoncan)
{
	switch (state)
	{
		case 0:
			if(levelup && lastleveluppressed == 0)
			{
				level ++;
				if (level > 3)
				{
					level = currentlevel;
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
			if (buttoncan)
			{
				state = 4;
			}
			SetLevel(targetPoint);
			break;
		case 1:
			if(ExtendStateLeft != 2 && ExtendStateRight != 2)
			{
				Stacker::Extender(1,0,0,0,0);
			}
			if(ExtendStateLeft == 2 && ExtendStateRight == 2)
			{
				state = 2;
			}
			if(Intake->GetLeftArm() == 0 && Intake->GetLeftArm() == 0)
			{
				Intake->setState(1,0,0);
			}
			if(Intake->getGrableft() == 1 && Intake->getGrabright() == 1)
			{
				Intake->setGrab(1,0,0);
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
			if (Clock.Get() >= .5)
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
		case 4:
			targetPoint = CAN;
			SetLevel(targetPoint);
			if(levelup)
			{
				level = 1;
				lastleveluppressed = 1;
				state = 0;
			}
			if(leveldown)
			{
				level = 0;
				state = 0;
			}
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
			if(Intake->GetLeftArm() == 0 && Intake->GetLeftArm() == 0)
			{
				Intake->setState(1,0,0);
			}
			if(Intake->getGrableft() == 1 && Intake->getGrabright() == 1)
			{
				Intake->setGrab(1,0,0);
			}
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

int Stacker::ReturnState()
{
	return state;
}

void Stacker::CurrentLevel()
{
	if (LiftPotLeft->Get() < (ONE -10))
	{
		currentlevel = 0;
	}
	else if (LiftPotLeft->Get() > (ONE - 10) && LiftPotLeft->Get() < (TWO -10))
	{
		currentlevel = 1;
	}
	else if (LiftPotLeft->Get() > (TWO - 10) && LiftPotLeft->Get() < (THREE - 10))
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
	return (LiftPotLeft->Get() <= 200);
}

//When a joystick is moved, move the stacker accordingly
void Stacker::ManualStacker(int up, int down) {
		CurrentLevel();
		if (down)
		{
//			AutoLiftPIDLeft->SetPID(PID_LIFT_DOWN_LEFT);
//			AutoLiftPIDRight->SetPID(PID_LIFT_DOWN_RIGHT);
			targetPoint -= 5;

		}
		if (up)
		{
//			AutoLiftPIDLeft->SetPID(PID_LIFT_UP_LEFT);
//			AutoLiftPIDRight->SetPID(PID_LIFT_UP_RIGHT);
			targetPoint += 5;
		}
	SetLevel(targetPoint);
}


//When a joystick is moved, extend or retract the stacker accordingly
void Stacker::Extender(int extend, int retract, int limitswitch, int manual, int reset)
{
	switch (ExtendStateLeft){
	case 1:
		if(extend)
		{
			extensionspeedleft = .2;
			if (ExtendPotLeft->Get() >= 260)
			{
				ExtendStateLeft = 2;
			}
		}
		else if (retract)
		{
			extensionspeedleft = -.25;
			if (ExtendPotLeft->Get() <=  70.5)
			{
				ExtendStateLeft = 3;
			}
		}
		else{
			extensionspeedleft = 0;
		}
		if(reset)
		{
			ExtendStateLeft = 4;
		}
		break;
	case 2:
		if (retract)
		{
			extensionspeedleft = -.25;
			if (ExtendPotLeft->Get() <= 260)
			{
				ExtendStateLeft = 1;
			}
		}
		else
		{
			extensionspeedleft = 0;
		}
		if(reset)
		{
			ExtendStateLeft = 4;
		}
		break;
	case 3:
		if(extend)
		{
			extensionspeedleft = .2;
			if (ExtendPotLeft->Get() >= 70.5)
			{
				ExtendStateLeft = 1;
			}
		}
		else
		{
			extensionspeedleft = 0;
		}
		if(reset)
		{
			ExtendStateLeft = 4;
		}
		break;
	case 4:
		if(ExtendPotLeft->Get() > 70.5)
		{
			extensionspeedleft = -.25;
		}
		else
		{
			ExtendStateLeft = 3;
		}

	}
	switch (ExtendStateRight){
		case 1:
			if(extend)
			{
				extensionspeedright = .2;
				if (ExtendPotRight->Get() >= 260)
				{
					ExtendStateRight = 2;
				}
			}
			else if (retract)
			{
				extensionspeedright = -.2;
				if (ExtendPotRight->Get() <= 70.5)
				{
					ExtendStateRight = 3;
				}
			}
			else{
				extensionspeedright = 0;
			}
			if(reset)
			{
				ExtendStateRight = 4;
			}
			break;
		case 2:
			if (retract)
			{
				extensionspeedright = -.2;
				if (ExtendPotRight->Get() <= 260)
				{
					ExtendStateRight = 1;
				}
			}
			else
			{
				extensionspeedright = 0;
			}
			if(reset)
			{
				ExtendStateRight = 4;
			}
			break;
		case 3:
			if(extend)
			{
				extensionspeedright = .2;
				if (ExtendPotRight->Get() >= 70.5)
				{
					ExtendStateRight = 1;
				}
			}
			else
			{
				extensionspeedright = 0;
			}
			if(reset)
			{
				ExtendStateRight = 4;
			}
			break;
		case 4:
			if(ExtendPotRight->Get() > 70.5)
			{
				extensionspeedright = -.2;
			}
			else
			{
				ExtendStateRight = 3;
			}
			break;
		}
	ExtendLeft->Set(-.5*extensionspeedleft);
	ExtendRight->Set(.75*extensionspeedright);
	SmartDashboard::PutNumber("Extend Pot Left", ExtendPotLeft->Get());
	SmartDashboard::PutNumber("Extend Pot Right", ExtendPotRight->Get());
	SmartDashboard::PutNumber("ExtendState Left", ExtendStateLeft);
	SmartDashboard::PutNumber("ExtendState Right", ExtendStateRight);
}

bool Stacker::CollectorDanger(bool left, bool right)
{
	if (left || right)
		danger = true;
	else
		danger = false;
	return danger;
}

void Stacker::StackLeft(int lup, int ldown)
{
	if(lup)
	{
		LiftLeft->Set(-1);
	}
	else if(ldown)
	{
		LiftLeft->Set(.75);
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
		LiftRight->Set(1);
	}
	else if(rdown)
	{
		LiftRight->Set(-.75);
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

void Stacker::SetLevel(float SetPoint)
{
		if (SetPoint < 10)
		{
			AutoLiftPIDLeft->SetSetpoint(22);
			AutoLiftPIDRight->SetSetpoint(24);
		}
		if (SetPoint > 10)
		{
			AutoLiftPIDLeft->SetSetpoint(SetPoint+LeftOffset);
			AutoLiftPIDRight->SetSetpoint(SetPoint);
		}
	/*
	if(danger && SetPoint > (ONE - 100))
	{
		AutoLiftPIDLeft->SetSetpoint(SetPoint+LeftOffset);
		AutoLiftPIDRight->SetSetpoint(SetPoint);
	}*/
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
	if(fabs(LiftPotLeft->Get() - LiftPotRight->Get()) > DangerDiferance)
	{
		SmartDashboard::PutNumber("Safety Test", 0);
		if(fabs(AutoLiftPIDLeft->GetError()) > fabs(AutoLiftPIDRight->GetError()))
		{
			SmartDashboard::PutNumber("Safety Test", 1);
			AutoLiftPIDRight->Disable();
		}
		else
		{
			SmartDashboard::PutNumber("Safety Test", 2);
			AutoLiftPIDLeft->Disable();
		}
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
	SmartDashboard::PutBoolean("Left stack pid", AutoLiftPIDLeft->IsEnabled());
	SmartDashboard::PutBoolean("Right stack pid", AutoLiftPIDRight->IsEnabled());
	SmartDashboard::PutNumber("Absolute Pot Differance", fabs(LiftPotLeft->Get() - LiftPotRight->Get()));
	CurrentLevel();
}

bool Stacker::OnTarget()
{
	if(AutoLiftPIDRight->OnTarget() && AutoLiftPIDLeft->OnTarget())
	{
		return true;
	}
	else
	{
		return false;
	}
}
