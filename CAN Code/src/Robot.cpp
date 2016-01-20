#include "WPILib.h"
#include "Schematic.h"
#include "swerve/Swerve.h"
#include "Compressor.h"

class Robot: public IterativeRobot {
private:
	Joystick* controller;
	LiveWindow *lw;
	PowerDistributionPanel *PDP;
	Gyro *gyro;
	Swerve *swerve;

	void RobotInit() {
		controller = new Joystick(0);
		lw = LiveWindow::GetInstance();
		PDP = new PowerDistributionPanel;
		gyro = new Gyro(0);
		swerve = new Swerve(controller);
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
		// PDP.ClearStickyFaults();
		swerve->Initialize();
	}

	void TeleopPeriodic() {
		// Comment this in when you want to run the robot normaly:
		swerve->Run();

		// Comment this in when tuning and comment out code above:
		// swerve->Tune();

		SmartDashboard::PutNumber("Gyro: ", gyro->GetAngle());
	}

	void TestInit() {
	}

	void TestPeriodic() {
	}
};

START_ROBOT_CLASS(Robot);
