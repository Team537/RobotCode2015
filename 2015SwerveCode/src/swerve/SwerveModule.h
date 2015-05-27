#ifndef SWERVEMODULE_H
#define SWERVEMODULE_H

#include <cmath>
#include <ctime>
#include <string>
#include <WPIlib.h>
#include <Schematic.h>
#include <swerve/DoublePot.h>
#include <swerve/PIDDistance.h>
#include <swerve/PIDDriveValue.h>
#include <swerve/PIDValue.h>

class SwerveModule {
private:
	PIDController *PIDAngle, *PIDDrive, *PIDDriveDistance;
	Victor *SPEEDOUTPUT, *ANGLEOUTPUT;
	Encoder *SPEEDENCODER;
	DoublePot *ANGLEPOT;
	Timer WATCH;
	std::string NAME;

	float RANGE, MIN, MAX, OFFSET, SETPOINTOFFSET;
	float OLDSETPOINT;
	float TARGET;

public:
	/**
	 * Main Swerve Module Constructor Needs These Arguments: (speed, angle, encoder1, encoder2, pot, pid angle, pid drive, pid distance values, name, offset, setpoint offset)
	 */
	SwerveModule(uint32_t speedport, uint32_t angleport, uint32_t encoderport1, uint32_t encoderport2, uint32_t potport, PIDValue *PIDAngleValues, PIDDriveValue *PIDDriveValues, PIDDistance *PIDDistanceValues, std::string name, float offset, float offsetsetpoint) {
		SPEEDOUTPUT = new Victor(speedport);
		ANGLEOUTPUT = new Victor(angleport);
		SPEEDENCODER = new Encoder(encoderport1, encoderport2, false, Encoder::EncodingType::k4X);
		SPEEDENCODER->SetDistancePerPulse(0.023271056296296);
		ANGLEPOT = new DoublePot(potport, 360, PIDAngleValues->MININPUT, PIDAngleValues->MAXINPUT, 0, name);

		PIDAngle = new PIDController(PIDAngleValues->P, PIDAngleValues->I, PIDAngleValues->D, ANGLEPOT, ANGLEOUTPUT, 0.025);
		PIDDrive = new PIDController(PIDDriveValues->P, PIDDriveValues->I, PIDDriveValues->D, SPEEDENCODER, SPEEDOUTPUT);
		PIDDriveDistance = new PIDController(PIDDistanceValues->P, PIDDistanceValues->I, PIDDistanceValues->D, SPEEDENCODER, SPEEDOUTPUT);
		PIDDriveDistance->SetTolerance(5);
		PIDDrive->SetPID(PIDDriveValues->P, PIDDriveValues->I, PIDDriveValues->D, PIDDriveValues->F);
		PIDAngle->SetInputRange(PIDAngleValues->MININPUT, PIDAngleValues->MAXINPUT);
		PIDAngle->SetOutputRange(PIDAngleValues->MINOUTPUT, PIDAngleValues->MaxOUTPUT);
		PIDAngle->SetAbsoluteTolerance(20);
		PIDAngle->SetContinuous(true);

		NAME = name;
		SETPOINTOFFSET = offsetsetpoint;
		OFFSET = offset;
		OLDSETPOINT = 165;
		TARGET = 0;

		MIN = PIDAngleValues->MININPUT;
		MAX = PIDAngleValues->MAXINPUT;
		RANGE = MAX - MIN;
	}

	void Initialize();
	void Drive(float speed);
	void AutoDrive(float distance);
	void Steer(float angle);
	void OffsetAdjust(int a, int b);
	void PIDAdjust(float P, float I, float D);

	float POTReadAngle();
	PIDController* PIDGetAngle();
	bool PIDAtAngle();
	void PIDDisableAngle();
	void PIDResetAngle();

	bool PIDAtDistance();
	void PIDDisableDistance();

	void DashboardLoop();
};

#endif
