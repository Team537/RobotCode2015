//Dependencies
#include "Hoarder.h"

//When the bot is enabled, resets the hoarder
void Hoarder::initialize()
{
	pistonextend->Set(1);
	pistonretract->Set(0);
}

//When a button is pressed, grabs or releases the can
void Hoarder::hoard(int btnhoard){
	if(btnhoard && !lastpressed)
	{
		pistonextend->Set(!pistonextend->Get());
		pistonretract->Set(!pistonretract->Get());
	}
	lastpressed = btnhoard;
}
