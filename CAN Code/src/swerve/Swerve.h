#ifndef SRC_SWERVE_H_
#define SRC_SWERVE_H_

#include <swerve/PIDValue.h>
#include <swerve/PIDDriveValue.h>
#include <swerve/Autotune.h>
#include "WPILib.h"
#include "SwerveModule.h"
#include <swerve/PIDDistance.h>
#include <Schematic.h>

class Swerve {
private:
	SwerveModule *FrontLeftMod, *FrontRightMod, *BackLeftMod, *BackRightMod;
	PID_ATune *automatic;
	Joystick *Controller;
	float AngleSetpoint, PChangeTest, p, i, d, NAngleSetpoint;
	Timer newtime, *dashboardtime;
	int sign;
	LiveWindow *LW;
	bool turtle;
	int lastturtle;
	bool initialized;
	float SpinTurtle;
	float DriveTurtle;
	bool SpinMode;

public:
	Swerve(Joystick *controller) {
		Controller = controller;
		LW = LiveWindow::GetInstance();
		PIDValue *FrontLeftAngleValues = new PIDValue(PID_FRONT_LEFT_ANGLE);
		PIDValue *FrontRightAngleValues = new PIDValue(PID_FRONT_RIGHT_ANGLE);
		PIDValue *BackLeftAngleValues = new PIDValue(PID_BACK_LEFT_ANGLE);
		PIDValue *BackRightAngleValues = new PIDValue(PID_BACK_RIGHT_ANGLE);
		PIDDriveValue *FrontLeftDriveValues = new PIDDriveValue(.004, 0, 0, 0, .5 / 515.808);
		PIDDriveValue *FrontRightDriveValues = new PIDDriveValue(.004, 0, 0, 0, .5 / 440);
		PIDDriveValue *BackLeftDriveValues = new PIDDriveValue(.004, 0, 0, 0, .5 / 477.852);
		PIDDriveValue *BackRightDriveValues = new PIDDriveValue(.00, 0, 0, 0, .5 / 476.224);
		PIDDistance *FrontLeftDistance = new PIDDistance(PID_FRONT_LEFT_DISTANCE);
		PIDDistance *FrontRightDistance = new PIDDistance(PID_FRONT_RIGHT_DISTANCE);
		PIDDistance *BackLeftDistance = new PIDDistance(PID_BACK_LEFT_DISTANCE);
		PIDDistance *BackRightDistance = new PIDDistance(PID_BACK_RIGHT_DISTANCE);
		automatic = new PID_ATune();

		// (speed,angle,encoder1,encoder2,pot,pidAngle,PIDDrive,name,PIDDistance Values,offset, Max Encoder rate, setpointoffset)
		FrontRightMod = new SwerveModule(9, 6, 0, 0, 1, FrontRightAngleValues, FrontRightDriveValues, FrontRightDistance, "FrontRight", 0, 400, 0);
		FrontLeftMod = new SwerveModule(8, 3, 0, 0, 0, FrontLeftAngleValues, FrontLeftDriveValues, FrontLeftDistance, "FrontLeft", 0, 400, 0);
		BackRightMod = new SwerveModule(5, 2, 0, 0, 3, BackRightAngleValues, BackRightDriveValues, BackRightDistance, "BackRight", 0, 400, 0);
		BackLeftMod = new SwerveModule(4, 1, 0, 0, 4, BackLeftAngleValues, BackLeftDriveValues, BackLeftDistance, "BackLeft", 0, 400, 0);

		sign = 0;
		NAngleSetpoint = 0;
		AngleSetpoint = 90;
		PChangeTest = 0;
		p = 0.0217;
		i = 0.000;
		d = 0.0;
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
