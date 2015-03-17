#include "SimpleCanAndToteAuto.h"

void SimpleCanAndToteAutonomous::Run()
{
	switch(SimpleAutoSwitch)
	{
	case 0:
		Autotime->Reset();
		Elevator->AutoStacker(1,0,0,0);
		Elevator->AutoStacker(0,0,0,0);
		if(Elevator->ReturnState() == 0)
		{
			SimpleAutoSwitch = 1;
		}
		break;
	case 1:
		DriveTrain->AutonomousAngle(90,90,90,90);
		if(DriveTrain->OnTarget())
		{
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			SimpleAutoSwitch = 2;
		}
		break;
	case 2:
		if(Autotime->Get() > 4)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Autotime->Stop();
			SimpleAutoSwitch = 3;
		}
		break;
	case 3:
		Autotime->Reset();
		Elevator->AutoStacker(0,0,1,0);
		if(Elevator->OnTarget())
		{
			DriveTrain->AutonomousAngle(180,180,180,180);
			if(DriveTrain->OnTarget())
			{
				SimpleAutoSwitch = 4;
			}

		}
		break;
	case 4:
		DriveTrain->AutonomousSpeed(.5,.5,.5,.5);
		Autotime->Start();
		if(Autotime->Get() > 4)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Autotime->Stop();
			SimpleAutoSwitch = 5;
		}
		break;
	case 5:
		Autotime->Reset();
		break;
	}
}
