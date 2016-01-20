#ifndef PID_AutoTune_v0
#define PID_AutoTune_v0
#define LIBRARY_VERSION	0.0.1
#include "WPILib.h"

class PID_ATune {

public:
	PID_ATune(); // Constructor. Links the Autotune to a given PID.

	void InitializeRuntime(float); // Initialize working variables the first run.
	int Runtime(float, float); // Similar to the PID Compute function, returns non 0 when done.
	void Cancel(); // Stops the AutoTune.

	void SetControlType(int); // Determines if the tuning parameters returned will be PI (D=0) or PID. (0=PI, 1=PID).
	int GetControlType(); // Returns ControlType.

	void SetLookbackSec(int); // How far back are we looking to identify peaks.
	int GetLookbackSec(); // Returns LookBack * SampleTime.

	void SetNoiseBand(float); // The autotune will ignore signal chatter smaller than this value.
	double GetNoiseBand(); // This should be accurately set.

	// Once autotune is complete, these functions contain the computed tuning parameters.
	double GetKp();
	double GetKi();
	double GetKd();

private:
	void FinishUp();
	bool isMax, isMin;
	Timer watchclock;
	float noiseBand;
	int controlType;
	bool running;
	unsigned long peak1, peak2;
	double lastTime;
	int sampleTime;
	int nLookBack;
	int peakType;
	float lastInputs[101];
	float peaks[10];
	int peakCount;
	bool justchanged;
	bool justevaled;
	float absMax, absMin;
	float Ku, Pu;
	int i;
};

#endif

