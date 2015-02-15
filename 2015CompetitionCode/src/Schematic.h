#ifndef SCHEMATIC_H_
#define SCHEMATIC_H_

//Controller
#define HOARD_BTN 				1
#define TOTE_GRAB_BTN			3
#define AUTOSTACK_BTN			2
#define STACKER_UP				6
#define STACKER_DOWN			5
#define EXTENDER_IN				1
#define EXTENDER_OUT			4
#define LEFT_TOGGLE				7
#define LEFT_ORIENT				13
#define RIGHT_TOGGLE			8
#define RIGHT_ORIENT			14
#define COL_GRAB_RIGHT_AXIS		0
#define COL_GRAB_LEFT_AXIS		2
#define COL_MOTOR_LEFT			1
#define COL_MOTOR_RIGHT			3
#define JOYDEADBAND 			0.25

//Pistons
#define HOARDER_PISTON_1	0
#define HOARDER_PISTON_2 	0
#define GRAB_L_PISTON 	 	0
#define GRAB_R_PISTON 	 	0
#define STACKER_FLAPS 		0

//Victors
#define COLLECTOR_SUCKL 	0
#define COLLECTOR_SUCKR	 	0
#define STACKER_LIFT		0
#define STACKER_EXTEND		0
#define COLLECTOR_ARMLB 	0
#define COLLECTOR_ARMLF 	0
#define COLLECTOR_ARMRB 	0
#define COLLECTOR_ARMRF 	0

//Constants
#define COLLECTOR_STATEINIT 0
#define COLLECTOR_CONVSPD	0.5
#define COLLECTOR_CONVRAMP 	0.05

//Digital Inputs
#define STACKER_IN_SWITCH	0
#define STACKER_OUT_SWITCH	0

//Analog Inputs
#define STACKER_LIFT_POT	0

//Compressor
#define COMPRESSOR_SWITCH	0
#define COMPRESSOR_RELAY	0

//PIDValues
#define PID_LIFT_UP 		.04,.00,.00
#define PID_LIFT_DOWN		.04,.00,.00

#endif
