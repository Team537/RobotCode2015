#ifndef SCHEMATIC_H_
#define SCHEMATIC_H_

#define JOYDEADBAND 			0.25
#define SPEED_MULTIPLYER 			0.40

//Drive train Angle PID's on Capn hook
#define PID_FRONT_LEFT_ANGLE 	-.0217, -.00026, -.0444, 15, 345, -1, 1
#define PID_FRONT_RIGHT_ANGLE	 .0251,  .00029,  .0505, 15, 345, -1, 1
#define PID_BACK_RIGHT_ANGLE	 .0289,  .00029,  .0489, 15, 345, -1, 1
#define PID_BACK_LEFT_ANGLE	 .0301,  .00026,  .0633, 15, 345, -1, 1

//Drive train Velocity PID's on Capn hook
#define PID_FRONT_LEFT_VELOCITY		 	.04, 0, 0, 0
#define PID_FRONT_RIGHT_VELOCITY		.04, 0, 0, 0
#define PID_BACK_LEFT_VELOCITY			.04, 0, 0, 0
#define PID_BACK_RIGHT_VELOCITY 		.04, 0, 0, 0

//Drive train Distance PID's on Capn hook
#define PID_FRONT_LEFT_DISTANCE		 	.04, 0, 0
#define PID_FRONT_RIGHT_DISTANCE		.04, 0, 0
#define PID_BACK_LEFT_DISTANCE			.04, 0, 0
#define PID_BACK_RIGHT_DISTANCE 		.04, 0, 0

#endif
