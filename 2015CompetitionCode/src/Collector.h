#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "WPILib.h"
#include "Schematic.h"

/** CONTROLS:
	 LT - Increase left arm extend state.
	 LB - Decrease left arm extend state.
	 RT - Increase right arm extend state.
	 RB - Decrease right arm extend state.

	 Start  - Grab.
	 Dpad v	- Motor into bot.
	 Dpad ^	- Motor out of bot.
 */

// Collector class constructor.
class Collector {
private:
	// Used only in this class.
	Solenoid *leftFrontArm, *rightFrontArm; // Arm pistons pushing pistons to grab.
	Victor *leftBelt, *rightBelt; // Conveyer belt suckers.
	DigitalInput *CollectedTote;
	int lState, rState;

public:
	Solenoid *leftGrabber, *rightGrabber;
	Collector() {
		leftFrontArm = new Solenoid(COLLECTOR_ARMLF);
		rightFrontArm = new Solenoid(COLLECTOR_ARMRF);

		leftGrabber = new Solenoid(GRAB_L_PISTON);
		rightGrabber = new Solenoid(GRAB_R_PISTON);

		leftBelt = new Victor(COLLECTOR_SUCKL);
		rightBelt = new Victor(COLLECTOR_SUCKR);
		CollectedTote = new DigitalInput(9);

		lastrightgrab = 0;
		lastleftgrab = 0;
		lState = 0;
		rState = 0;
		rampbelt = 0.1;
		oldlbelt = false;
		oldrbelt = false;
		lastltoggle = 0;
		lastrtoggle = 0;
		rbelton = 0;
		lbelton = 0;
	}

	void setState(int ltoggle, int rtoggle, bool elevatordanger);
	int getLeftState();
	int getRightState();
	int lastrightgrab;
	int lastleftgrab;
	bool oldrbelt, oldlbelt;
	float rampbelt;
	int lastltoggle;
	int lastrtoggle;
	int rbelton, lbelton;

	void setGrab(int leftyaxis, float rightyaxis, bool elevatordanger);
	bool getGrableft();
	bool getGrabright();
	bool GetLeftArm();
	bool GetRightArm();
	void LimitSwitch();
	void setMotors(int leftverticaljoy, int rightverticaljoyint, int rightreverse, int leftreverse);
	float getLeftMotor();
	float getRightMotor();
};

#endif
