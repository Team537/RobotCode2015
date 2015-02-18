#ifndef SRC_SWERVE_H_
#define SRC_SWERVE_H_

#include <swerve/PIDValue.h>
#include <swerve/PIDDriveValue.h>
#include <swerve/Autotune.h>
#include "WPILib.h"
#include "SwerveModule.h"
#include <swerve/PIDDistance.h>
#include <Schematic.h>

/* defines for extended board ports
#define FrontLeftSpeed
#define FrontLeftAngle
#define FrontLeftEnc1
#define FrontLeftEnc2
#define FrontLeftPot
#define FrontLeftOffSet
#define EXT6
#define EXT7
#define EXT8
#define EXT9 */

class Swerve
{
private:
	SwerveModule *FrontLeftMod, *FrontRightMod, *BackLeftMod, *BackRightMod;
	PID_ATune *automatic;
	Joystick *Controller;
	float AngleSetpoint, PChangeTest, p, i, d, NAngleSetpoint;
	Timer newtime;
	int sign;
	LiveWindow *LW;
public:
	Swerve(Joystick *controller)
	{
		Controller = controller;
		LW = LiveWindow::GetInstance();
		PIDValue *FrontLeftAngleValues  = new PIDValue(PID_FRONT_LEFT_ANGLE);
		PIDValue *FrontRightAngleValues = new PIDValue(PID_FRONT_RIGHT_ANGLE);
		PIDValue *BackLeftAngleValues   = new PIDValue(PID_BACK_LEFT_ANGLE);
		PIDValue *BackRightAngleValues  = new PIDValue(PID_BACK_RIGHT_ANGLE);
		PIDDriveValue *FrontLeftDriveValues  = new PIDDriveValue(.004, 0, 0,0, .5/515.808);
		PIDDriveValue *FrontRightDriveValues = new PIDDriveValue(.004, 0, 0,0,.5/440);
		PIDDriveValue *BackLeftDriveValues   = new PIDDriveValue(.004, 0, 0,0,.5/477.852);
		PIDDriveValue *BackRightDriveValues  = new PIDDriveValue(.00, 0, 0,0,.5/476.224);
		PIDDistance *FrontLeftDistance = new PIDDistance(.004,0.0,0);
		PIDDistance *FrontRightDistance = new PIDDistance(.004,0.0,0.0);
		PIDDistance *BackLeftDistance = new PIDDistance(.004,0.0,0.0);
		PIDDistance *BackRightDistance = new PIDDistance(.004,0.0,0.0);
		automatic = new PID_ATune();
		///                             (speed,angle,encoder1,encoder2,pot,pidAngle,PIDDrive,name,PIDDistance Values,offset, Max Encoder rate, setpointoffset)
		FrontRightMod = new SwerveModule(10,   14,   14,      15,      4,  FrontRightAngleValues,FrontRightDriveValues,FrontRightDistance,"FrontRight", 0,400,0);
		FrontLeftMod  = new SwerveModule(11,   15,   16,      17,      5,  FrontLeftAngleValues, FrontLeftDriveValues,FrontLeftDistance,"FrontLeft", 0,400,0);
		BackRightMod  = new SwerveModule(12,   16,   23,      22,      6,  BackRightAngleValues, BackRightDriveValues,BackRightDistance,"BackRight", 0,400,0);
		BackLeftMod   = new SwerveModule(13,   17,   24,      25,      7,  BackLeftAngleValues, BackLeftDriveValues,BackLeftDistance,"BackLeft",0,400,0);

		sign = 0;
		NAngleSetpoint = 0;
		AngleSetpoint = 90;
		PChangeTest = 0;
		p = 0.0217;
		i = 0.000;
		d = 0.0;
	}
	void Initialize();
	void Run();
	void TestMode();
	void Tune();
};
#endif
