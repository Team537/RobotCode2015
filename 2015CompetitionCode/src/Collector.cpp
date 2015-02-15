//Dependencies
#include "Collector.h"

void Collector::setLeftState(int ltoggle, int lorient) {

	switch (lState){
	case 0: // both pistons retracted
		leftBackArm->Set(false);
		leftFrontArm->Set(false);
		if(ltoggle && !lastltoggle)
		{
			lState = 2;
		}
		if(lorient)
		{
			lState = 1;
			rState = 1;
		}
		lastltoggle = ltoggle;
		break;
	case 1:
		leftBackArm->Set(true);
		leftFrontArm->Set(false);
		if(!lorient)
		{
			lState = 2;
			rState = 2;
		}
		break;
	case 2:
		leftBackArm->Set(true);
		leftFrontArm->Set(true);
		if(ltoggle && !lastltoggle)
		{
			lState = 0;
		}
		if(lorient)
		{
			lState = 1;
			rState = 1;
		}
		lastltoggle = ltoggle;
		break;
	default:
		//wut u do now kurt...
		break;
	}

}

void Collector::setRightState(int rtoggle, int rorient) {
	switch (rState){
	case 0: // both pistons retracted
		rightBackArm->Set(false);
		rightFrontArm->Set(false);
		if(rorient)
		{
			rState = 1;
			lState = 1;
		}
		if(rtoggle && !lastrtoggle)
		{
			rState = 2;
		}
		lastrtoggle = rtoggle;
		break;
	case 1:
		rightBackArm->Set(true);
		rightFrontArm->Set(false);
		if(!rorient)
		{
			rState = 1;
			lState = 1;
		}
		break;
	case 2:
		rightBackArm->Set(true);
		rightFrontArm->Set(true);
		if(rorient)
		{
			rState = 1;
			lState = 1;
		}
		if(rtoggle && !lastrtoggle)
		{
			rState = 0;
		}
		lastrtoggle = rtoggle;
		break;
	default:
		//wut u do now kurt...
		break;
	}
}

int Collector::getLeftState() { return lState; }
int Collector::getRightState() { return rState; }

void Collector::setGrab(float leftyaxis, float rightyaxis) {
	if(lState == 2)
	{
		if (leftyaxis <= -.5)
		{
			leftGrabber->Set(0);
		}
		if (leftyaxis >= .5)
		{
			leftGrabber->Set(1);
		}
	}
	if(rState == 2)
	{
		if (rightyaxis <= -.5)
		{
			rightGrabber->Set(1);
		}
		if (rightyaxis >= .5)
		{
			rightGrabber->Set(0);
		}
	}
}

bool Collector::getGrab() { return (leftGrabber->Get() && rightGrabber->Get()); }

void Collector::setMotors(float leftverticaljoy, float rightverticaljoy) {
	if(fabs(rightverticaljoy) >= .1)
	{
		float rightbeltdifferance = rightverticaljoy - oldrbelt;
		if(fabs(rightbeltdifferance) >= rampbelt)
		{
			oldrbelt += rampbelt * (rightbeltdifferance / fabs(rightbeltdifferance));
		}
		rightBelt->Set(rightverticaljoy);
	}
	if (fabs(leftverticaljoy) >= .1)
	{
		float leftbeltdifferance = leftverticaljoy - oldlbelt;
		if(fabs(leftbeltdifferance) >= rampbelt)
		{
			oldlbelt += rampbelt * (leftbeltdifferance / fabs(leftbeltdifferance));
		}
		leftBelt->Set(leftverticaljoy);
	}
}

float Collector::getLeftMotor() {
	return leftBelt->Get();
}

float Collector::getRightMotor() {
	return rightBelt->Get();
}
