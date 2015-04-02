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

	Solenoid  *leftFrontArm, *rightFrontArm; //arm pistons
									 //pushing pistons to grab
	Victor 	 *leftBelt, *rightBelt; 	  								 //conveyor belt suckers
	DigitalInput *CollectedTote;
	int lState, rState;


public: //Used in all classes
	Solenoid *leftGrabber, *rightGrabber;
	Collector ()
	{
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

	//Declare functions
	void setState(int ltoggle, int rtoggle, bool elevatordanger );
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
