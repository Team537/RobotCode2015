#include "WPILib.h"
#include "Schematic.h"
#include "Collector.h"
#include "Hoarder.h"
#include "Stacker.h"
#include "swerve/Swerve.h"

class Robot: public IterativeRobot
{
	Joystick* PrimaryController, *SecondaryController;
	Collector Collect;
	Hoarder   Hoard;
	Stacker   Stack;
private:
	LiveWindow *lw;
	Swerve *swerve;
	CameraServer *camera;

	void RobotInit()
	{
		lw 					= LiveWindow::GetInstance();
		Hoard.initialize();
		camera 				= CameraServer::GetInstance();
		camera->StartAutomaticCapture("cam0");
		PrimaryController 	= new Joystick(0);
		SecondaryController = new Joystick(1);
		swerve 				= new Swerve(PrimaryController);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		swerve->Initialize();
	}

	void TeleopPeriodic()
	{
		swerve->Run();
		Collect.setLeftState(SecondaryController->GetRawButton(LEFT_PROGRESS), SecondaryController->GetRawButton(LEFT_DEGRESS));
		Collect.setRightState(SecondaryController->GetRawButton(RIGHT_PROGRESS), SecondaryController->GetRawButton(RIGHT_DEGRESS));
		Collect.setGrab(SecondaryController->GetRawButton(COL_GRAB_RIGHT_BTN), SecondaryController->GetRawButton(COL_GRAB_LEFT_BTN));
		Collect.setMotors(SecondaryController->GetRawButton(COL_MOTOR_BACKWARDS), SecondaryController->GetRawButton(COL_MOTOR_FORWARD));
		Hoard.hoard(PrimaryController->GetRawButton(HOARD_BTN));
		Stack.Run(SecondaryController->GetRawButton(TOTE_GRAB_BTN), SecondaryController->GetRawButton(AUTOSTACK_BTN), SecondaryController->GetRawAxis(EXTENDER_JOYSTICK), SecondaryController->GetRawAxis(STACKER_JOYSTICK));
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
