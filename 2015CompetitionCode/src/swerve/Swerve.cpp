#include "Swerve.h"
#include "SwerveModule.h"

void Swerve::Initialize() {
	if (initialized) {
		return;
	}

	initialized = true;
	newtime.Start();
	AngleSetpoint = 90;
	FrontLeftMod->Initialize();
	FrontRightMod->Initialize();
	BackLeftMod->Initialize();
	BackRightMod->Initialize();
	AngleSetpoint = .5;
	automatic->InitializeRuntime(BackRightMod->ReadPot());
}

void Swerve::Run() {
	/*FrontLeftMod->drive(.5*Controller->GetRawAxis(0),.5*Controller->GetRawAxis(1));
	FrontRightMod->drive(.5*Controller->GetRawAxis(0),.5*Controller->GetRawAxis(1));
	BackRightMod->drive(.5*Controller->GetRawAxis(0),.5*Controller->GetRawAxis(1));
	BackLeftMod->drive(.5*Controller->GetRawAxis(0),.5*Controller->GetRawAxis(1));*/

	if (Controller->GetRawButton(2) && lastturtle == 0) {
		turtle = !turtle;
	}

	lastturtle = Controller->GetRawButton(2);

	// Create Turtle Speed Variables.

	// Set Turtle Speeds

	if (turtle) {
		SpinTurtle = .8;
		DriveTurtle = .7;
	}

	if (!turtle) {
		SpinTurtle = 1;
		DriveTurtle = 1;
	}

	float SpinAxis = Controller->GetRawAxis(2);
	SmartDashboard::PutBoolean("Turtle Mode", turtle);
	bool SetSpinMode = fabs(SpinAxis) > .25;

	// Get Spin Axis.
	if (SetSpinMode || SpinMode) {
		SpinMode = true;
		FrontLeftMod->AutoDrive(329.3);
		FrontRightMod->AutoDrive(30.7);
		BackLeftMod->AutoDrive(30.7);
		BackRightMod->AutoDrive(329.3);

		if (FrontRightMod->AtAngle() && BackRightMod->AtAngle() && FrontLeftMod->AtAngle() && BackLeftMod->AtAngle() && SetSpinMode) {
			// Comp
			BackRightMod->drive(0, -1 * SpinTurtle * SpinAxis);
			BackLeftMod->drive(0, 1 * SpinTurtle * SpinAxis);

			// Practice
			/*BackRightMod->drive(0,1*SpinTurtle*SpinAxis);
			BackLeftMod->drive(0,-1*SpinTurtle*SpinAxis);*/

			// These are Identical In Both Bots
			FrontLeftMod->drive(0, -1 * SpinTurtle * SpinAxis);
			FrontRightMod->drive(0, SpinTurtle * SpinAxis);
		} else {
			FrontLeftMod->drive(0, 0);
			FrontRightMod->drive(0, 0);
			BackRightMod->drive(0, 0);
			BackLeftMod->drive(0, 0);
		}
	}

	if (Controller->GetMagnitude() > .05) {
		SpinMode = false;
		NAngleSetpoint = Controller->GetDirectionDegrees();
		NAngleSetpoint = NAngleSetpoint * (-1);
		NAngleSetpoint += 180;
		AngleSetpoint = (NAngleSetpoint);
		SmartDashboard::PutNumber("Magnitude", Controller->GetMagnitude());

		if (AngleSetpoint > 330) {
			sign = -1;
			AngleSetpoint -= 180;
		} else if (AngleSetpoint < 30) {
			sign = -1;
			AngleSetpoint += 180;
		} else {
			sign = 1;
		}

		SmartDashboard::PutNumber("Angle Setpoint", AngleSetpoint);
		FrontRightMod->AutoDrive(AngleSetpoint);
		BackLeftMod->AutoDrive(AngleSetpoint);
		BackRightMod->AutoDrive(AngleSetpoint);
		FrontLeftMod->AutoDrive(AngleSetpoint);
		float Magnitude = Controller->GetMagnitude();

		if (FrontRightMod->AtAngle() && BackRightMod->AtAngle() && FrontLeftMod->AtAngle() && BackLeftMod->AtAngle()) {
			FrontLeftMod->drive(0, DriveTurtle * sign * Magnitude);
			FrontRightMod->drive(0, DriveTurtle * sign * Magnitude);
			BackRightMod->drive(0, DriveTurtle * sign * Magnitude);
			BackLeftMod->drive(0, DriveTurtle * sign * Magnitude);
		} else {
			FrontLeftMod->drive(0, 0);
			FrontRightMod->drive(0, 0);
			BackRightMod->drive(0, 0);
			BackLeftMod->drive(0, 0);
		}
	}

}

