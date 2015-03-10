//Dependencies
#include "Collector.h"

void Collector::setState(int ltoggle, int rtoggle) {
	if (ltoggle == 1 && lastltoggle == 0)
	{
		leftFrontArm->Set(!leftFrontArm->Get());
	}
	lastltoggle = ltoggle;
	if (rtoggle == 1 && lastrtoggle == 0)
	{
		rightFrontArm->Set(!rightFrontArm->Get());
	}
	lastrtoggle = rtoggle;
}


void Collector::setGrab(float leftyaxis, float rightyaxis, bool elevatorInDanger) {
	if (leftyaxis <= -.5)
	{
		leftGrabber->Set(0);
	}
	if (!elevatorInDanger)
	{
		if (leftyaxis >= .5)
		{
			leftGrabber->Set(1);
		}
		if (rightyaxis <= -.5)
		{
			rightGrabber->Set(1);
		}
	}
	if (rightyaxis >= .5)
	{
		rightGrabber->Set(0);
	}
}

bool Collector::getGrab() { return (leftGrabber->Get() && rightGrabber->Get()); }

void Collector::setMotors(float leftverticaljoy, float rightverticaljoy) {
	if(fabs(rightverticaljoy) >= .25)
	{
		float rightbeltdifferance = rightverticaljoy - oldrbelt;
		if(fabs(rightbeltdifferance) >= rampbelt)
		{
			oldrbelt += rampbelt * (rightbeltdifferance / fabs(rightbeltdifferance));
		}
		rightBelt->Set(-rightverticaljoy);
	}
	else{
		rightBelt->Set(0);
	}
	if (fabs(leftverticaljoy) >= .25)
	{
		float leftbeltdifferance = leftverticaljoy - oldlbelt;
		if(fabs(leftbeltdifferance) >= rampbelt)
		{
			oldlbelt += rampbelt * (leftbeltdifferance / fabs(leftbeltdifferance));
		}
		leftBelt->Set(-leftverticaljoy);
	}
	else
	{
		leftBelt->Set(0);
	}
}

float Collector::getLeftMotor() {
	return leftBelt->Get();
}

float Collector::getRightMotor() {
	return rightBelt->Get();
}
