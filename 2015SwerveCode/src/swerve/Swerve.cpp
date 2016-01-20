#include "Swerve.h"

void Swerve::Initialize() {
	if (INITIALIZED) { // Don't reinitialize once initialized.
		return;
	}

	NEWTIME.Start();
	ANGLESETPOINT = 90;
	FRONTLEFTMOD->Initialize();
	FRONTRIGHTMOD->Initialize();
	BACKLEFTMOD->Initialize();
	BACKRIGHTMOD->Initialize();
	ANGLESETPOINT = 0.5;
	//AUTOMATIC->InitializeRuntime(BACKRIGHTMOD->ReadPot());
	INITIALIZED = true;
}

/**
 * This function takes controller inputs and uses them to send commands to the swerve modules.
 */
void Swerve::Run() {
	if (CONTROLLER->GetRawButton(2) && !TURTLEBUTTONSTATE) {
		TURTLE = !TURTLE; // Turn 'Turtle' mode on or off depending on its previous state.
	}

	TURTLEBUTTONSTATE = CONTROLLER->GetRawButton(2); // State of button 2 (1 == TRUE, 0 == FALSE).

	if (TURTLE) { // Set to turtle speed multiplier.
		DRIVETURTLE = TURTLE_DRIVE_MULTIPLIER;
		SPINTURTLE = TURTLE_SPIN_MULTIPLIER;
	} else { // Set to normal speed multiplier.
		SPINTURTLE = 1;
		DRIVETURTLE = 1;
	}

	double FWD = CONTROLLER->GetRawAxis(1); // The robot goes forward when joystick is pushed forward.
	double STR = CONTROLLER->GetRawAxis(2); // The robot strafes right when joystick is pushed to the right.
	double RCW = CONTROLLER->GetTwist(); // The robot clockwise when joystick is twisted clockwise.
	//double GRO = GYRO->GetAngle(); // The robot gyroscope angle.

	// It doesn't matter what measurement units are used for L and W, since only the ratios will be used in the calculations.
	double L = 36.5; // The robots wheelbase.
	double W = 22; // The robots trackwidth.
	double R = sqrt((L * L) + (W * W));  // The robot length and width ratio.

	// Field Orientation.
	//STR = -FWD * sin(GRO) + STR * cos(GRO);
	//FWD = FWD * cos(GRO) + STR * sin(GRO);

	double A = STR - RCW * (L / R);
	double B = STR + RCW * (L / R);
	double C = FWD - RCW * (W / R);
	double D = FWD + RCW * (W / R);

	double WheelSpeed1 = sqrt((B * B) + (C * C));
	double WheelAngle1 = atan2(B, C) * 180 / PI;

	double WheelSpeed2 = sqrt((B * B) + (D * D));
	double WheelAngle2 = atan2(B, D) * 180 / PI;

	double WheelSpeed3 = sqrt((A * A) + (D * D));
	double WheelAngle3 = atan2(A, D) * 180 / PI;

	double WheelSpeed4 = sqrt((A * A) + (C * C));
	double WheelAngle4 = atan2(A, C) * 180 / PI;

	// Normalize wheel angles before being used.
	if (WheelAngle1 < 0) WheelAngle1 += 360;
	if (WheelAngle2 < 0) WheelAngle2 += 360;
	if (WheelAngle3 < 0) WheelAngle3 += 360;
	if (WheelAngle4 < 0) WheelAngle4 += 360;

	// Normalize wheel speeds before being used.
	double max = WheelSpeed1;

	if (WheelSpeed2 > max) max = WheelSpeed2;
	if (WheelSpeed3 > max) max = WheelSpeed3;
	if (WheelSpeed4 > max) max = WheelSpeed4;

	if (max > 1) {
		WheelSpeed1 /= max;
		WheelSpeed2 /= max;
		WheelSpeed3 /= max;
		WheelSpeed4 /= max;
	}

	FRONTLEFTMOD->Steer(WheelAngle1);
	FRONTRIGHTMOD->Steer(WheelAngle2);
	BACKLEFTMOD->Steer(WheelAngle3);
	BACKRIGHTMOD->Steer(WheelAngle4);

	if (FRONTRIGHTMOD->PIDAtAngle() && BACKRIGHTMOD->PIDAtAngle() && FRONTLEFTMOD->PIDAtAngle() && BACKLEFTMOD->PIDAtAngle()) { // If all wheels are at the proper angle DRIVE!
		FRONTLEFTMOD->Drive(WheelSpeed1);
		FRONTRIGHTMOD->Drive(WheelSpeed2);
		BACKLEFTMOD->Drive(WheelSpeed3);
		BACKRIGHTMOD->Drive(WheelSpeed4);
	} else { // Otherwise if all wheels are not at angle properly don't drive.
		FRONTLEFTMOD->Drive(0);
		FRONTRIGHTMOD->Drive(0);
		BACKRIGHTMOD->Drive(0);
		BACKLEFTMOD->Drive(0);
	}

	// OLD DRIVE AND SPIN CODE!
	/*float SpinAxis = CONTROLLER->GetRawAxis(2);
	float Magnitude = CONTROLLER->GetMagnitude();
	bool SetSpinMode = fabs(SpinAxis) > JOYSTICK_DEADBAND;

	// Get spin axis.
	if (SetSpinMode || SPINMODE) {
		SPINMODE = true;

		// Set wheel angles so the robot can spin!
		FRONTLEFTMOD->Steer(329.3);
		FRONTRIGHTMOD->Steer(30.7);
		BACKLEFTMOD->Steer(30.7);
		BACKRIGHTMOD->Steer(329.3);

		if (FRONTRIGHTMOD->PIDAtAngle() && BACKRIGHTMOD->PIDAtAngle() && FRONTLEFTMOD->PIDAtAngle() && BACKLEFTMOD->PIDAtAngle() && SetSpinMode) {
			if (COMPETITION_ROBOT) { // Competition Robot.
				FRONTLEFTMOD->Drive(0, (-1 * SPINTURTLE * SpinAxis));
				FRONTRIGHTMOD->Drive(0, (1 * SPINTURTLE * SpinAxis));
				BACKLEFTMOD->Drive(0, (1 * SPINTURTLE * SpinAxis));
				BACKRIGHTMOD->Drive(0, (-1 * SPINTURTLE * SpinAxis));
			} else if (PRACTICE_ROBOT) { // Practice Robot.
				FRONTLEFTMOD->Drive(0, (-1 * SPINTURTLE * SpinAxis));
				FRONTRIGHTMOD->Drive(0, (1 * SPINTURTLE * SpinAxis));
				BACKLEFTMOD->Drive(0, (-1 * SPINTURTLE * SpinAxis));
				BACKRIGHTMOD->Drive(0, (1 * SPINTURTLE * SpinAxis));
			}
		} else {
			FRONTLEFTMOD->Drive(0, 0);
			FRONTRIGHTMOD->Drive(0, 0);
			BACKRIGHTMOD->Drive(0, 0);
			BACKLEFTMOD->Drive(0, 0);
		}
	}

	// Drive the robot if the controller is being moved.
	if (Magnitude > 0.05) {
		SPINMODE = false;

		NEWANGLESETPOINT = CONTROLLER->GetDirectionDegrees();
		NEWANGLESETPOINT = -1 * NEWANGLESETPOINT;
		NEWANGLESETPOINT += 180;

		ANGLESETPOINT = NEWANGLESETPOINT;

		if (ANGLESETPOINT > 330) {
			SIGN = -1;
			ANGLESETPOINT -= 180;
		} else if (ANGLESETPOINT < 30) {
			SIGN = -1;
			ANGLESETPOINT += 180;
		} else {
			SIGN = 1;
		}

		// Move wheel angles to the setpoint.
		FRONTLEFTMOD->Steer(ANGLESETPOINT);
		FRONTRIGHTMOD->Steer(ANGLESETPOINT);
		BACKLEFTMOD->Steer(ANGLESETPOINT);
		BACKRIGHTMOD->Steer(ANGLESETPOINT);

		if (FRONTRIGHTMOD->PIDAtAngle() && BACKRIGHTMOD->PIDAtAngle() && FRONTLEFTMOD->PIDAtAngle() && BACKLEFTMOD->PIDAtAngle()) { // If all wheels are at the proper angle DRIVE!
			FRONTLEFTMOD->Drive(0, (SIGN * DRIVETURTLE * Magnitude));
			FRONTRIGHTMOD->Drive(0, (SIGN * DRIVETURTLE * Magnitude));
			BACKRIGHTMOD->Drive(0, (SIGN * DRIVETURTLE * Magnitude));
			BACKLEFTMOD->Drive(0, (SIGN * DRIVETURTLE * Magnitude));
		} else { // Otherwise if all wheels are not aligned properly don't drive, (STOPS ROBOT FROM TEARINGITSELF APART!)
			FRONTLEFTMOD->Drive(0, 0);
			FRONTRIGHTMOD->Drive(0, 0);
			BACKRIGHTMOD->Drive(0, 0);
			BACKLEFTMOD->Drive(0, 0);
		}
	}

	SmartDashboard::PutBoolean("Turtle Multiplier", TURTLE);
	SmartDashboard::PutNumber("Angle Setpoint", ANGLESETPOINT);
	SmartDashboard::PutNumber("Controller Magnitude", Magnitude);*/
}

