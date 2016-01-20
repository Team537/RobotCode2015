#include "Schematic.h"
#include "SwerveModule.h"
#include "cmath"

void SwerveModule::Initialize() {
	PIDAngle->Disable();
	PIDAngle->Reset();
	PIDAngle->Disable();
	firsttime = true;
	SpeedEncoder->Reset();
}

void SwerveModule::drive(float speed) {
	SpeedEncoder->SetPIDSourceParameter(PIDSource::kRate);

	if (fabs(speed) < JOYDEADBAND) {
		speed = 0;
	}

	/*SmartDashboard::PutNumber(Name + "crate", crate);
	SmartDashboard::PutNumber(Name + "max encoder rate", maxencrate);
	AngleOutput->Set(angle);*/
	SpeedOutput->Set(SPEED_MULTIPLYER * speed);
	// PIDDrive->SetSetpoint(.5*speed*MaxRate);
}

void SwerveModule::shittydrive(float speed)
{
	if (fabs(speed) < JOYDEADBAND) {
		speed = 0;
	}
	SpeedOutput->Set(speed);
}
void SwerveModule::shittyangle(float speed)
{
	if (fabs(speed) < JOYDEADBAND) {
		speed = 0;
	}
	SmartDashboard::PutNumber(Name + "CANTalonAnalog", AngleOutput->GetAnalogInRaw());
	AngleOutput->Set(speed);
}

void SwerveModule::steer(float angle) {
	//angle = (angle / 360) * 330 + 15;
	// SmartDashboard::PutNumber(Name+"actual I",((PIDAngle->GetI())*1000));
	//angle += Offset;
	//angle += range;

	/*if (angle > MAX) {
		angle -= range;
	} if (angle < MIN) {
		angle += range;
	}*/

	/* if(angle > 300) {
	 	 angle = 300;
	 } if (Angle < 90) {
	 	 angle = 90;
	 }*/

	PIDAngle->Enable();
	//OldSetpoint = angle;
	PIDAngle->SetSetpoint(angle);
	//target = PIDAngle->Get();
}

void SwerveModule::PIDAdjust(float P, float I, float D) {
	PIDAngle->SetPID(P, I, D);
}

bool SwerveModule::AtAngle() {
	return PIDAngle->OnTarget();
}

float SwerveModule::ReadPot() {
	return AnglePotentiometer->PIDGet();
}

void SwerveModule::Reset() {
	PIDAngle->Reset();
}

void SwerveModule::DisablePID() {
	PIDAngle->Disable();
}

void SwerveModule::offSetAdjust(int a, int b) {
	if (a) {
		offSet += 1;
	}

	if (b) {
		offSet -= 1;
	}
}

PIDController* SwerveModule::GetAnglePID() {
	return PIDAngle;
}

void SwerveModule::PIDAuto(float distance) {
	SpeedEncoder->SetPIDSourceParameter(PIDSource::kDistance);
	PIDDriveDistance->Enable();
	PIDDriveDistance->SetSetpoint(distance);
}

bool SwerveModule::GetDistancePID() {
	return PIDDriveDistance->OnTarget();
}

void SwerveModule::DistancePIDDisable() {
	PIDDriveDistance->Disable();
}

void SwerveModule::DashboardLoop() {
	watch.Start();

	if (watch.Get() > .25) {
		SmartDashboard::PutNumber(Name+ " Initial Pot Reading", AnglePotentiometer->PIDGet());
		SmartDashboard::PutNumber(Name + " Potentiometer", AnglePotentiometer->PIDGet());
		SmartDashboard::PutNumber(Name+ " Angle Error", PIDAngle->GetError());
		SmartDashboard::PutNumber(Name + " Angle Setpoint", PIDAngle->GetSetpoint());
		SmartDashboard::PutBoolean(Name + " Angle Target", PIDAngle->OnTarget());
		SmartDashboard::PutNumber(Name + " Angle Error", PIDAngle->GetError());
		SmartDashboard::PutNumber(Name + " Setpoint offset", offSet);
		watch.Stop();
		watch.Reset();
	}
}
