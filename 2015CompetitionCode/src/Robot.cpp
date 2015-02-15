#include "WPILib.h"
#include "Schematic.h"
#include "Collector.h"
#include "Hoarder.h"
#include "Stacker.h"
#include "swerve/Swerve.h"
#include "Compressor.h"

class Robot: public IterativeRobot
{
	Joystick* PrimaryController, *SecondaryController;
	Collector Collect;
	Hoarder   Hoard;
	Stacker   Stack;
	CompressorManager compressor;
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
		//compressor.checkCompressor();
	}

	void AutonomousPeriodic()
	{
		//compressor.checkCompressor();
	}

	void TeleopInit()
	{
		swerve->Initialize();
		//compressor.checkCompressor();
	}

	void TeleopPeriodic()
	{
		//compressor.checkCompressor();
		swerve->Run();
		Collect.setLeftState(SecondaryController->GetRawButton(LEFT_TOGGLE), SecondaryController->GetRawButton(LEFT_ORIENT));
		Collect.setRightState(SecondaryController->GetRawButton(RIGHT_TOGGLE), SecondaryController->GetRawButton(RIGHT_ORIENT));
		Collect.setGrab(SecondaryController->GetRawAxis(COL_GRAB_RIGHT_AXIS), SecondaryController->GetRawAxis(COL_GRAB_LEFT_AXIS));
		Collect.setMotors(SecondaryController->GetRawAxis(COL_MOTOR_LEFT), SecondaryController->GetRawButton(COL_MOTOR_RIGHT));
		Hoard.hoard(PrimaryController->GetRawButton(HOARD_BTN));
		//Stack.Run(SecondaryController->GetRawButton(TOTE_GRAB_BTN), SecondaryController->GetRawButton(AUTOSTACK_BTN),  SecondaryController->GetPOV(),SecondaryController->GetRawButton(STACKER_UP),SecondaryController->GetRawButton(STACKER_DOWN), SecondaryController->GetRawButton(EXTENDER_OUT),SecondaryController->GetRawButton(EXTENDER_IN));
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
