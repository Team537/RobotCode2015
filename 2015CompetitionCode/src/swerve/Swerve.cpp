#include "Swerve.h"
#include "SwerveModule.h"

void Swerve::Initialize()
{
	newtime.Start();
	AngleSetpoint = 90;
	FrontLeftMod->Initialize();
	FrontRightMod->Initialize();
	BackLeftMod->Initialize();
	BackRightMod->Initialize();
	AngleSetpoint = .5;
	SmartDashboard::PutNumber("538test", 538);
	automatic->InitializeRuntime(BackRightMod->ReadPot());
}

void Swerve::Run()
{
						FrontLeftMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));
						FrontRightMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));
						BackRightMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));
						BackLeftMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));

					/*if (Controller->GetRawButton(7) || Controller->GetRawButton(8))
					{
						FrontLeftMod->AutoDrive(329.3);
						FrontRightMod->AutoDrive(30.7);
						BackLeftMod->AutoDrive(30.7);
						BackRightMod->AutoDrive(329.3);
						if (FrontRightMod->AtAngle() && BackRightMod->AtAngle() && FrontLeftMod->AtAngle() && BackLeftMod->AtAngle() && Controller->GetRawButton(8))
						{
							FrontLeftMod->drive(0,-1);
							FrontRightMod->drive(0,1);
							BackRightMod->drive(0,1);
							BackLeftMod->drive(0,-1);
						}
						if (FrontRightMod->AtAngle() && BackRightMod->AtAngle() && FrontLeftMod->AtAngle() && BackLeftMod->AtAngle() && Controller->GetRawButton(7))
						{
							FrontLeftMod->drive(0,1);
							FrontRightMod->drive(0,-1);
							BackRightMod->drive(0, -1);
							BackLeftMod->drive(0,1);
						}
					}
					else
					{
						NAngleSetpoint = Controller->GetDirectionDegrees();
						NAngleSetpoint = NAngleSetpoint * (-1);
						NAngleSetpoint += 180;
						AngleSetpoint = (NAngleSetpoint);
						SmartDashboard::PutNumber("Magnitude", Controller->GetMagnitude());
						if(AngleSetpoint > 315)
						{
							sign = -1;
							AngleSetpoint -= 180;
						}
						else if (AngleSetpoint < 45)
						{
							sign = -1;
							AngleSetpoint += 180;
						}
						else{
							sign = 1;
						}
						SmartDashboard::PutNumber("Angle Setpoint", AngleSetpoint);
						FrontRightMod->AutoDrive(AngleSetpoint);
						BackLeftMod->AutoDrive(AngleSetpoint);
						BackRightMod->AutoDrive(AngleSetpoint);
						FrontLeftMod->AutoDrive(AngleSetpoint);
						if (FrontRightMod->AtAngle() && BackRightMod->AtAngle() && FrontLeftMod->AtAngle() && BackLeftMod->AtAngle())
						{
							FrontLeftMod->drive(Controller->GetRawAxis(0),sign*Controller->GetMagnitude());
							FrontRightMod->drive(Controller->GetRawAxis(0),sign*Controller->GetMagnitude());
							BackRightMod->drive(Controller->GetRawAxis(0), sign*Controller->GetMagnitude());
							BackLeftMod->drive(Controller->GetRawAxis(0),sign*Controller->GetMagnitude());
						}
						else
						{
							FrontLeftMod->drive(0,0);
							FrontRightMod->drive(0,0);
							BackRightMod->drive(0,0);
							BackLeftMod->drive(0,0);
						}
					}*/
}

void Swerve::TestMode()
{
	LW->AddActuator("Left Back", "Angle", FrontLeftMod->GetAnglePID());
}

void Swerve::Tune()
{
					//Manually drive the motors use for sensor testing

					//FrontLeftMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));
					//FrontRightMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));
					//BackRightMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));
					//BackLeftMod->drive(Controller->GetRawAxis(0),Controller->GetRawAxis(1));

					//Get Angle based off Button Inputs

					if (Controller->GetRawButton(1) == 1){
						AngleSetpoint = 250;
					}
					else if (Controller->GetRawButton(2)) {
						AngleSetpoint = 185;
					}
					else {
						AngleSetpoint = 165;
					}

					//Get Angle Based off Joystick

					//AngleSetpoint = Controller->GetDirectionDegrees();
					//AngleSetpoint += 180;
					//SmartDashboard::PutNumber("Angle Setpoint", AngleSetpoint);
					//SmartDashboard::PutNumber("N Angle Setpoint", NAngleSetpoint);

					//Enables AutoDrive

					//FrontRightMod->AutoDrive(AngleSetpoint);
					//BackLeftMod->AutoDrive(AngleSetpoint);
					BackRightMod->AutoDrive(AngleSetpoint);
					//FrontLeftMod->AutoDrive(AngleSetpoint);

		 		if(newtime.Get() >= .25)
					{
						if (Controller->GetRawButton(7)==1)
						{
							p-=.0001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(8)==1)
						{
							p+=.0001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(9)==1)
						{
							i-=.000001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(10)==1)
						{
							i+=.000001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(3)==1)
						{
							i-=.00001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(5)==1)
						{
							i+=.00001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(11)==1)
						{
							d-=.0001;
							BackRightMod->Reset();
						}
						if (Controller->GetRawButton(12)==1)
						{
							d+=.0001;
							BackRightMod->Reset();
						}
						BackRightMod->offSetAdjust(Controller->GetRawButton(4),Controller->GetRawButton(6));
					SmartDashboard::PutNumber("P Change Test", PChangeTest);
						newtime.Stop();
						newtime.Reset();
						newtime.Start();
						BackRightMod->PIDAdjust(p,i,d);
						}
}
