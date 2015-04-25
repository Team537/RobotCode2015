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

bool Collector::GetLeftArm()
{
	return leftFrontArm->Get();
}

bool Collector::GetRightArm()
{
	return rightFrontArm->Get();
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
	if(leftverticaljoy && oldlbelt == false && leftreverse == 0)
	{
		lbelton = !lbelton;
	}
	oldlbelt = leftverticaljoy;

	if (leftreverse && lbelton == false)
	{
		leftBelt->Set(1);
	}
	else
	{
		leftBelt->Set(-lbelton);
	}

	if(rightverticaljoy && oldrbelt == false && rightreverse == 0)
	{
		rbelton = !rbelton;
	}
	if (rightreverse && rbelton == false)
	{
		rightBelt->Set(-1);
	}
	else
	{
		rightBelt->Set(rbelton);
	}
	oldrbelt = rightverticaljoy;
	/*
	if(rightverticaljoy)
	{
		lbelton = true;
	}
	if(leftverticaljoy)
	{
		lbelton = false;
	}

	if (rightreverse && lbelton == false)
	{
		rightBelt->Set(-1);
	}
	if (leftreverse && lbelton == false)
	{
		leftBelt->Set(1);
	}

	if(lbelton == true)
	{
		leftBelt->Set(-lbelton);
		rightBelt->Set(rbelton);
	}
	else if (lbelton == false && leftreverse == false && rightreverse == false)
	{
		leftBelt->Set(0);
		rightBelt->Set(0);
	}*/


}

float Collector::getLeftMotor() {
	return leftBelt->Get();
}

float Collector::getRightMotor() {
	return rightBelt->Get();
}
void Collector::LimitSwitch()
{
	bool CollectSwitch = CollectedTote->Get();
	SmartDashboard::PutBoolean("Collected Tote 2", CollectSwitch);
}
