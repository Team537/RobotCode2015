#include <swerve/SwerveModule.h>

void SwerveModule::Initialize() {
	PIDAngle->Disable();
	PIDAngle->Reset();
	PIDAngle->Disable();
	SPEEDENCODER->Reset();

	//SmartDashboard::PutData("Angle PID", PIDAngle);
}

/**
 * Moves the wheels forward at the provided speed, limited by the max drive speed multiplier.
 */
void SwerveModule::Drive(float speed) {
	SPEEDENCODER->SetPIDSourceType(PIDSourceType::kRate);

	if (fabs(speed) < JOYSTICK_DEADBAND) {
		speed = 0;
	}

	//AngleOutput->Set(angle);
	SPEEDOUTPUT->Set(DRIVE_MULTIPLIER * speed);
	//SmartDashboard::PutNumber((NAME + "POT"), ANGLEPOT->PIDGet());
	//PIDDrive->SetSetpoint(0.5 * MAXRATE * speed);
	SmartDashboard::PutNumber(NAME + "SpeedEncoder", SPEEDENCODER->GetRate());
	SmartDashboard::PutNumber(NAME + "AnglePOT", ANGLEPOT->Get());
	//SmartDashboard::PutNumber("Angle IO", angle);
	//SmartDashboard::PutNumber("Speed IO", speed);
}

/**
 * Autonomously drives the robot a set distance.
 */
void SwerveModule::AutoDrive(float distance) {
	SPEEDENCODER->SetPIDSourceType(PIDSourceType::kDisplacement);
	PIDDriveDistance->Enable();
	PIDDriveDistance->SetSetpoint(distance);

	SmartDashboard::PutNumber((NAME + "PID Error Distance"), PIDDriveDistance->GetError());
}

/**
 * Turns the wheels to the provided angle.
 */
void SwerveModule::Steer(float angle) {
	angle = (angle / 360) * 330 + 15;
	angle += OFFSET;
	angle += RANGE;

	if (angle > MAX) {
		angle -= RANGE;
	}

	if (angle < MIN) {
		angle += RANGE;
	}

	//SmartDashboard::PutNumber((NAME + "Accurate I"), (PIDAngle->GetI() * 1000));
	SmartDashboard::PutNumber((NAME + "Angle Setpoint Precap"), angle);

	/*if(Angle > 300) {
	 	 Angle = 300;
	 } if (Angle < 90) {
	 	 Angle = 90;
	 }*/

	PIDAngle->Enable();
	PIDAngle->SetSetpoint(angle);
	TARGET = PIDAngle->Get();
	OLDSETPOINT = angle;

	//SmartDashboard::PutNumber((NAME + "PID Output"), TARGET);
	SmartDashboard::PutNumber((NAME + "Angle POT"), ANGLEPOT->PIDGet());
	//SmartDashboard::PutNumber((NAME + "Angle Error1"), PIDAngle->GetError());
	SmartDashboard::PutNumber((NAME + "Angle Setpoint"), PIDAngle->GetSetpoint());
	//SmartDashboard::PutBoolean((NAME + "Angle Target"), PIDAngle->OnTarget());
	SmartDashboard::PutNumber((NAME + "Angle Error2"), PIDAngle->GetError());
}

/**
 * Adjust the setpoint to cooperate with the given wheel offset.
 */
void SwerveModule::OffsetAdjust(int a, int b) {
	if (a) {
		SETPOINTOFFSET += 1;
	}

	if (b) {
		SETPOINTOFFSET -= 1;
	}
}

/**
 * Live PID adjustment.
 */
void SwerveModule::PIDAdjust(float P, float I, float D) {
	//SmartDashboard::PutNumber((NAME + "P"), (PIDAngle->GetP() * 1000));
	//SmartDashboard::PutNumber((NAME + "I"), (PIDAngle->GetI() * 1000));
	//SmartDashboard::PutNumber((NAME + "D"), (PIDAngle->GetD() * 1000));
	SmartDashboard::PutNumber((NAME + "Setpoint Offset"), SETPOINTOFFSET);

	PIDAngle->SetPID(P, I, D);
}

/**
 * Returns the Angle POT reading.
 */
float SwerveModule::POTReadAngle() {
	//SmartDashboard::PutNumber((NAME + "Initial Pot Reading"), ANGLEPOT->PIDGet());

	return ANGLEPOT->PIDGet();
}

/**
 * Returns the Angle PID value.
 */
PIDController* SwerveModule::PIDGetAngle() {
	return PIDAngle;
}

/**
 * Is the wheel at the target angle?
 */
bool SwerveModule::PIDAtAngle() {
	return PIDAngle->OnTarget();
}

/**
 * Disable the Angle PID.
 */
void SwerveModule::PIDDisableAngle() {
	PIDAngle->Disable();
}

/**
 * Reset the Angle PID.
 */
void SwerveModule::PIDResetAngle() {
	PIDAngle->Reset();
}

/**
 * Is the Distance PID on its target?.
 */
bool SwerveModule::PIDAtDistance() {
	return PIDDriveDistance->OnTarget();
}

/**
 * Disable the Distance PID.
 */
void SwerveModule::PIDDisableDistance() {
	PIDDriveDistance->Disable();
}

/**
 * Updates Smart Dashboard readings as values change.
 */
void SwerveModule::DashboardLoop() {
	WATCH.Start();

	if (WATCH.Get() > 0.25) { // How Frequently Dashboard Values Update.
		SmartDashboard::PutBoolean("Distance On Target", PIDDriveDistance->OnTarget());
		//SmartDashboard::PutNumber((NAME + "Initial Pot Reading"), ANGLEPOT->PIDGet());
		//SmartDashboard::PutNumber((NAME + "P"), (PIDAngle->GetP() * 1000));
		//SmartDashboard::PutNumber((NAME + "I"), (PIDAngle->GetI() * 1000));
		//SmartDashboard::PutNumber((NAME + "D"), (PIDAngle->GetD() * 1000));
		//SmartDashboard::PutNumber((NAME + "PID Output"), TARGET);
		SmartDashboard::PutNumber((NAME + "Angle POT"), ANGLEPOT->PIDGet());
		//SmartDashboard::PutNumber((NAME + "Angle Error"), PIDAngle->GetError());
		SmartDashboard::PutNumber((NAME + "Angle Setpoint"), PIDAngle->GetSetpoint());
		//SmartDashboard::PutBoolean((NAME + "Angle Target"), PIDAngle->OnTarget());
		SmartDashboard::PutNumber((NAME + "Angle Error2"), PIDAngle->GetError());
		SmartDashboard::PutNumber((NAME + "Setpoint Offset"), SETPOINTOFFSET);
		//SmartDashboard::PutNumber((NAME + "Encoder"), SPEEDENCODER->GetRate());
		//SmartDashboard::PutNumber((NAME + "POT"), ANGLEPOT->Get());
		//SmartDashboard::PutNumber((NAME + "Angle IO"), angle);
		//SmartDashboard::PutNumber((NAME + "Speed IO"), speed);

		WATCH.Stop();
		WATCH.Reset();
	}
}
