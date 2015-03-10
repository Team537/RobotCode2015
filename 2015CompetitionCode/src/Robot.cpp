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
	Stacker   *Stack;
	//CompressorManager compressor;
	PowerDistributionPanel PDP;
private:
	LiveWindow *lw;
	Swerve *swerve;
	//CameraServer *camera;

	void RobotInit()
	{
		lw 					= LiveWindow::GetInstance();
		//Hoard.initialize();
		//camera 				= CameraServer::GetInstance();
		//camera->StartAutomaticCapture("cam0");
		PrimaryController 	= new Joystick(0);
		SecondaryController = new Joystick(1);
		swerve 				= new Swerve(PrimaryController);
		Stack = new Stacker();
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
		PDP.ClearStickyFaults();
		swerve->Initialize();
		//compressor.checkCompressor();
		Stack->init();

	}

	void TeleopPeriodic()
	{
		//compressor.checkCompressor();
		swerve->Run();
		//swerve->Tune();
		Collect.setState(SecondaryController->GetRawButton(LEFT_VERTICAL), SecondaryController->GetRawButton(RIGHT_VERTICAL));
		Collect.setGrab(SecondaryController->GetRawAxis(COL_GRAB_RIGHT_AXIS), SecondaryController->GetRawAxis(COL_GRAB_LEFT_AXIS), Stack->DangerLevel());
		Collect.setMotors(SecondaryController->GetRawAxis(COL_MOTOR_LEFT), SecondaryController->GetRawAxis(COL_MOTOR_RIGHT));
		Hoard.hoard(PrimaryController->GetRawButton(HOARD_BTN));
		//Stack.Run(SecondaryController->GetRawButton(TOTE_GRAB_BTN), SecondaryController->GetRawButton(AUTOSTACK_BTN),  SecondaryController->GetPOV(),SecondaryController->GetRawButton(STACKER_UP),SecondaryController->GetRawButton(STACKER_DOWN), SecondaryController->GetRawButton(EXTENDER_OUT),SecondaryController->GetRawButton(EXTENDER_IN));
		//Stack->StackLeft(SecondaryController->GetRawButton(5), SecondaryController->GetRawButton(7));
		//Stack->StackRight(SecondaryController->GetRawButton(6), SecondaryController->GetRawButton(8));
		//Stack->Tune(PrimaryController->GetRawButton(8),PrimaryController->GetRawButton(7),PrimaryController->GetRawButton(5),PrimaryController->GetRawButton(3),PrimaryController->GetRawButton(10),PrimaryController->GetRawButton(9),PrimaryController->GetRawButton(12),PrimaryController->GetRawButton(11),PrimaryController->GetRawButton(1), PrimaryController->GetRawButton(2));
		Stack->ManualStacker(SecondaryController->GetRawButton(SETPOINT_UP), SecondaryController->GetRawButton(SETPOINT_DOWN));
		Stack->Extender(SecondaryController->GetRawButton(EXTENDER_IN), SecondaryController->GetRawButton(EXTENDER_OUT),SecondaryController->GetRawButton(AUTOMATIC), SecondaryController->GetRawButton(MANUAL));
		Stack->Grab(SecondaryController->GetRawButton(TOTE_GRAB_BTN));
		Stack->AutoStacker(SecondaryController->GetRawButton(AUTOSTACK_BTN), SecondaryController->GetRawButton(LEVEL_UP), SecondaryController->GetRawButton(LEVEL_DOWN));
		SmartDashboard::PutNumber("POV", SecondaryController->GetPOV());
		SmartDashboard::PutNumber("Right Stacker Motor Current",  PDP.GetCurrent(10));
		SmartDashboard::PutNumber("Left Stacker Motor Current",  PDP.GetCurrent(9));
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