void Swerve::TestMode() {
	LW->AddActuator("Left Back", "Angle", FrontLeftMod->GetAnglePID());
}

void Swerve::Tune() {
	// Manually drive the motors use for sensor testing.
	FrontLeftMod->drive(Controller->GetRawAxis(0), Controller->GetRawAxis(1));
	FrontRightMod->drive(Controller->GetRawAxis(0), Controller->GetRawAxis(1));
	BackRightMod->drive(Controller->GetRawAxis(0), Controller->GetRawAxis(1));
	BackLeftMod->drive(Controller->GetRawAxis(0), Controller->GetRawAxis(1));

	// Get Angle based off Button Inputs.
	if (Controller->GetRawButton(1) == 1) {
		AngleSetpoint = 250;
	} else if (Controller->GetRawButton(2)) {
		AngleSetpoint = 185;
	} else {
		AngleSetpoint = 165;
	}

	// Get Angle Based off Joystick.
	/*AngleSetpoint = Controller->GetDirectionDegrees();
	AngleSetpoint += 180;
	SmartDashboard::PutNumber("Angle Setpoint", AngleSetpoint);
	SmartDashboard::PutNumber("N Angle Setpoint", NAngleSetpoint);*/

	// Enables AutoDrive

	/*FrontRightMod->AutoDrive(AngleSetpoint);
	BackLeftMod->AutoDrive(AngleSetpoint);
	BackRightMod->AutoDrive(AngleSetpoint);
	FrontLeftMod->AutoDrive(AngleSetpoint);*/

	if (newtime.Get() >= .25) {
		if (Controller->GetRawButton(7) == 1) {
			p -= .0001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(8) == 1) {
			p += .0001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(9) == 1) {
			i -= .000001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(10) == 1) {
			i += .000001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(3) == 1) {
			i -= .00001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(5) == 1) {
			i += .00001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(11) == 1) {
			d -= .0001;
			BackRightMod->Reset();
		}

		if (Controller->GetRawButton(12) == 1) {
			d += .0001;
			FrontLeftMod->Reset();
		}

		FrontLeftMod->offSetAdjust(Controller->GetRawButton(4), Controller->GetRawButton(6));
		newtime.Stop();
		newtime.Reset();
		newtime.Start();
		FrontLeftMod->PIDAdjust(p, i, d);
	}
}

void Swerve::AutonomousAngle(float FrontLeft, float FrontRight, float BackLeft, float BackRight) {
	FrontLeftMod->AutoDrive(FrontLeft);
	FrontRightMod->AutoDrive(FrontRight);
	BackLeftMod->AutoDrive(BackLeft);
	BackRightMod->AutoDrive(BackLeft);
}

void Swerve::AutonomousSpeed(float FrontLeft, float FrontRight, float BackLeft, float BackRight) {
	FrontLeftMod->drive(0, FrontLeft);
	FrontRightMod->drive(0, FrontRight);
	BackRightMod->drive(0, BackLeft);
	BackLeftMod->drive(0, BackRight);
}

bool Swerve::OnTarget() {
	if (FrontLeftMod->AtAngle() && FrontRightMod->AtAngle() && BackLeftMod->AtAngle() && BackRightMod->AtAngle()) {
		return true;
	} else {
		return false;
	}
}

bool Swerve::DistanceOnTarget() {
	if (FrontLeftMod->GetDistancePID(), FrontRightMod->GetDistancePID(), BackLeftMod->GetDistancePID(), BackRightMod->GetDistancePID()) {
		return true;
	} else {
		return false;
	}
}

void Swerve::SetDistance(float FrontLeft, float FrontRight, float BackLeft, float BackRight) {
	FrontLeftMod->PIDAuto(FrontLeft);
	FrontRightMod->PIDAuto(FrontRight);
	BackLeftMod->PIDAuto(BackLeft);
	BackRightMod->PIDAuto(BackRight);
}

void Swerve::DisableDistance() {
	FrontLeftMod->DistancePIDDisable();
	FrontRightMod->DistancePIDDisable();
	BackLeftMod->DistancePIDDisable();
	BackRightMod->DistancePIDDisable();
}
