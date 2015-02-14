#ifndef SCHEMATIC_H_
#define SCHEMATIC_H_

//Controller
#define HOARD_BTN 				1
#define TOTE_GRAB_BTN			4
#define AUTOSTACK_BTN			1
#define STACKER_JOYSTICK		3
#define EXTENDER_JOYSTICK		1
#define LEFT_PROGRESS			7
#define LEFT_DEGRESS			5
#define RIGHT_PROGRESS			8
#define RIGHT_DEGRESS			6
#define COL_GRAB_RIGHT_BTN		14
#define COL_GRAB_LEFT_BTN		13
#define COL_MOTOR_FORWARD		2
#define COL_MOTOR_BACKWARDS		3
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

//PIDValues
#define PID_LIFT_UP 		.04,.00,.00
#define PID_LIFT_DOWN		.04,.00,.00

#endif
