#include "WhipAuto.h"

void WhipAuto::Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro) {
	AutoState = 0;
	AutoTimer->Reset();
}

void WhipAuto::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro) {
	//Step 1 PID Down  to 85

	//Step 2 After 20 drive back at full speed

	//Step 3 retract whips

	switch (AutoState) {
	case 1:
		DriveTrain->AutonomousAngle(180, 180, 180, 180);
		CanStealer->DeployWhips();
		if (CanStealer->ReadyToDrive()) {
			AutoState = 2;
		}
		break;
	case 2:
		DriveTrain->AutonomousSpeed(2, 2, 2, 2);
		AutoTimer->Start();
		if (AutoTimer->Get() > 1.5) {
			AutoTimer->Stop();
			AutoState = 3;
		}
		break;
	case 3:
		AutoTimer->Reset();
		DriveTrain->AutonomousSpeed(0, 0, 0, 0);
		CanStealer->RetractWhips();
		break;
	}
}

void WhipAuto::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro) {

}
