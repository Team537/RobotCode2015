#ifndef SWERVEMODULE_H
#define SWERVEMODULE_H
#include <swerve/PIDValue.h>
#include <swerve/PIDDriveValue.h>
#include <swerve/PIDDistance.h>
#include "DoublePot.h"
#include <wpilib.h>
#include <ctime>
#include <string>

class SwerveModule
{
private:
	Victor *SpeedOutput, *AngleOutput;
	Encoder *SpeedEncoder;
	DoublePot *AnglePotentiometer;
	double potfeedbackmin, potfeedbackmax;
	PIDController *PIDAngle;
	PIDController *PIDDrive;
	PIDController *PIDDriveDistance;
	std::string Name;
	float range,MIN,MAX,Offset;
	float OldSetpoint;
	Timer watch;
	double MaxRate;
public:
	SwerveModule(uint32_t SpeedPort, uint32_t AngPort, uint32_t EncPort1, uint32_t EncPort2,uint32_t PotPort, PIDValue *AnglePIDValues, PIDDriveValue *DrivePIDValues, PIDDistance *DistancePIDValues,std::string name, float offset, double MAXRate, float OFFSETsetpoint)
	{
		SpeedOutput = new Victor(SpeedPort);
		SpeedEncoder = new Encoder(EncPort1,EncPort2, false, Encoder::EncodingType::k4X);
		AngleOutput = new Victor(AngPort);
		AnglePotentiometer = new DoublePot(PotPort,360,0, AnglePIDValues->MINInput, AnglePIDValues->MAXInput,0, name);
		Name = name;
		PIDAngle = new PIDController(AnglePIDValues->P,AnglePIDValues->I,AnglePIDValues->D,AnglePotentiometer,AngleOutput, .025);
		PIDDrive = new PIDController(DrivePIDValues->P,DrivePIDValues->I,DrivePIDValues->D,SpeedEncoder,SpeedOutput);
		PIDDriveDistance = new PIDController(DistancePIDValues->P,DistancePIDValues->I,DistancePIDValues->D,SpeedEncoder,SpeedOutput);
		PIDDrive->SetPID(DrivePIDValues->P,DrivePIDValues->I,DrivePIDValues->D,DrivePIDValues->F);
		PIDAngle->SetInputRange(AnglePIDValues->MINInput,AnglePIDValues->MAXInput);
		PIDAngle->SetOutputRange(AnglePIDValues->MINOutput, AnglePIDValues->MaxOutput);
		PIDAngle->SetAbsoluteTolerance(15);
		potfeedbackmin = 100;
		potfeedbackmax = 100;
		PIDAngle->SetContinuous(true);
		MIN = AnglePIDValues->MINInput;
		MAX = AnglePIDValues->MAXInput;
		toggle = true;
		MaxRate = MAXRate;
		Offset = offset;
		lasttrigger = 0;
		range = MAX - MIN;
		OldSetpoint = 165;
		Oldreading = 165;
		firsttime = true;
		SpeedEncoder->SetDistancePerPulse(.05026548);
		maxencrate = 10;
		offSet = OFFSETsetpoint;

	}
	void Initialize();
	void drive(float angle, float speed);
	void AutoDrive(float Angle);
	void offSetAdjust(int a, int b);
	void PIDAdjust(float P, float I, float D);
	bool AtAngle();
	bool toggle;
	float ReadPot();
	int lasttrigger;
	PIDController* GetAnglePID();
	float Oldreading;
	bool firsttime;
	double maxencrate;
	float offSet;
	void Reset();
	void DisablePID();
	void PIDAuto(float distance);
	bool GetDistancePID();
	void DistancePIDDisable();
};
#endif
