#include "AutonomousCan.h"

void AutonomousCan::Run(int cannumber)
{
	switch (Autostate)
	{
	case 0:
	  /*Drive->setdistance(10 or something IDFK)
		if (Drive->atdistance())
		{
			AutoState = 1;
		}*/
	break;
	case 1:
		Drive->AutonomousAngle(180,180,180,180);
		if(Drive->OnTarget())
		{
			hoarder->hoard(1);
			hoarder->hoard(0);
			Drive->AutonomousSpeed(1,1,1,1);
			Autotime->Start();
			if (Autotime->Get() > 2)
			{
				hoarder->hoard(1);
				hoarder->hoard(0);
				if(Autotime->Get() > 3)
				{
					hoarder->hoard(1);
					hoarder->hoard(0);
					Autotime->Stop();
					if(cannumber > 1)
					{
						Autostate = 2;
					}
					else
					{
						Autostate = 5;
					}
				}
			}
		}
	break;
	case 2:
		Autotime->Reset();
		Drive->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 2)
		{
			hoarder->hoard(1);
			hoarder->hoard(0);
			if(Autotime->Get() > 3)
			{
				hoarder->hoard(1);
				hoarder->hoard(0);
				Autotime->Stop();
				if(cannumber > 2)
				{
					Autostate = 3;
				}
				else
				{
					Autostate = 5;
				}
			}
		}
	break;
	case 3:
		Autotime->Reset();
		Drive->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 4)
		{
			hoarder->hoard(1);
			hoarder->hoard(0);
			if(Autotime->Get() > 5)
			{
				hoarder->hoard(1);
				hoarder->hoard(0);
				Autotime->Stop();
				if(cannumber > 3)
				{
					Autostate = 4;
				}
				else
				{
					Autostate = 5;
				}
			}
		}
	break;
	case 4:
		Autotime->Reset();
		Drive->AutonomousSpeed(1,1,1,1);
		Autotime->Start();
		if (Autotime->Get() > 2)
		{
			hoarder->hoard(1);
			hoarder->hoard(0);
			if(Autotime->Get() > 3)
			{
				hoarder->hoard(1);
				hoarder->hoard(0);
				Autotime->Stop();
				Autostate = 5;
			}
		}
		break;
	case 5:
		Autotime->Reset();
		break;
	}
}
