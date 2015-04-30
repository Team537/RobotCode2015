#include "Whips.h"

double Whips::Conversion(double DegreeValue, double Offset)
{
	//converts degrees to encoder ticks
	return ((1024/360)*DegreeValue) + Offset;
}

double Whips::OppisiteConversion(double ticks, double Offset)
{
	return (360/1024) * (ticks - Offset);
}

void Whips::DeployWhips()
{
	//LeftWhip->SetControlMode(CANTalon::kPosition);
	RightWhip->SetControlMode(CANTalon::kPosition);

	RightWhip->SetPID(10,0.004,0);
	//LeftWhip->SetPID(10,0.004,0);

	//LeftWhip->SetD(Conversion(Deployed*-1,-362));
	RightWhip->SetD(Conversion(Deployed,-580));

	//LeftWhip->EnableControl();
	RightWhip->EnableControl();
}

void Whips::RetractWhips()
{
	//LeftWhip->SetControlMode(CANTalon::kPosition);
	RightWhip->SetControlMode(CANTalon::kPosition);

	RightWhip->SetPID(2,0.004,0);
	//LeftWhip->SetPID(2,0.004,0);

	//LeftWhip->SetD(Conversion(Stowed*-1,-362));
	RightWhip->SetD(Conversion(Stowed,-580));

	//LeftWhip->EnableControl();
	RightWhip->EnableControl();
}

bool Whips::ReadyToDrive()
{
	return ((OppisiteConversion(RightWhip->GetPosition(),-580) >= 20));
}

void Whips::TeleWhips(int WhipsToggle)
{
	if(WhipsToggle == 1 && lastpressedWhips == 0)
	{
		retracttoggle = !retracttoggle;
	}
	lastpressedWhips = WhipsToggle;

	if(retracttoggle == true)
	{
		RetractWhips();
	}
	if(retracttoggle == false)
	{
		DeployWhips();
	}
}

void Whips::EndClaws(int ClawToggle)
{
	if(ClawToggle == 1 && lastpressedClaws == 0)
	{
		//LeftClaw->Set(!LeftClaw->Get());
		RightClaw->Set(!RightClaw->Get());
	}
	lastpressedClaws = ClawToggle;
}
