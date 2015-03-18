#include "AutonomousTote.h"

void AutonomousTote::Run()
{
	switch(AutoState)
	{
	case 0:
		Autotime->Reset();
		Stack->AutoStacker(1,0,0,0);
		if(Stack->ReturnState() == 0)
		{
			if(repetition < 2)
			{
				DriveTrain->AutonomousAngle(270,270,270,270);
				if(DriveTrain->OnTarget())
				{
					AutoState = 1;
				}
			}
			else
			{
				DriveTrain->AutonomousAngle(90,90,90,90);
				if(DriveTrain->OnTarget())
				{
					AutoState = 5;
				}
			}
		}
	break;
	case 1:
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if(Autotime->Get() > 2)
		{
			Autotime->Stop();
			DriveTrain->AutonomousSpeed(0,0,0,0);
			DriveTrain->AutonomousAngle(180,180,180,180);
			if(DriveTrain->OnTarget())
			{
				AutoState = 2;
			}
		}
	break;
	case 2:
		Autotime->Reset();
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if(Autotime->Get() > 3)
		{
			Autotime->Stop();
			DriveTrain->AutonomousSpeed(0,0,0,0);
			DriveTrain->AutonomousAngle(90,90,90,90);
			if(DriveTrain->OnTarget())
			{
				AutoState = 3;
			}
		}
	break;
	case 3:
		Autotime->Reset();
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if(Autotime->Get() > 2)
		{
			Autotime->Stop();
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Collect->setState(1,0,0);
			Collect->setGrab(1,0,0);
			Collect->setMotors(1,1,0,0);
			DriveTrain->AutonomousAngle(180,180,180,180);
			if(DriveTrain->OnTarget())
			{
				Collect->setMotors(0,0,0,0);
				AutoState = 4;
			}
		}
	break;
	case 4:
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if(Autotime->Get() > 1)
		{
			Autotime->Stop();
			DriveTrain->AutonomousSpeed(0,0,0,0);
			repetition++;
			AutoState = 0;
		}
	break;
	case 5:
		DriveTrain->AutonomousSpeed(1.5,1.5,1.5,1.5);
		Autotime->Start();
		if(Autotime->Get() > 3)
		{
			Autotime->Stop();
			DriveTrain->AutonomousSpeed(0,0,0,0);
			AutoState = 6;
		}
		break;
	case 6:
		Autotime->Reset();
		break;
	}
}
