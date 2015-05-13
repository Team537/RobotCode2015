#include <swerve/Swerve.h>
#include <Schematic.h>
#include "WPILib.h"

class Robot: public IterativeRobot {
private:
	Joystick *PrimaryController, *SecondaryController;
	//Gyro *AutoGyro;
	PowerDistributionPanel *PDP;
	LiveWindow *lw;
	Swerve *swerve;
	//CameraServer *camera;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		//camera = CameraServer::GetInstance();
		PDP = new PowerDistributionPanel;
		//camera->StartAutomaticCapture("cam0");
		PrimaryController = new Joystick(0);
		SecondaryController = new Joystick(1);
		//AutoGyro = new Gyro(0);
		swerve = new Swerve(PrimaryController);

		//AutoGyro->InitGyro();
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
		swerve->Initialize();
	}

	void TeleopPeriodic() {
		swerve->Run();
	}

	void TestInit() {
		swerve->Initialize();
	}

	void TestPeriodic() {
		// swerve->Tune();
	}
};

START_ROBOT_CLASS(Robot);
