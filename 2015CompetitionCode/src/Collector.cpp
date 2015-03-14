//Dependencies
#include "Collector.h"

void Collector::setState(int ltoggle, int rtoggle, bool elevatordanger) {
		if (ltoggle == 1 && lastltoggle == 0)
		{
			leftFrontArm->Set(!leftFrontArm->Get());
		//}
		//if (rtoggle == 1 && lastrtoggle == 0)
		//{
			rightFrontArm->Set(!rightFrontArm->Get());
		}
	lastltoggle = ltoggle;
	lastrtoggle = rtoggle;
}


void Collector::setGrab(int leftyaxis, float rightyaxis, bool elevatordanger) {
	/*if (leftyaxis <= -.5)
	{
		leftGrabber->Set(0);
	}
		if (leftyaxis >= .5)
		{
			leftGrabber->Set(1);
		}
		if (rightyaxis <= -.5)
		{
			rightGrabber->Set(1);
		}
	if (rightyaxis >= .5)
	{
		rightGrabber->Set(0);
	}*/
	if(leftyaxis == 1 && lastleftgrab == 0)
	{
		rightGrabber->Set(!rightGrabber->Get());
		leftGrabber->Set(!leftGrabber->Get());
	}
	lastleftgrab = leftyaxis;
}

bool Collector::getGrableft()
{
	return leftGrabber->Get();
}

bool Collector::getGrabright()
{
	return rightGrabber->Get();
}

void Collector::setMotors(int leftverticaljoy, int rightverticaljoy, int rightreverse, int leftreverse) {
	/*if(fabs(rightverticaljoy) >= .25)
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
	}*/
	if(leftverticaljoy && leftreverse == 0)
	{
		leftBelt->Set(1);
	}
	else if (leftreverse && leftverticaljoy == 0)
	{
		leftBelt->Set(-1);
	}
	else
	{
		leftBelt->Set(0);
	}
	if(rightverticaljoy && rightreverse == 0)
	{
		rightBelt->Set(1);
	}
	else if (rightreverse && rightverticaljoy == 0)
	{
		rightBelt->Set(-1);
	}
	else
	{
		rightBelt->Set(0);
	}
}

float Collector::getLeftMotor() {
	return leftBelt->Get();
}

float Collector::getRightMotor() {
	return rightBelt->Get();
}
