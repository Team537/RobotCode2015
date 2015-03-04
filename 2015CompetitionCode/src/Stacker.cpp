
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
//	switch (state)
//	{
//	case 0:
//		break;
//	case 1:
//		AutoLiftPIDLeft->SetPID(PID_LIFT_UP_LEFT);
//		AutoLiftPIDRight->SetPID(PID_LIFT_UP_RIGHT);
//		AutoLiftPIDLeft->Enable();
//		AutoLiftPIDRight->Enable();
//		AutoLiftPIDLeft->SetSetpoint(1);
//		AutoLiftPIDRight->SetSetpoint(1);
//		if (AutoLiftPIDLeft->OnTarget() && AutoLiftPIDRight->OnTarget())
//		{
//			Clock.Start();
//			state = 2;
//		}
//		break;
//	case 2:
//		if (Clock.Get() >= .5)
//		{
//			AutoLiftPIDLeft->SetPID(PID_LIFT_DOWN_LEFT);
//			AutoLiftPIDRight->SetPID(PID_LIFT_DOWN_RIGHT);
//			Clock.Stop();
//			Clock.Reset();
//			AutoLiftPIDLeft->SetSetpoint(0);
//			AutoLiftPIDRight->SetSetpoint(0);
//			if (AutoLiftPIDLeft->OnTarget() && AutoLiftPIDRight->OnTarget())
//			{
//				state = 0;
//			}
//		}
//		break;
//	default:
//		break;
//	}
}

//When a joystick is moved, move the stacker accordingly
void Stacker::ManualStacker(int up, int down) {
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

	SmartDashboard::PutNumber("Stacker Left Error", AutoLiftPIDLeft->GetError());
	SmartDashboard::PutNumber("Stacker Right Error", AutoLiftPIDRight->GetError());
	SmartDashboard::PutNumber("Stacker Left Error2", AutoLiftPIDLeft->GetError());
	SmartDashboard::PutNumber("Stacker Right Error2", AutoLiftPIDRight->GetError());
	SmartDashboard::PutNumber("Stacker Left Pot Value", LiftPotLeft->Get());
	SmartDashboard::PutNumber("Stacker Right Pot Value", LiftPotRight->Get());
	SmartDashboard::PutNumber("Stacker Left Setpoint", AutoLiftPIDLeft->GetSetpoint());
	SmartDashboard::PutNumber("Stacker Right Setpoint", AutoLiftPIDRight->GetSetpoint());
	SetLevel(targetPoint);
}


//When a joystick is moved, extend or retract the stacker accordingly
void Stacker::Extender(int extend, int retract)
{
	switch (ExtendState){
	case 0:
		ExtendState = 1;
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
		break;
	}
	ExtendLeft->Set(extensionspeed);
	ExtendRight->Set(-extensionspeed);
	SmartDashboard::PutNumber("Limit Switch", Switch->Get());
}


//Master function: Runs all functions
void Stacker::Run(bool btngrab, bool autobtn, float pov,int up, int down, int extend, int retract)
{
	Grab(btngrab);
	AutoStacker( autobtn,  pov);
	ManualStacker( up,  down);
	Extender( extend,  retract);

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
void Stacker::Tune(int pup, int pdown, int biup, int bidown, int iup, int idown, int dup, int ddown, int toggle)
{
	AutoLiftPIDLeft->Enable();
	AutoLiftPIDRight->Enable();

	int setPoint = 100;
	if(toggle)
	{
		setPoint = 500;
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
	AutoLiftPIDLeft->SetPID(p,i,d);
	AutoLiftPIDRight->SetPID(p,i,d);
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


}

void Stacker::SetLevel(float SetPoint)
{
	AutoLiftPIDLeft->SetSetpoint(SetPoint+LeftOffset);
	AutoLiftPIDRight->SetSetpoint(SetPoint);
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
}
