#include "Autonomous.h"

void Autonomous::Run()
{
	switch (AutoState)
	{
	case 0:
	  /*drive->setdistance(10 or something IDFK)
		if (drive->atdistance())
		{
			AutoState = 1;
		}*/
	break;
	case 1:
		hoarder.hoard(1);
		hoarder.hoard(0);
	  /*drive->setdistance(1)
	    if (drive->atdistance())
	    {
			hoarder.hoard(1);
			hoarder.hoard(0);
			hoarder.hoard(1);
			hoarder.hoard(0)
			Autostate = 2;
	    }*/
	break;
	case 2:
		/*drive->setdistance(2)
		  if (drive->atdistance())
	      {
	     	hoarder.hoard(1);
			hoarder.hoard(0);
			hoarder.hoard(1);
			hoarder.hoard(0)
			 Autostate = 3;
		  }*/
	break;
	case 3:
		/*drive->setdistance(3)
		  if (drive->atdistance())
		  {
			hoarder.hoard(1);
			hoarder.hoard(0);
			hoarder.hoard(1);
			hoarder.hoard(0)
			 Autostate = 4;
		  }*/
	break;
	case 4:
		/*drive->setdistance(4)
		 if (drive->atdistance())
		  {
			hoarder.hoard(1);
			hoarder.hoard(0);
			 Autostate = 4;
		  }*/
		break;
	}
}
