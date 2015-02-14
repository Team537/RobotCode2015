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
	  /*drive->setdistance(1)
	    if (drive->atdistance())
	    {
			hoarder.hoard(1);
			count++;
			if (count == 2)
			{
				Autostate = 2;
			}
			else if (count = 4)
			{
				Autostate = 3;
			}
			else
			{
				Autostate = 0;
			}
	    }*/
	break;
	case 2:
		/*drive->setdistance(20)
		  if (drive->atdistance())
	      {
			 Autostate = 1;
		  }*/
	break;
	case 3:
		//Do nothing
	break;
	}
}