void Swerve::TestMode() {
	//LW->AddActuator("Left Back", "Angle", FRONTLEFTMOD->PIDGetAngle());
}

void Swerve::Tune() {
	// Manually drive the motors use for sensor testing.
	FRONTLEFTMOD->Drive(CONTROLLER->GetRawAxis(1));
	FRONTRIGHTMOD->Drive(CONTROLLER->GetRawAxis(1));
	BACKRIGHTMOD->Drive(CONTROLLER->GetRawAxis(1));
	BACKLEFTMOD->Drive(CONTROLLER->GetRawAxis(1));

	// Get Angle based off Button Inputs.
	if (CONTROLLER->GetRawButton(1) == 1) {
		ANGLESETPOINT = 250;
	} else if (CONTROLLER->GetRawButton(2)) {
		ANGLESETPOINT = 185;
	} else {
		ANGLESETPOINT = 165;
	}

	// Get Angle Based off Joystick.
	/*ANGLESETPOINT = Controller->GetDirectionDegrees();
	 ANGLESETPOINT += 180;
	 SmartDashboard::PutNumber("Angle Setpoint", ANGLESETPOINT);
	 SmartDashboard::PutNumber("New Angle Setpoint", NEWANGLESETPOINT);*/

	// Enables AutoStear
	/*FRONTRIGHTMOD->Stear(ANGLESETPOINT);
	 BACKLEFTMOD->Stear(ANGLESETPOINT);
	 BACKRIGHTMOD->Stear(ANGLESETPOINT);
	 FRONTLEFTMOD->Stear(ANGLESETPOINT);*/

	if (NEWTIME.Get() >= 0.20) { // Wait a few milliseconds after the last button press so values don't get added too quickly.
		// Used to increase P in the selected PID.
		if (CONTROLLER->GetRawButton(7) == 1) {
			p -= 0.0001;
			BACKRIGHTMOD->PIDResetAngle();
		} else if (CONTROLLER->GetRawButton(8) == 1) {
			p += 0.0001;
			BACKRIGHTMOD->PIDResetAngle();
		}

		// Used to increase I in the selected PID (NOTE: there are 2 sets of buttons that do the same things but at different paces).
		if (CONTROLLER->GetRawButton(3) == 1) {
			i -= 0.00001;
			BACKRIGHTMOD->PIDResetAngle();
		} else if (CONTROLLER->GetRawButton(5) == 1) {
			i += 0.00001;
			BACKRIGHTMOD->PIDResetAngle();
		} else if (CONTROLLER->GetRawButton(9) == 1) {
			i -= 0.000001;
			BACKRIGHTMOD->PIDResetAngle();
		} else if (CONTROLLER->GetRawButton(10) == 1) {
			i += 0.000001;
			BACKRIGHTMOD->PIDResetAngle();
		}

		// Used to increase D in the selected PID.
		if (CONTROLLER->GetRawButton(11) == 1) {
			d -= 0.0001;
			BACKRIGHTMOD->PIDResetAngle();
		} else if (CONTROLLER->GetRawButton(12) == 1) {
			d += 0.0001;
			FRONTLEFTMOD->PIDResetAngle();
		}

		FRONTLEFTMOD->OffsetAdjust(CONTROLLER->GetRawButton(4), CONTROLLER->GetRawButton(6));
		NEWTIME.Stop();
		NEWTIME.Reset();
		NEWTIME.Start();
		FRONTLEFTMOD->PIDAdjust(p, i, d);
	}
}

