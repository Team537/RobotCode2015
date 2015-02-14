//Define header file
#ifndef COLLECTOR_H
#define COLLECTOR_H

//Dependencies
#include "WPILib.h"
#include "Schematic.h"

/* #### CONTROLS ####
LT		-	increase left arm extend state
LB		-	decrease left arm extend state
RT 		-	increase right arm extend state
RB		-	decrease right arm extend state

## below are changeable ##
Start	-	grab
Dpad v	-	motor into bot
Dpad ^	-	motor out of bot
*/

//Collector class constructor
class Collector {

private: //Used only in this class

	Solenoid *leftBackArm, *leftFrontArm, *rightBackArm, *rightFrontArm; //arm pistons
	Solenoid *leftGrabber, *rightGrabber; 								 //pushing pistons to grab
	Victor 	 *leftBelt, *rightBelt; 	  								 //conveyor belt suckers

	int lState, rState;


public: //Used in all classes

	Collector ()
	{
		leftBackArm = new Solenoid(COLLECTOR_ARMLB);
		leftFrontArm = new Solenoid(COLLECTOR_ARMLF);
		rightBackArm = new Solenoid(COLLECTOR_ARMRB);
		rightFrontArm = new Solenoid(COLLECTOR_ARMRF);

		leftGrabber = new Solenoid(GRAB_L_PISTON);
		rightGrabber = new Solenoid(GRAB_R_PISTON);

		leftBelt = new Victor(COLLECTOR_SUCKL);
		rightBelt = new Victor(COLLECTOR_SUCKR);
		lastrightgrab = 0;
		lastleftgrab = 0;
		lState = 0;
		rState = 0;
	}

	//Declare functions
	void setLeftState(int lprogress, int ldegress);
	void setRightState(int rprogess, int rdegress);
	int getLeftState();
	int getRightState();
	int lastrightgrab;
	int lastleftgrab;

	void setGrab(int rightgrab, int leftgrab);
	bool getGrab();

	void setMotors(bool forward, bool reverse);
	float getLeftMotor();
	float getRightMotor();


};

#endif
