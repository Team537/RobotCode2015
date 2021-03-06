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
#include "NoAuto.h"
#include "AutonomousTote.h"
#include "Whips.h"
#include "WhipAuto.h"

class Robot: public IterativeRobot {
private:
	Joystick* PrimaryController, *SecondaryController;
	Gyro *AutoGyro;
	Hoarder * Hoard;
	Stacker *Stack;
	Collector *Collect;
	Whips *Burgerler;
	//CompressorManager compressor;
	PowerDistributionPanel *PDP;
	LiveWindow *lw;
	Swerve *swerve;
	SimpleAutonomous *SimpleAuto;
	CameraServer *camera;
	SimpleCanAndToteAutonomous *SingleTote;
	AutonomousCan *CanAuto, *CanAuto2, *CanAuto3;
	AutonomousTote *TripleTote;
	WhipAuto *StealCans;
	NoAutonomous *NoAuto;
	SendableChooser *AutoChooser;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		camera = CameraServer::GetInstance();
		PDP = new PowerDistributionPanel;
		camera->StartAutomaticCapture("cam0");
		PrimaryController = new Joystick(0);
		SecondaryController = new Joystick(1);
		AutoGyro = new Gyro(0);
		swerve = new Swerve(PrimaryController);
		Collect = new Collector();
		Stack = new Stacker(Collect, PDP);
		Hoard = new Hoarder();
		Burgerler = new Whips();
		SimpleAuto = new SimpleAutonomous();
		SingleTote = new SimpleCanAndToteAutonomous();
		CanAuto = new AutonomousCan(1);
		CanAuto2 = new AutonomousCan(2);
		CanAuto3 = new AutonomousCan(3);
		TripleTote = new AutonomousTote();
		StealCans = new WhipAuto(Burgerler);

		NoAuto = new NoAutonomous();
		AutoChooser = new SendableChooser;

		AutoGyro->InitGyro();
		AutoChooser->AddDefault("2 Can Auto", CanAuto2);
		AutoChooser->AddObject("SimpleAuto", SimpleAuto);
		AutoChooser->AddObject("NoAutonomous", NoAuto);
		AutoChooser->AddObject("3 Can Auto", CanAuto3);
		AutoChooser->AddObject("Whip Auto", StealCans);
		// AutoChooser->AddObject("Triple Yellow Tote", TripleTote);
		AutoChooser->AddObject("Hoard Can", CanAuto);
		// AutoChooser->AddObject("Single Yellow Tote", SingleTote);
		SmartDashboard::PutData("Auto Choice", AutoChooser);

	}

	void AutonomousInit() {
		// compressor.checkCompressor();
		AutoSelect *ChoosenAutonomous = (AutoSelect *) AutoChooser->GetSelected();
		ChoosenAutonomous->Initialize(swerve, Collect, Stack, Hoard, AutoGyro);
		// SimpleAuto->Initialize(swerve, Collect, Stack, Hoard);
	}

	void AutonomousPeriodic() {
		AutoSelect *ChoosenAutonomous = (AutoSelect *) AutoChooser->GetSelected();

		while (IsAutonomous() && IsEnabled()) {
			ChoosenAutonomous->Run(swerve, Collect, Stack, Hoard, AutoGyro);
		}

		ChoosenAutonomous->End(swerve, Collect, Stack, Hoard, AutoGyro);
		/*compressor.checkCompressor();
		SimpleAuto->Run(swerve, Collect, Stack, Hoard);
		CanAuto->Run(swerve, Collect, Stack, Hoard);
		SingleTote->Run(swerve, Collect, Stack, Hoard);
		TripleTote->Run(swerve, Collect, Stack, Hoard);*/
	}

	void TeleopInit() {
		// PDP.ClearStickyFaults();
		swerve->Initialize();
		// compressor.checkCompressor();
		Stack->init();
	}

	void TeleopPeriodic() {
		// compressor.checkCompressor();

		// Comment this in when you want to run a functionality don't forget to test the limit switch:
		swerve->Run();
		Hoard->hoard(SecondaryController->GetRawButton(HOARD_BTN));
		Stack->ManualStacker(SecondaryController->GetRawButton(SETPOINT_UP), SecondaryController->GetRawButton(SETPOINT_DOWN));
		Stack->AutoStacker(SecondaryController->GetRawButton(AUTOSTACK_BTN), SecondaryController->GetRawButton(LEVEL_UP), SecondaryController->GetRawButton(LEVEL_DOWN), SecondaryController->GetRawButton(BUTTON_CAN));
		Stack->Kill(SecondaryController->GetRawButton(9));
		Stack->SwitchStacking(SecondaryController->GetRawButton(1));
		Collect->setMotors(PrimaryController->GetRawButton(5), PrimaryController->GetRawButton(6), PrimaryController->GetRawButton(8), PrimaryController->GetRawButton(7));
		Collect->setState(PrimaryController->GetRawButton(4), SecondaryController->GetRawButton(RIGHT_VERTICAL), Stack->DangerLevel());

		Collect->setGrab(PrimaryController->GetRawButton(3), SecondaryController->GetRawAxis(COL_GRAB_LEFT_AXIS), Stack->DangerLevel());
		Collect->LimitSwitch();

		// Comment this out when running a funtionality:
		//Stack->StackLeft(SecondaryController->GetRawButton(5), SecondaryController->GetRawButton(7));
		//Stack->StackRight(SecondaryController->GetRawButton(6), SecondaryController->GetRawButton(8));
		//Stack->Tune(PrimaryController->GetRawButton(8),PrimaryController->GetRawButton(7),PrimaryController->GetRawButton(5),PrimaryController->GetRawButton(3),PrimaryController->GetRawButton(10),PrimaryController->GetRawButton(9),PrimaryController->GetRawButton(12),PrimaryController->GetRawButton(11),PrimaryController->GetRawButton(1), PrimaryController->GetRawButton(2));
		//swerve->Tune();

		SmartDashboard::PutNumber("Right Stack Current", PDP->GetCurrent(10));
		SmartDashboard::PutNumber("Left Stack Current", PDP->GetCurrent(9));
		SmartDashboard::PutNumber("Gyro", AutoGyro->GetAngle());
	}

	void TestInit() {
		swerve->Initialize();
		Stack->init();
	}

	void TestPeriodic() {
		// swerve->Tune();
		Stack->StackLeft(SecondaryController->GetRawButton(5), SecondaryController->GetRawButton(7));
		Stack->StackRight(SecondaryController->GetRawButton(6), SecondaryController->GetRawButton(8));
		// Stack->Tune(PrimaryController->GetRawButton(8),PrimaryController->GetRawButton(7),PrimaryController->GetRawButton(5),PrimaryController->GetRawButton(3),PrimaryController->GetRawButton(10),PrimaryController->GetRawButton(9),PrimaryController->GetRawButton(12),PrimaryController->GetRawButton(11),PrimaryController->GetRawButton(1), PrimaryController->GetRawButton(2));
	}
};

START_ROBOT_CLASS(Robot);
