#include "WPILib.h"
#include "Autotune.h"

/**
 * Auto Tune the PID's in the swerve drive. Currently WIP and does not work.
 */
PID_ATune::PID_ATune() {
	watchclock.Start();
	controlType = 0; // Default to PI
	noiseBand = 3;
	running = false;
	SetLookbackSec(10);
	lastTime = watchclock.Get();

}

void PID_ATune::Cancel() {
	running = false;
}

void PID_ATune::InitializeRuntime(float refVal) {
	// Initialize working variables the first time around
	peakType = 0;
	peakCount = 0;
	peak1 = 0;
	peak2 = 0;
	justchanged = false;
	absMax = refVal;
	absMin = refVal;
	running = true;
}

int PID_ATune::Runtime(float refVal, float Pval) {
	if (fabs(Ku - Pval) >= .000001) {
		PID_ATune::InitializeRuntime(refVal);
	}

	Ku = Pval;
	justevaled = false;

	if (peakCount > 9 && running) {
		running = false;
		FinishUp();

		return 1;
	}

	double now = watchclock.Get();

	if ((now - lastTime) < sampleTime) {
		return 0;
	}

	lastTime = now;
	justevaled = true;

	if (running) {
		if (refVal > absMax) {
			absMax = refVal;
		} if (refVal < absMin) {
			absMin = refVal;
		}
	}

	SmartDashboard::PutNumber("Ref val", refVal);
	//bool isMax=true, isMin=true;
	isMax = true;
	isMin = true;

	/*
	 * Id peaks.
	 */
	for (int i = nLookBack - 1; i >= 0; i--) {
		float val = lastInputs[i];

		if (isMax) {
			isMax = refVal > val;
		}

		if (isMin) {
			isMin = refVal < val;
		}

		lastInputs[i + 1] = lastInputs[i];
	}

	lastInputs[0] = refVal;

	if (nLookBack < 9) { // We don't want to trust the maxes or mins until the inputs array has been filled.
		return 0;
	}

	if (isMax) {
		if (peakType == 0) {
			peakType = 1;
		}

		if (peakType == -1) {
			peakType = 1;
			justchanged = true;
			peak2 = peak1;
		}

		peak1 = now;
		peaks[peakCount] = refVal;

	} else if (isMin) {
		if (peakType == 0) {
			peakType = -1;
		}

		if (peakType == 1) {
			peakType = -1;
			peakCount++;
			justchanged = true;
		}

		if (peakCount < 10) {
			peaks[peakCount] = refVal;
		}
	}

	if (justchanged && peakCount > 2) { // We've transitioned.  check if we can autotune based on the last peaks.
		float avgSeparation = (fabs(peaks[peakCount - 1] - peaks[peakCount - 2]) + fabs(peaks[peakCount - 2] - peaks[peakCount - 3])) / 2;

		if (avgSeparation < 0.05 * (absMax - absMin)) {
			FinishUp();
			running = false;

			return 1;
		}
	}

	justchanged = false;

	return 0;
}

void PID_ATune::FinishUp() {
	// We can generate tuning parameters!
	Pu = (float) (peak1 - peak2) / 1000;
}

double PID_ATune::GetKp() {
	return controlType == 1 ? 0.6 * Ku : 0.4 * Ku;
}

double PID_ATune::GetKi() {
	return controlType == 1 ? 1.2 * Ku / Pu : 0.48 * Ku / Pu;  // Ki = Kc/Ti
}

double PID_ATune::GetKd() {
	return controlType == 1 ? 0.075 * Ku * Pu : 0;  // Kd = Kc * Td
}

void PID_ATune::SetControlType(int Type) { // 0=PI, 1=PID
	controlType = Type;
}

int PID_ATune::GetControlType() {
	return controlType;
}

void PID_ATune::SetNoiseBand(float Band) {
	noiseBand = Band;
}

double PID_ATune::GetNoiseBand() {
	return noiseBand;
}

void PID_ATune::SetLookbackSec(int value) {
	if (value < 1) {
		value = 1;
	}

	if (value < 25) {
		nLookBack = value * 4;
		sampleTime = .25;
	} else {
		nLookBack = 100;
		sampleTime = value * .010;
	}
}

int PID_ATune::GetLookbackSec() {
	return nLookBack * sampleTime;
}
