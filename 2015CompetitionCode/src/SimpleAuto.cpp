#include "SimpleAuto.h"

void SimpleAutonomous::Run()
{
	switch(SimpleAutoSwitch)
	{
	case 0:
		//Set Angle Target
		DriveTrain->AutonomousAngle(180,180,180,180);
		if(DriveTrain->OnTarget())
		{
			SimpleAutoSwitch = 1;
		}
		break;
	case 1:
		//Drive For a Time
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() >= 1.5)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Autotime->Stop();
			SimpleAutoSwitch = 2;
		}
		break;
	case 2:
		//Reset Timer
		Autotime->Reset();
		break;
	}
}
