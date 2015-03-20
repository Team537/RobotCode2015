#include "NoAuto.h"

void NoAutonomous::Initialize(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{
	SmartDashboard::PutString("Auto Selected", "No Autonomous");
}

void NoAutonomous::Run(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{

}

void NoAutonomous::End(Swerve *DriveTrain, Collector *Collect, Stacker *Stack, Hoarder *Hoard)
{

}
