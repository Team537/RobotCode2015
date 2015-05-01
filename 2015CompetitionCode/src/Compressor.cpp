#include "Compressor.h"
#include "Schematic.h"

void CompressorManager::checkCompressor() {
	if (preassureswitch->Get() == 1) {
		comp->Set(Relay::Value::kOff);
	} else {
		comp->Set(Relay::Value::kOn);
	}
}

int CompressorManager::getPressureSwitch() {
	return preassureswitch->Get();
}