/**
 * If all of the wheels are on the Angle target it will return true.
 */
bool Swerve::OnAngleTarget() {
	if (FRONTLEFTMOD->PIDAtAngle() && FRONTRIGHTMOD->PIDAtAngle() && BACKLEFTMOD->PIDAtAngle() && BACKRIGHTMOD->PIDAtAngle()) {
		return true;
	} else {
		return false;
	}
}

/**
 * If the robot is at the Distance target it will return true.
 */
bool Swerve::OnDistanceTarget() {
	if (FRONTLEFTMOD->PIDAtDistance(), FRONTRIGHTMOD->PIDAtDistance(), BACKLEFTMOD->PIDAtDistance(), BACKRIGHTMOD->PIDAtDistance()) {
		return true;
	} else {
		return false;
	}
}

/**
 * Disables Distance.
 */
void Swerve::DisableDistance() {
	FRONTLEFTMOD->PIDDisableDistance();
	FRONTRIGHTMOD->PIDDisableDistance();
	BACKLEFTMOD->PIDDisableDistance();
	BACKRIGHTMOD->PIDDisableDistance();
}

/**
 * Autonomous Wheel Driving Speed.
 */
void Swerve::AutonomousDrive(float frontleft, float frontright, float backleft, float backright) {
	FRONTLEFTMOD->Drive(frontleft);
	FRONTRIGHTMOD->Drive(frontright);
	BACKRIGHTMOD->Drive(backleft);
	BACKLEFTMOD->Drive(backright);
}

/**
 * Autonomous Wheel Angles.
 */
void Swerve::AutonomousSteer(float frontleft, float frontright, float backleft, float backright) {
	FRONTLEFTMOD->Steer(frontleft);
	FRONTRIGHTMOD->Steer(frontright);
	BACKLEFTMOD->Steer(backleft);
	BACKRIGHTMOD->Steer(backright);
}

/**
 * Autonomous Driving Target Distance.
 */
void Swerve::AutonomousSetDistance(float frontleft, float frontright, float backleft, float backright) {
	FRONTLEFTMOD->AutoDrive(frontleft);
	FRONTRIGHTMOD->AutoDrive(frontright);
	BACKLEFTMOD->AutoDrive(backleft);
	BACKRIGHTMOD->AutoDrive(backright);
}
