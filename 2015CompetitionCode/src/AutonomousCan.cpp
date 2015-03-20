#include "AutonomousCan.h"

void AutonomousCan::Initialize(Swerve *DriveTrainTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	SmartDashboard::PutString("Auto Selected", "Auto Can");
	cannumber = 1;

	Autostate = 0;
}

void AutonomousCan::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	switch (Autostate)
	{
	case 0:
		Autostate = 1;
	break;
	case 1:
		DriveTrain->AutonomousAngle(180,180,180,180);
		if(DriveTrain->OnTarget())
		{
			Hoard->Extend();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > 2)
			{
				DriveTrain->AutonomousSpeed(0,0,0,0);
				Hoard->Retract();
				if(Autotime->Get() > 3)
				{
					Hoard->Extend();
					Autotime->Stop();
					if(cannumber > 1)
					{
						Autostate = 2;
					}
					else
					{
						Autostate = 5;
					}
				}
			}
		}
	break;
	case 2:
		Autotime->Reset();
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 2)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Hoard->Retract();
			if(Autotime->Get() > 3)
			{
				Hoard->Extend();
				Autotime->Stop();
				if(cannumber > 2)
				{
					Autostate = 3;
				}
				else
				{
					Autostate = 5;
				}
			}
		}
	break;
	case 3:
		Autotime->Reset();
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 4)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Hoard->Retract();
			if(Autotime->Get() > 5)
			{
				Hoard->Extend();
				Autotime->Stop();
				if(cannumber > 3)
				{
					Autostate = 4;
				}
				else
				{
					Autostate = 5;
				}
			}
		}
	break;
	case 4:
		Autotime->Reset();
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 2)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Hoard->Retract();
			if(Autotime->Get() > 3)
			{
				Autotime->Stop();
				Autostate = 5;
			}
		}
		break;
	case 5:
		//Hoarder Out
		Autotime->Reset();
		break;
	}
}

void AutonomousCan::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	Autotime->Reset();
}
