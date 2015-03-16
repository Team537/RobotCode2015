
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
	ExtendStateLeft = 0;
	ExtendStateRight = 0;
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
			if(Intake->GetLeftArm() == 1 && Intake->GetLeftArm() == 1)
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
			if(Intake->GetLeftArm() == 1 && Intake->GetLeftArm() == 1)
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
	case 0:
		extendlefttimer->Start();
		extensionspeedleft = -.25;
		if (extendlefttimer->Get() > .5)
		{
			extensionspeedleft = .25;
			if(SwitchLeft->Get() == 0)
			{
				extendlefttimer->Stop();
				extendlefttimer->Reset();
				ExtendStateLeft = 2;
			}
		}
		break;
	case 1:
		if(extend)
		{
			extensionspeedleft = .25;
			if (SwitchLeft->Get() == 0)
			{
				ExtendStateLeft = 2;
			}
		}
		else if (retract)
		{
			extensionspeedleft = -.25;
			if (SwitchLeft->Get() == 0)
			{
				ExtendStateLeft = 3;
			}
		}
		else{
			extensionspeedleft = 0;
		}
		if (manual)
		{
			ExtendStateLeft = 4;
		}
		if (reset)
		{
			ExtendStateLeft = 0;
		}
		break;
	case 2:
		if (retract)
		{
			extensionspeedleft = -.25;
			if (SwitchLeft->Get() == 1)
			{
				ExtendStateLeft = 1;
			}
		}
		else
		{
			extensionspeedleft = 0;
		}
		if (manual)
		{
			ExtendStateLeft = 4;
		}
		if (reset)
		{
			ExtendStateLeft = 0;
		}
		break;
	case 3:
		if(extend)
		{
			extensionspeedleft = .25;
			if (SwitchLeft->Get() == 1)
			{
				ExtendStateLeft = 1;
			}
		}
		else
		{
			extensionspeedleft = 0;
		}
		if (manual)
		{
			ExtendStateLeft = 4;
		}
		if (reset)
		{
			ExtendStateLeft = 0;
		}
		break;
	case 4:
		if (extend)
		{
			extensionspeedleft = .25;
		}
		else if (retract)
		{
			extensionspeedleft = -.25;
		}
		else
		{
			extensionspeedleft = 0;
		}
		if(limitswitch)
		{
			ExtendStateLeft = 1;
		}
		if (reset)
		{
			ExtendStateLeft = 0;
		}
		break;
	}
	switch (ExtendStateRight){
		case 0:
			extendrighttimer->Start();
			extensionspeedright = -.25;
			if (extendrighttimer->Get() > .5)
			{
				extensionspeedright = .25;
				if(SwitchRight->Get() == 0)
				{
					extendrighttimer->Stop();
					extendrighttimer->Reset();
					ExtendStateRight = 2;
				}
			}
			break;
		case 1:
			if(extend)
			{
				extensionspeedright = .25;
				if (SwitchRight->Get() == 0)
				{
					ExtendStateRight = 2;
				}
			}
			else if (retract)
			{
				extensionspeedright = -.25;
				if (SwitchRight->Get() == 0)
				{
					ExtendStateRight = 3;
				}
			}
			else{
				extensionspeedright = 0;
			}
			if (manual)
			{
				ExtendStateRight = 4;
			}
			if (reset)
			{
				ExtendStateRight = 0;
			}
			break;
		case 2:
			if (retract)
			{
				extensionspeedright = -.25;
				if (SwitchRight->Get() == 1)
				{
					ExtendStateRight = 1;
				}
			}
			else
			{
				extensionspeedright = 0;
			}
			if (manual)
			{
				ExtendStateRight = 4;
			}
			if (reset)
			{
				ExtendStateRight = 0;
			}
			break;
		case 3:
			if(extend)
			{
				extensionspeedright = .25;
				if (SwitchRight->Get() == 1)
				{
					ExtendStateRight = 1;
				}
			}
			else
			{
				extensionspeedright = 0;
			}
			if (manual)
			{
				ExtendStateRight = 4;
			}
			if (reset)
			{
				ExtendStateRight = 0;
			}
			break;
		case 4:
			if (extend)
			{
				extensionspeedright = .25;
			}
			else if (retract)
			{
				extensionspeedright = -.25;
			}
			else
			{
				extensionspeedright = 0;
			}
			if(limitswitch)
			{
				ExtendStateRight = 1;
			}
			if (reset)
			{
				ExtendStateRight = 0;
			}
			break;
		}
	ExtendLeft->Set(1.04*extensionspeedleft);
	ExtendRight->Set(-extensionspeedright);
	SmartDashboard::PutNumber("Limit Switch Left", SwitchLeft->Get());
	SmartDashboard::PutNumber("Limit Switch Right", SwitchRight->Get());
	SmartDashboard::PutNumber("ExtendState", ExtendStateLeft);
	SmartDashboard::PutNumber("ExtendState", ExtendStateRight);
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

void Stacker::SetLevel(float SetPoint)
{
		if (SetPoint < 10)
		{
			AutoLiftPIDLeft->SetSetpoint(27);
			AutoLiftPIDRight->SetSetpoint(26);
		}
		if (SetPoint > 10)
		{
			AutoLiftPIDLeft->SetSetpoint(SetPoint+LeftOffset);
			AutoLiftPIDRight->SetSetpoint(SetPoint);
		}
	/*}
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
