#include "AutonomousCan.h"

void AutonomousCan::Initialize(Swerve *DriveTrainTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	SmartDashboard::PutString("Auto Selected", "Auto Can");
	cannumber = 2;
	count = 0;
	Autostate = 0;
	Autotime->Reset();
	Hoardtime->Reset();
}

void AutonomousCan::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{

	SmartDashboard::PutNumber("Auto Sate", Autostate);
	SmartDashboard::PutNumber("Autotime", Autotime->Get());
	switch (Autostate)
	{
	case 0:
		Hoard->Extend();
		Autotime->Start();
		if(Autotime->Get() > 1.5){
			Autotime->Stop();
			Autostate = 1;
		}
	break;
	case 1:
		Autotime->Stop();
		Autotime->Reset();
		DriveTrain->AutonomousAngle(180,180,180,180);
		if(DriveTrain->OnTarget())
		{
			Autostate = 10;
		}
	break;
	case 2:
		Hoard->Extend();
		Hoardtime->Start();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > 1.6
					)
			{
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				count = 2;
				Autostate = 9;
			}
		}
	break;
	case 3:
		Hoard->Extend();
		Hoardtime->Start();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > 1)
			{
				count = 3;
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				Autostate = 6;
			}
		}
	break;
	case 4:
		Hoard->Extend();
		Hoardtime->Start();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > .5)
			{
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				Autostate = 6;
			}
		}

		break;
	case 5:
		//Hoarder Out
		Autotime->Reset();
		break;
	case 6:
		Hoardtime->Stop();
		Hoardtime->Reset();
		DriveTrain->AutonomousSpeed(0,0,0,0);
		DriveTrain->AutonomousAngle(90,90,90,90);
		if(DriveTrain->OnTarget())
		{
			Autostate = 7;
		}
		break;
	case 7:
		Autotime->Start();
		DriveTrain->AutonomousSpeed(-1,-1,-1,-1);
		if(Autotime->Get() > 1)
		{
			Hoard->Retract();
			Autotime->Stop();
			Hoardtime->Start();
			Autostate = 8;
		}
		break;
	case 8:
		Autotime->Reset();
		if(Hoardtime->Get() > 1)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Hoardtime->Stop();
			Autostate = 9;
		}
		break;
	case 9:
		//DriveTrain->AutonomousSpeed(1,1,1,1);
		DriveTrain->AutonomousSpeed(0,0,0,0);
		Autotime->Start();

		if(Autotime->Get() > 2)
		{
				Hoard->Retract();
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				if(cannumber > 1 && count == 1)
				{
					Autostate = 2;
				}
				else if(cannumber > 2 && count == 2)
				{
					Autostate = 3;
				}
				else if(cannumber == 4 && count == 3)
				{
					Autostate = 3;
				}
				else
				{
					Autostate = 5;
				}
		}
		break;
	case 10:
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if(Autotime->Get() >= .9)
		{
			count = 1;
			Autostate = 9;
		}
		break;
	}
}

void AutonomousCan::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	Autotime->Reset();
}
