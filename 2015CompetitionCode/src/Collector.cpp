//Dependencies
#include "Collector.h"

void Collector::setLeftState(int lprogress, int ldegress) {

	switch (lState){
	case 0: // both pistons retracted
		leftBackArm->Set(false);
		leftFrontArm->Set(false);
		if(lprogress)
		{
			lState = 1;
		}
		if(ldegress)
		{
			lState = 2;
		}
		break;
	case 1:
		leftBackArm->Set(true);
		leftFrontArm->Set(false);
		if(lprogress)
		{
			lState = 2;
		}
		if(ldegress)
		{
			lState = 0;
		}
		break;
	case 2:
		leftBackArm->Set(true);
		leftFrontArm->Set(true);
		if(lprogress)
		{
			lState = 0;
		}
		if(ldegress)
		{
			lState = 1;
		}
		break;
	default:
		//wut u do now kurt...
		break;
	}

}

void Collector::setRightState(int rprogress, int rdegress) {
	switch (rState){
	case 0: // both pistons retracted
		rightBackArm->Set(false);
		rightFrontArm->Set(false);
		if(rprogress)
		{
			rState = 1;
		}
		if(rdegress)
		{
			rState = 2;
		}
		break;
	case 1:
		rightBackArm->Set(true);
		rightFrontArm->Set(false);
		if(rprogress)
		{
			rState = 2;
		}
		if(rdegress)
		{
			rState = 0;
		}
		break;
	case 2:
		rightBackArm->Set(true);
		rightFrontArm->Set(true);
		if(rprogress)
		{
			rState = 0;
		}
		if(rdegress)
		{
			rState = 1;
		}
		break;
	default:
		//wut u do now kurt...
		break;
	}
}

int Collector::getLeftState() { return lState; }
int Collector::getRightState() { return rState; }

void Collector::setGrab(int rightgrab, int leftgrab) {
	if(rState == 1 || rState == 2)
	{
		if (rightgrab && !lastrightgrab)
		{
			leftGrabber->Set(1);
		}
	}
	lastrightgrab = rightgrab;
	if(lState == 1 || lState == 2)
	{
		if(leftgrab && !lastleftgrab)
		{
			rightGrabber->Set(1);
		}
	}
	lastleftgrab = leftgrab;
}

bool Collector::getGrab() { return (leftGrabber->Get() && rightGrabber->Get()); }

void Collector::setMotors(bool forward, bool reverse) {
	if(forward)
	{
		leftBelt->Set(1);
		rightBelt->Set(1);
	}
	if (reverse)
	{
		leftBelt->Set(-1);
		rightBelt->Set(-1);
	}
}

float Collector::getLeftMotor() {
	return leftBelt->Get();
}

float Collector::getRightMotor() {
	return rightBelt->Get();
}
