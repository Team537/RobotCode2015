#ifndef SCHEMATIC_H_
#define SCHEMATIC_H_

//Controller
#define HOARD_BTN 				11
#define TOTE_GRAB_BTN			3
#define AUTOSTACK_BTN			2
#define LEVEL_DOWN				5
#define LEVEL_UP				6
#define EXTENDER_IN				1
#define EXTENDER_OUT			4
#define SETPOINT_DOWN			7
#define SETPOINT_UP				8
#define MANUAL					9
#define AUTOMATIC				10
#define LEFT_VERTICAL			11
#define RIGHT_VERTICAL			12
#define COL_GRAB_RIGHT_AXIS		0
#define COL_GRAB_LEFT_AXIS		2
#define COL_MOTOR_LEFT			1
#define COL_MOTOR_RIGHT			3
#define JOYDEADBAND 			0.25
#define BUTTON_CAN				3

//Pistons
#define HOARDER					3

//Collector Pistons
#define GRAB_L_PISTON 	 		2
#define GRAB_R_PISTON 	 		6
#define COLLECTOR_ARMLF 		0
#define COLLECTOR_ARMRF 		5

//Stacker
#define STACKER_FLAPS 			0
#define STACKER_LEVEL_0			50
#define STACKER_LEVEL_1			100
#define STACKER_LEVEL_2			392
#define STACKER_LEVEL_3			570

//Victors
#define COLLECTOR_SUCKL 		0
#define COLLECTOR_SUCKR	 		1
#define STACKER_LIFT_RIGHT		4
#define STACKER_LIFT_LEFT		5
#define STACKER_EXTEND_RIGHT	2
#define STACKER_EXTEND_LEFT		3

//Constants
#define COLLECTOR_STATEINIT 	0
#define COLLECTOR_CONVSPD		0.5
#define COLLECTOR_CONVRAMP 		0.05

//Digital Inputs
#define STACKER_SWITCH_LEFT		0
#define STACKER_SWITCH_RIGHT	1

//Analog Inputs
#define STACKER_LIFT_POT_RIGHT	2
#define STACKER_LIFT_POT_LEFT	3

//Compressor
#define COMPRESSOR_SWITCH		5
#define COMPRESSOR_RELAY		1

//PIDValues for the Stacker on Capn hook
//#define STACKERLEFT	-.021,-.0000191,-.005
//#define STACKERRIGHT	.039, .000042, .005

//PIDValues for the Stacker on Dragon
#define STACKERLEFT -.02, -0.00012, -0.054
#define STACKERRIGHT -.02, -0.000151, -0.054

//Drive train Angle PID's on Capn hook
//#define PID_FRONT_LEFT_ANGLE 	-.0217, -.00026, -.0444, 15, 345, -1, 1
//#define PID_FRONT_RIGHT_ANGLE	 .0251,  .00029,  .0505, 15, 345, -1, 1
//#define PID_BACK_RIGHT_ANGLE	 .0289,  .00029,  .0489, 15, 345, -1, 1
//#define PID_BACK_LEFT_ANGLE	 .0301,  .00026,  .0633, 15, 345, -1, 1

//Drive train Angle PID's on Dragon
#define PID_FRONT_LEFT_ANGLE 			.0217,0.000320,.0431, 15, 345, -1,1
#define PID_FRONT_RIGHT_ANGLE 			.020,0.000350,0.05, 15, 345, -1, 1
#define PID_BACK_LEFT_ANGLE				.0217,0.00025,0.045, 15,345,-1,1
#define PID_BACK_RIGHT_ANGLE			.025,0.000220,0.05,15,345,-1,1

//Have Back  Modules as Replacements


//Drive train Velocity PID's on Capn hook

#define PID_FRONT_LEFT_VELOCITY		 	.04, 0, 0, 0
#define PID_FRONT_RIGHT_VELOCITY		.04, 0, 0, 0
#define PID_BACK_LEFT_VELOCITY			.04, 0, 0, 0
#define PID_BACK_RIGHT_VELOCITY 		.04, 0, 0, 0


//Drive train Velocity PID's on Dragon
//#define PID_FRONT_LEFT_VELOCITY 		.04, 0.0, 0.0, .5/515.808
//#define PID_FRONT_RIGHT_VELOCITY		.04, 0.0, 0.0, .5/440
//#define PID_BACK_LEFT_VELOCITY			.04, 0.0, 0.0, .5/477.852
//#define PID_BACK_RIGHT_VELOCITY 		.04, 0.0, 0.0, .5/476.224

//Drive train Distance PID's on Capn hook
//#define PID_FRONT_LEFT_DISTANCE		 	.04, 0, 0, 0
//#define PID_FRONT_RIGHT_DISTANCE		.04, 0, 0, 0
//#define PID_BACK_LEFT_DISTANCE			.04, 0, 0, 0
//#define PID_BACK_RIGHT_DISTANCE 		.04, 0, 0, 0

//Drive train Distance PID's on Dragon
#define PID_FRONT_LEFT_DISTANCE		 	.03, 0, 0.03
#define PID_FRONT_RIGHT_DISTANCE		.03, 0, 0.02
#define PID_BACK_LEFT_DISTANCE			.03, 0, 0.03
#define PID_BACK_RIGHT_DISTANCE			.03, 0, 0.03

//Stacker Heights
#define ZERO 	5
#define DRIVE 	100
#define ONE		300
#define TWO		500
#define THREE	750
#define CAN 	150

//Stacker Speed on Cap'n Hook
//#define LEFT_CAPS		-1,.9
//#define RIGHT_CAPS	-1,1

//Stacker Speed on Dragon
#define LEFT_CAPS		-.5,.4
#define RIGHT_CAPS		-.5,.35

//Names
#define RETRACT 0
#define EXTEND 1

//Autonomous Can States
#define INITIALIZE 			0
#define SETWHEEL_ANGLE 		1
#define FIRST_CAN 			7
#define RETRACT_STATE 		6
#define SECOND_CAN 			2
#define THIRD_CAN 			3
#define FOURTH_CAN 			4
#define	NEW_ANGLE			5
#define DRIVE_AWAY			8
#define DONE				9

//Current Dragon
//#define MAX_CURRENT	25

//Current Comp Bot
#define MAX_CURRENT 41

#endif
