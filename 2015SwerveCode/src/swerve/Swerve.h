#ifndef SWERVE_H
#define SWERVE_H

#include <WPILib.h>
#include <Schematic.h>
#include <swerve/PIDDistance.h>
#include <swerve/PIDDriveValue.h>
#include <swerve/PIDValue.h>
#include <swerve/SwerveModule.h>
#include <swerve/SwerveModule.h>

class Swerve {
private:
	SwerveModule *FRONTLEFTMOD, *FRONTRIGHTMOD, *BACKLEFTMOD, *BACKRIGHTMOD;
	//PIDAutotune *automatic;
	Joystick *CONTROLLER;
	LiveWindow *LW;
	Gyro *GYRO;
	Timer NEWTIME, *DASHBOARDTIME;
	bool INITIALIZED;

	float ANGLESETPOINT, NEWANGLESETPOINT;
	bool SPINMODE;
	int SIGN;
	float p, i, d; // Used in PID tuning.

	bool TURTLE, TURTLEBUTTONSTATE;
	float DRIVETURTLE, SPINTURTLE; // Drive & Spin speed multiplier, higher the value the faster the robot.

public:
	/**
	 * Main Swerve Constructor. Needs to be given the robots LiveWindow and main Driving Controller.
	 */
	Swerve(Joystick *controller, LiveWindow *window, Gyro *gyro) {
		CONTROLLER = controller;
		LW = window;
		GYRO = gyro;
		DASHBOARDTIME = new Timer;
		INITIALIZED = false;

		PIDValue *frontleftanglevalues, *frontrightanglevalues, *backleftanglevalues, *backrightanglevalues;
		PIDDriveValue *frontleftdrivevalues, *frontrightdrivevalues, *backleftdrivevalues, *backrightdrivevalues;
		PIDDistance *frontleftdistance, *frontrightdistance, *backleftdistance, *backrightdistance;

		if (COMPETITION_ROBOT) {
			frontleftanglevalues = new PIDValue(PID_COMPETITION_FRONT_LEFT_ANGLE);
			frontrightanglevalues = new PIDValue(PID_COMPETITION_FRONT_RIGHT_ANGLE);
			backleftanglevalues = new PIDValue(PID_COMPETITION_BACK_LEFT_ANGLE);
			backrightanglevalues = new PIDValue(PID_COMPETITION_BACK_RIGHT_ANGLE);

			// TODO DriveValue?
			frontleftdrivevalues = new PIDDriveValue(0.004, 0, 0, 0, (0.5 / 515.808));
			frontrightdrivevalues = new PIDDriveValue(0.004, 0, 0, 0, (0.5 / 440.000));
			backleftdrivevalues = new PIDDriveValue(0.004, 0, 0, 0, (0.5 / 477.852));
			backrightdrivevalues = new PIDDriveValue(0.000, 0, 0, 0, (0.5 / 476.224));

			frontleftdistance = new PIDDistance(PID_COMPETITION_FRONT_LEFT_DISTANCE);
			frontrightdistance = new PIDDistance(PID_COMPETITION_FRONT_RIGHT_DISTANCE);
			backleftdistance = new PIDDistance(PID_COMPETITION_BACK_LEFT_DISTANCE);
			backrightdistance = new PIDDistance(PID_COMPETITION_BACK_RIGHT_DISTANCE);
		} else if (PRACTICE_ROBOT) {
			frontleftanglevalues = new PIDValue(PID_PRACTICE_FRONT_LEFT_ANGLE);
			frontrightanglevalues = new PIDValue(PID_PRACTICE_FRONT_RIGHT_ANGLE);
			backleftanglevalues = new PIDValue(PID_PRACTICE_BACK_LEFT_ANGLE);
			backrightanglevalues = new PIDValue(PID_PRACTICE_BACK_RIGHT_ANGLE);

			// TODO DriveValue?
			frontleftdrivevalues = new PIDDriveValue(0.004, 0, 0, 0, (0.5 / 515.808));
			frontrightdrivevalues = new PIDDriveValue(0.004, 0, 0, 0, (0.5 / 440.000));
			backleftdrivevalues = new PIDDriveValue(0.004, 0, 0, 0, (0.5 / 477.852));
			backrightdrivevalues = new PIDDriveValue(0.000, 0, 0, 0, (0.5 / 476.224));

			frontleftdistance = new PIDDistance(PID_PRACTICE_FRONT_LEFT_DISTANCE);
			frontrightdistance = new PIDDistance(PID_PRACTICE_FRONT_RIGHT_DISTANCE);
			backleftdistance = new PIDDistance(PID_PRACTICE_BACK_LEFT_DISTANCE);
			backrightdistance = new PIDDistance(PID_PRACTICE_BACK_RIGHT_DISTANCE);
		}

		FRONTLEFTMOD = new SwerveModule(11, 15, 16, 17, 5, frontleftanglevalues, frontleftdrivevalues, frontleftdistance, "FrontLeft", 400, 0);
		FRONTRIGHTMOD = new SwerveModule(12, 16, 23, 22, 6, frontrightanglevalues, frontrightdrivevalues, frontrightdistance, "FrontRight", 400, 0);
		BACKLEFTMOD = new SwerveModule(10, 14, 14, 15, 4, backleftanglevalues, backleftdrivevalues, backleftdistance, "BackLeft", 400, 0);
		BACKRIGHTMOD = new SwerveModule(13, 17, 24, 25, 7, backrightanglevalues, backrightdrivevalues, backrightdistance, "BackRight", 400, 0);

		ANGLESETPOINT = 90;
		NEWANGLESETPOINT = 0;
		SPINMODE = false;
		SIGN = 0;
		
		p = 0.0217;
		i = 0.0000;
		d = 0.0000;

		TURTLE = false;
		TURTLEBUTTONSTATE = 0;
		DRIVETURTLE = 1;
		SPINTURTLE = 1;
	}

	void Initialize();
	void Run();
	void TestMode();
	void Tune();
	bool OnAngleTarget();
	bool OnDistanceTarget();
	void DisableDistance();
	void AutonomousDrive(float frontleft, float frontright, float backleft, float backright);
	void AutonomousSteer(float frontleft, float frontright, float backleft, float backright);
	void AutonomousSetDistance(float frontleft, float frontright, float backleft, float backright);
};

// molly = :)

#endif
