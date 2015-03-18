#include "WPILib.h"
#include "Schematic.h"
#include "Collector.h"
#include "Hoarder.h"
#include "Stacker.h"
#include "swerve/Swerve.h"
#include "Compressor.h"
#include "SimpleAuto.h"
#include "AutoSelect.h"
#include "SimpleCanAndToteAuto.h"
#include "AutonomousCan.h"
#include "AutonomousTote.cpp"

class Robot: public IterativeRobot
{

private:
	Joystick* PrimaryController, *SecondaryController;
	Hoarder  * Hoard;
	Stacker   *Stack;
	Collector *Collect;
	//CompressorManager compressor;
	PowerDistributionPanel PDP;
	LiveWindow *lw;
	Swerve *swerve;
	//SendableChooser *AutoSelect;
	SimpleAutonomous *SimpleAuto;
	CameraServer *camera;
	SimpleCanAndToteAutonomous *SingleTote;
	AutonomousCan *CanAuto;
	AutonomousTote *TripleTote;

	void RobotInit()
	{
		lw 					= LiveWindow::GetInstance();
		camera 				= CameraServer::GetInstance();
		camera->StartAutomaticCapture("cam0");
		PrimaryController 	= new Joystick(0);
		SecondaryController = new Joystick(1);
		swerve 				= new Swerve(PrimaryController);
		Collect = new Collector();
		Stack = new Stacker(Collect);
		Hoard = new Hoarder();
		SimpleAuto = new SimpleAutonomous(swerve);
		SingleTote = new SimpleCanAndToteAutonomous(swerve , Stack);
		CanAuto = new AutonomousCan(Hoard, swerve);
		TripleTote = new AutonomousTote(swerve, Collect, Stack);
		//AutoSelect->AddDefault("SimpleAuto", &SimpleAuto);
	}

	void AutonomousInit()
	{
		//compressor.checkCompressor();

	}

	void AutonomousPeriodic()
	{
		//compressor.checkCompressor();
		//SimpleAuto->Run();
		//CanAuto->Run(3);
		SingleTote->Run();
		//TripleTote->ToteRun();

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
		Collect->setMotors(PrimaryController->GetRawButton(5), PrimaryController->GetRawButton(6), PrimaryController->GetRawButton(8), PrimaryController->GetRawButton(7));
		Hoard->hoard(PrimaryController->GetRawButton(HOARD_BTN));
		//Stack->StackLeft(SecondaryController->GetRawButton(5), SecondaryController->GetRawButton(7));
		//Stack->StackRight(SecondaryController->GetRawButton(6), SecondaryController->GetRawButton(8));
		//Stack->Tune(PrimaryController->GetRawButton(8),PrimaryController->GetRawButton(7),PrimaryController->GetRawButton(5),PrimaryController->GetRawButton(3),PrimaryController->GetRawButton(10),PrimaryController->GetRawButton(9),PrimaryController->GetRawButton(12),PrimaryController->GetRawButton(11),PrimaryController->GetRawButton(1), PrimaryController->GetRawButton(2));
		//Stack->CollectorIn(Collect.getGrableft(), Collect.getGrabright());
		//Stack->CollectorDanger(Collect.getGrableft(), Collect.getGrabright());
		Stack->ManualStacker(SecondaryController->GetRawButton(SETPOINT_UP), SecondaryController->GetRawButton(SETPOINT_DOWN));
		Stack->Extender(SecondaryController->GetRawButton(EXTENDER_IN), SecondaryController->GetRawButton(EXTENDER_OUT),SecondaryController->GetRawButton(AUTOMATIC), SecondaryController->GetRawButton(MANUAL), SecondaryController->GetRawButton(12));
		Stack->Grab(SecondaryController->GetRawButton(TOTE_GRAB_BTN));
		Stack->AutoStacker(SecondaryController->GetRawButton(AUTOSTACK_BTN), SecondaryController->GetRawButton(LEVEL_UP), SecondaryController->GetRawButton(LEVEL_DOWN), SecondaryController->GetRawButton(BUTTON_CAN));
		Collect->setState(PrimaryController->GetRawButton(4), SecondaryController->GetRawButton(RIGHT_VERTICAL), Stack->DangerLevel());
		Collect->setGrab(PrimaryController->GetRawButton(3), SecondaryController->GetRawAxis(COL_GRAB_LEFT_AXIS), Stack->DangerLevel());
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
