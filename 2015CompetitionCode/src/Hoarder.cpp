//Dependencies
#include "Hoarder.h"

//When the bot is enabled, resets the hoarder
void Hoarder::initialize()
{
	pistonextend->Set(0);
}

//When a button is pressed, grabs or releases the can
void Hoarder::hoard(int btnhoard){
	if(btnhoard && !lastpressed)
	{
		pistonextend->Set(!pistonextend->Get());
	}
	lastpressed = btnhoard;
}

void Hoarder::Extend()
{
	pistonextend->Set(1);
}

void Hoarder::Retract()
{
	pistonextend->Set(0);
}
