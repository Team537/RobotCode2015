#ifndef SRC_SWERVE_H_
#define SRC_SWERVE_H_

#include <swerve/PIDValue.h>
#include <swerve/PIDDriveValue.h>
#include <swerve/SwerveModule.h>
#include <swerve/PIDDistance.h>
#include <Schematic.h>
#include "WPILib.h"

class Swerve {
private:
	SwerveModule *FrontLeftMod, *FrontRightMod, *BackLeftMod, *BackRightMod;
	Joystick *Controller;
	float AngleSetpoint, PChangeTest, p, i, d, NAngleSetpoint;
	Timer newtime, *dashboardtime;
	int sign;
	LiveWindow *LW;
	bool turtle; // Is 1/2 speed?
	int lastturtle;
	bool initialized;
	float SpinTurtle;
	float DriveTurtle;
	bool SpinMode;

	// Values assigned the selected bots PID's, these are then set into Swerve Module values.
	PIDValue *FrontLeftAngleValues, *FrontRightAngleValues, *BackLeftAngleValues, *BackRightAngleValues;
	PIDDriveValue *FrontLeftDriveValues, *FrontRightDriveValues, *BackLeftDriveValues, *BackRightDriveValues;
	PIDDistance *FrontLeftDistance, *FrontRightDistance, *BackLeftDistance, *BackRightDistance;

public:
	Swerve(Joystick *controller) {
		Controller = controller;
		LW = LiveWindow::GetInstance();

		if (COMPETITION_BOT) {
			FrontLeftAngleValues = new PIDValue(PID_COMPETITION_FRONT_LEFT_ANGLE);
			FrontRightAngleValues = new PIDValue(PID_COMPETITION_FRONT_RIGHT_ANGLE);
			BackLeftAngleValues = new PIDValue(PID_COMPETITION_BACK_LEFT_ANGLE);
			BackRightAngleValues = new PIDValue(PID_COMPETITION_BACK_RIGHT_ANGLE);

			FrontLeftDistance = new PIDDistance(PID_COMPETITION_FRONT_LEFT_DISTANCE);
			FrontRightDistance = new PIDDistance(PID_COMPETITION_FRONT_RIGHT_DISTANCE);
			BackLeftDistance = new PIDDistance(PID_COMPETITION_BACK_LEFT_DISTANCE);
			BackRightDistance = new PIDDistance(PID_COMPETITION_BACK_RIGHT_DISTANCE);
		} else if (PRACTICE_BOT) {
			FrontLeftAngleValues = new PIDValue(PID_PRACTICE_FRONT_LEFT_ANGLE);
			FrontRightAngleValues = new PIDValue(PID_PRACTICE_FRONT_RIGHT_ANGLE);
			BackLeftAngleValues = new PIDValue(PID_PRACTICE_BACK_LEFT_ANGLE);
			BackRightAngleValues = new PIDValue(PID_PRACTICE_BACK_RIGHT_ANGLE);

			FrontLeftDistance = new PIDDistance(PID_PRACTICE_FRONT_LEFT_DISTANCE);
			FrontRightDistance = new PIDDistance(PID_PRACTICE_FRONT_RIGHT_DISTANCE);
			BackLeftDistance = new PIDDistance(PID_PRACTICE_BACK_LEFT_DISTANCE);
			BackRightDistance = new PIDDistance(PID_PRACTICE_BACK_RIGHT_DISTANCE);
		}

		FrontLeftDriveValues = new PIDDriveValue(0.004, 0, 0, 0, 0.50 / 515.808);
		FrontRightDriveValues = new PIDDriveValue(0.004, 0, 0, 0, 0.50 / 440.000);
		BackLeftDriveValues = new PIDDriveValue(0.004, 0, 0, 0, 0.50 / 477.852);
		BackRightDriveValues = new PIDDriveValue(0.00, 0, 0, 0, 0.50 / 476.224);

		// (speed, angle, encoder1, encoder2, pot, pidAngle, PIDDrive, name, PIDDistance Values, offset, Max Encoder rate, setpointoffset)
		FrontRightMod = new SwerveModule(10, 14, 14, 15, 4, FrontRightAngleValues, FrontRightDriveValues, FrontRightDistance, "FrontRight", 0, 400, 0);
		FrontLeftMod = new SwerveModule(11, 15, 16, 17, 5, FrontLeftAngleValues, FrontLeftDriveValues, FrontLeftDistance, "FrontLeft", 0, 400, 0);
		BackRightMod = new SwerveModule(12, 16, 23, 22, 6, BackRightAngleValues, BackRightDriveValues, BackRightDistance, "BackRight", 0, 400, 0);
		BackLeftMod = new SwerveModule(13, 17, 24, 25, 7, BackLeftAngleValues, BackLeftDriveValues, BackLeftDistance, "BackLeft", 0, 400, 0);

		sign = 0;
		NAngleSetpoint = 0;
		AngleSetpoint = 90;
		PChangeTest = 0;
		p = 0.0217;
		i = 0.0000;
		d = 0.0000;
		lastturtle = 0;
		turtle = 0;
		initialized = false;
		dashboardtime = new Timer;
		SpinTurtle = 1;
		DriveTurtle = 1;
		SpinMode = false;
	}

	void Initialize();
	void Run();
	void TestMode();
	void Tune();
	void AutonomousAngle(float FrontLeft, float FrontRight, float BackLeft, float BackRight);
	void AutonomousSpeed(float FrontLeft, float FrontRight, float BackLeft, float BackRight);
	bool OnTarget();
	bool DistanceOnTarget();
	void SetDistance(float FrontLeft, float FrontRight, float BackLeft, float BackRight);
	void DisableDistance();
};

#endif
