#include "SimpleAuto.h"

void SimpleAutonomous::Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro) {
	DriveTrain->Initialize();
	SmartDashboard::PutString("Auto Selected", "Simple Autonomous");
	SimpleAutoSwitch = 0;
}

void SimpleAutonomous::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro) {
	GyroOffset = -.5 * AutonomousGyro->GetAngle();
	SmartDashboard::PutNumber("GyroReading", GyroOffset);

	switch (SimpleAutoSwitch) {
	case 0:
		//Set Angle Target
		DriveTrain->AutonomousAngle(180, 180, 180, 180);
		if (DriveTrain->OnTarget()) {
			SimpleAutoSwitch = 1;
		}
		break;
	case 1:
		//Drive For a Time
		DriveTrain->AutonomousSpeed(1, 1, 1, 1);
		Autotime->Start();
		if (Autotime->Get() >= 1.75) {
			DriveTrain->AutonomousSpeed(0, 0, 0, 0);
			Autotime->Stop();
			SimpleAutoSwitch = 2;
		}

		DriveTrain->AutonomousAngle(180 + GyroOffset, 180 + GyroOffset, 180, 180);
		/*DriveTrain->SetDistance(300,300,300,300);
		 if (DriveTrain->DistanceOnTarget())
		 {
		 DriveTrain->DisableDistance();
		 SimpleAutoSwitch = 2;
		 }*/
		break;
	case 2:
		//Reset Timer
		Autotime->Reset();
		break;
	}
	SmartDashboard::PutNumber("AutoState", SimpleAutoSwitch);
}

void SimpleAutonomous::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro) {
	Autotime->Reset();
}
