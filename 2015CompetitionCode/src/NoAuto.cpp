#include "NoAuto.h"

void NoAutonomous::Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro)
{
	SmartDashboard::PutString("Auto Selected", "No Autonomous");
	DriveTrain->AutonomousAngle(180,180,180,180);
}

void NoAutonomous::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro)
{
	GyroOffset = -.5*AutonomousGyro->GetAngle();
	SmartDashboard::PutNumber("GyroReading", GyroOffset);
	DriveTrain->AutonomousAngle(180+GyroOffset, 180+GyroOffset,180,180);
}

void NoAutonomous::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard, Gyro *AutonomousGyro)
{

}
