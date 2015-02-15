#ifndef COMPRESSOR_MANAGER_H
#define COMPRESSOR_MANAGER_H
#include "Schematic.h"
#include "WPILib.h"

class CompressorManager
{

public:
	CompressorManager()

	{
		comp = new Relay(COMPRESSOR_RELAY, Relay::Direction::kForwardOnly);
		preassureswitch = new DigitalInput(COMPRESSOR_SWITCH);
	}
	void checkCompressor();
	int getPressureSwitch();

private:
	Relay *comp;
	DigitalInput *preassureswitch;
};
#endif
