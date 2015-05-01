#ifndef WHIPS_H
#define WHIPS_H

#include "WPIlib.h"

class Whips {
public:

	Whips() {
		//LeftWhip = new CANTalon(4);
		RightWhip = new CANTalon(5);
		//LeftClaw = new Solenoid(3);
		RightClaw = new Solenoid(4);
		Stowed = 0;
		Deployed = 85;
		drive = false;
		retracttoggle = true;
		lastpressedWhips = 0;
		lastpressedClaws = 0;
	}

	bool ReadyToDrive();
	void DeployWhips();
	void RetractWhips();

	void TeleWhips(int WhipsToggle);
	void EndClaws(int ClawToggle);
private:
	CANTalon *RightWhip;
	Solenoid *RightClaw;
	double Stowed;
	double Deployed;
	bool drive;
	bool retracttoggle;
	int lastpressedWhips;
	int lastpressedClaws;

	double Conversion(double, double);
	double OppisiteConversion(double, double);

};
#endif
