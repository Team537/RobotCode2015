#include "AutonomousCan.h"

void AutonomousCan::Initialize(Swerve *DriveTrainTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	SmartDashboard::PutString("Auto Selected", "Auto Can");
	cannumber = SmartDashboard::GetNumber("Can Count");

	Autostate = 0;
}

void AutonomousCan::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	switch (Autostate)
	{
	case 0:
	  /*DriveTrain->setdistance(10 or something IDFK)
		if (DriveTrain->atdistance())
		{
			AutoState = 1;
		}*/
	break;
	case 1:
		DriveTrain->AutonomousAngle(180,180,180,180);
		if(DriveTrain->OnTarget())
		{
			Hoard->hoard(1);
			Hoard->hoard(0);
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > 2)
			{
				Hoard->hoard(1);
				Hoard->hoard(0);
				if(Autotime->Get() > 3)
				{
					Hoard->hoard(1);
					Hoard->hoard(0);
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
			Hoard->hoard(1);
			Hoard->hoard(0);
			if(Autotime->Get() > 3)
			{
				Hoard->hoard(1);
				Hoard->hoard(0);
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
			Hoard->hoard(1);
			Hoard->hoard(0);
			if(Autotime->Get() > 5)
			{
				Hoard->hoard(1);
				Hoard->hoard(0);
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
			Hoard->hoard(1);
			Hoard->hoard(0);
			if(Autotime->Get() > 3)
			{
				Hoard->hoard(1);
				Hoard->hoard(0);
				Autotime->Stop();
				Autostate = 5;
			}
		}
		break;
	case 5:
		break;
	}
}

void AutonomousCan::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	Autotime->Reset();
}
