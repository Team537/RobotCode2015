#ifndef PID_AutoTune_v0
#define PID_AutoTune_v0
#define LIBRARY_VERSION	0.0.1
#include "WPILib.h"

class PID_ATune
{


  public:
  //commonly used functions **************************************************************************
    PID_ATune();                       	// * Constructor.  links the Autotune to a given PID
    void InitializeRuntime(float);
    int Runtime(float,float);						   			   	// * Similar to the PID Compue function, returns non 0 when done
	void Cancel();									   	// * Stops the AutoTune					   	//

	void SetControlType(int); 						   	// * Determies if the tuning parameters returned will be PI (D=0)
	int GetControlType();							   	//   or PID.  (0=PI, 1=PID)

	void SetLookbackSec(int);							// * how far back are we looking to identify peaks
	int GetLookbackSec();								//

	void SetNoiseBand(float);							// * the autotune will ignore signal chatter smaller than this value
	double GetNoiseBand();								//   this should be acurately set

	double GetKp();										// * once autotune is complete, these functions contain the
	double GetKi();										//   computed tuning parameters.
	double GetKd();										//

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

