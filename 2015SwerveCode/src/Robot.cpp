#include <WPILib.h>
#include <Schematic.h>
#include <swerve/Swerve.h>

/**
 * --- Formatting Rules: ---
 *
 * Schematic Variables: All characters capitalized, and between words put underscores EXAMPLE: (EXAMPLE_SCHEMATIC).
 * Header Variables: All characters capitalized, and between words put nothing EXAMPLE: (EXAMPLEHEADER).
 * Function Arguments: All characters lowercased, and between words put nothing EXAMPLE: (exampleargument).
 * Function Local Variables: Beginning of each word should be capitalized, and between words put nothing EXAMPLE: (ExampleVariable).
 */

class Robot: public IterativeRobot {
private:
	Joystick *CONTROLLER;
	LiveWindow *LW;
	Gyro *GYRO;
	Swerve *SWERVE;

	void RobotInit() {
		CONTROLLER = new Joystick(0);
		LW = LiveWindow::GetInstance();
		GYRO = new Gyro(0);
		GYRO->InitGyro();
		SWERVE = new Swerve(CONTROLLER, LW, GYRO);
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
		SWERVE->Initialize();
	}

	void TeleopPeriodic() {
		if (TUNING_DRIVE_PID) {
			SWERVE->Tune();
		} else {
			SWERVE->Run();
		}

		SmartDashboard::PutNumber("Gyro", GYRO->GetAngle());
	}

	// TODO: Could we devote test mode to PID tuning?
	void TestInit() {
		SWERVE->Initialize();
	}

	void TestPeriodic() {
		//swerve->Tune();
	}
};

START_ROBOT_CLASS(Robot);
