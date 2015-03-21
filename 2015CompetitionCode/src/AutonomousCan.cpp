#include "AutonomousCan.h"

void AutonomousCan::Initialize(Swerve *DriveTrainTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	SmartDashboard::PutString("Auto Selected", "Auto Can");
	cannumber = 1;

	Autostate = 0;
}

void AutonomousCan::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{

	SmartDashboard::PutNumber("Auto Sate", Autostate);
	switch (Autostate)
	{
	case 0:
		Hoard->Extend();
		Autotime->Start();
		if(Autotime->Get() > .5){
			Autotime->Stop();
			Autostate = 1;
		}
	break;
	case 1:
		Autotime->Reset();
		DriveTrain->AutonomousAngle(180,180,180,180);
		if(DriveTrain->OnTarget())
		{
			Hoard->Extend();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if(Autotime->Get() > .5)
			{
				Autostate = 6;
			}
		}
	break;
	case 2:
		Hoard->Extend();
		Hoardtime->Start();
		Autotime->Reset();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > .5)
			{
				Autostate = 6;
			}
		}
	break;
	case 3:
		Hoardtime->Reset();
		Hoard->Extend();
		Autotime->Reset();
		Hoardtime->Start();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > 1.5)
			{
				Autostate = 6;
			}
		}
	break;
	case 4:
		Hoardtime->Reset();
		Hoard->Extend();
		Autotime->Reset();
		Hoardtime->Start();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > .5)
			{
				Autostate = 6;
			}
		}

		break;
	case 5:
		//Hoarder Out
		Autotime->Reset();
		break;
	case 6:
		DriveTrain->AutonomousSpeed(0,0,0,0);
		Autotime->Stop();
		Autotime->Reset();
		Autotime->Start();
		if(Autotime->Get() > 1)
		{
			Hoard->Retract();
			Autotime->Stop();
			if(cannumber > 1 && count  == 0)
			{
				count++;
				Autostate = 2;
			}
			else if(cannumber > 2 && count == 1)
			{
				count++;
				Autostate = 3;
			}
			else if (cannumber > 3 && count == 2)
			{
				count++;
				Autostate = 4;
			}
			else{
				Autostate = 5;
			}
		}
		break;
	}
}

void AutonomousCan::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	Autotime->Reset();
}
