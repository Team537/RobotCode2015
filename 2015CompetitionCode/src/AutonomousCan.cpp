#include "AutonomousCan.h"

void AutonomousCan::Initialize(Swerve *DriveTrainTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro)
{
	count = 0;
	Autostate = INITIALIZE;
	Autotime->Reset();
	Hoardtime->Reset();
}

void AutonomousCan::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro)
{
	GyroOffset = -.5*AutonomousGyro->GetAngle();
	SmartDashboard::PutNumber("Auto Sate", Autostate);
	SmartDashboard::PutNumber("Autotime", Autotime->Get());
	switch (Autostate)
	{
	case INITIALIZE:
		Hoard->Extend();
		Autotime->Start();
		if(Autotime->Get() > 1.25){
			Autotime->Stop();
			Autostate = SETWHEEL_ANGLE;
		}
	break;

	case SETWHEEL_ANGLE:
		Autotime->Stop();
		Autotime->Reset();
		DriveTrain->AutonomousAngle(180,180,180,180);
		if(DriveTrain->OnTarget())
		{
			Autostate = FIRST_CAN;
		}
	break;

	case FIRST_CAN:
		DriveTrain->AutonomousAngle(180+GyroOffset, 180+GyroOffset,180,180);
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if(Autotime->Get() >= 1.1)
		{
			count = 1;
			Autostate = RETRACT_STATE;
		}
		/*
		 * DriveTrain->SetDistance(24,24,24,24);
		 * if (DriveTrain->DistanceOnTarget())
		 * {
		 * 		count = 1;
				Autostate = RETRACT_STATE;
		 * }
		 */
		break;

	case SECOND_CAN:
		DriveTrain->AutonomousAngle(180+GyroOffset, 180+GyroOffset,180,180);
		Hoardtime->Start();
		if(Hoardtime->Get() > .1)
		{
			Hoard->Extend();
			Hoardtime->Stop();
		}
		DriveTrain->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 1.95)
		{
			Hoardtime->Reset();
			Autotime->Stop();
			Autotime->Reset();
			count = 2;
			Autostate = RETRACT_STATE;
		}
		/*
		 * DriveTrain->SetDistance(36,36,36,36);
		 * if (DriveTrain->DistanceOnTarget())
		 * {
		 * 		Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				count = 2;
				Autostate = RETRACT_STATE;
		 * }
		 */
	break;

	case THIRD_CAN:
		DriveTrain->AutonomousAngle(180+GyroOffset, 180+GyroOffset,180,180);
			Hoard->Extend();
			Hoardtime->Start();
			if(Hoardtime->Get() > .5)
			{
				Hoardtime->Stop();
				DriveTrain->AutonomousSpeed(1,1,1,1);
				Autotime->Start();
				if (Autotime->Get() > 2.5)
				{
					count = 3;
					Hoardtime->Reset();
					Autotime->Stop();
					Autotime->Reset();
					Autostate =RETRACT_STATE;
				}
			}
		/*
		 * DriveTrain->SetDistance(48,48,48,48);
		 * if (DriveTrain->DistanceOnTarget())
		 * {
		 *		count = 3;
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				Autostate =RETRACT_STATE;
		 * }
		 */
	break;

	case FOURTH_CAN:
		DriveTrain->AutonomousAngle(180+GyroOffset, 180+GyroOffset,180,180);
		Hoard->Extend();
		Hoardtime->Start();
		if(Hoardtime->Get() > .5)
		{
			Hoardtime->Stop();
			DriveTrain->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > .5)
			{
				count = 4;
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				Autostate = RETRACT_STATE;
			}
		}
		/*
		 * DriveTrain->SetDistance(48,48,48,48);
		 * if (DriveTrain->DistanceOnTarget())
		 * {
		 *		count = 4;
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				Autostate = RETRACT_STATE;
		 * }
		 */
		break;

	case RETRACT_STATE:
		DriveTrain->AutonomousSpeed(0,0,0,0);

		if((count - cannumber) != 0)
		{
			Hoard->Retract();
			Autotime->Start();
			if(Autotime->Get() > 2)
			{
				Hoardtime->Reset();
				Autotime->Stop();
				Autotime->Reset();
				if(cannumber > 1 && count == 1)
				{
					Autostate = SECOND_CAN;
				}
				else if(cannumber > 2 && count == 2)
				{
					Autostate = THIRD_CAN;
				}
				else if(cannumber == 4 && count == 3)
				{
					Autostate = FOURTH_CAN;
				}
				else
				{
					Autostate = NEW_ANGLE;
				}
			}
		}
		else
		{
			Hoardtime->Reset();
			Autotime->Stop();
			Autotime->Reset();
			if(cannumber > 1 && count == 1)
			{
				Autostate = SECOND_CAN;
			}
			else if(cannumber > 2 && count == 2)
			{
				Autostate = THIRD_CAN;
			}
			else if(cannumber == 4 && count == 3)
			{
				Autostate = FOURTH_CAN;
			}
			else
			{
				Autostate = NEW_ANGLE;
			}
		}
		break;

	case NEW_ANGLE:
		//Hoarder Out
		DriveTrain->AutonomousAngle(90,90,90,90);
		if(DriveTrain->OnTarget())
		{
			Autostate = DRIVE_AWAY;
		}
		break;

	case DRIVE_AWAY:
		DriveTrain->AutonomousSpeed(-1,-1,-1,-1);
		Hoard->Retract();
		Autotime->Start();
		if(Autotime->Get() > 1.65)
		{
			DriveTrain->AutonomousSpeed(0,0,0,0);
			Autostate = DONE;
		}
		break;
	case DONE:
		Autotime->Reset();
		break;
	}
}

void AutonomousCan::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro)
{
	Autotime->Reset();
}
