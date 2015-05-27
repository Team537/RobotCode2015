#ifndef SCHEMATIC_H
#define SCHEMATIC_H

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

#define PI 3.1415926535897932384626433832795028841971

// Controller deadband (how much the joystick has to be moved before the code takes action, joysticks don't come fully back to the center!)
#define JOYSTICK_DEADBAND 0.25

// Is this robot the competition robot? Or is it the practice robot? (ONLY ONE CAN BE TRUE)
#define COMPETITION_ROBOT true
#define PRACTICE_ROBOT false

// Are you tuning this robot drive PID's?
#define TUNING_DRIVE_PID false

// Used when driving the robot, how much speed will be take off this is always set so the motors don't work at 100% and burn out.
#define DRIVE_MULTIPLIER 0.6

// When 'Turtle' mode is enables what will the drive & spin be multiplied by?
#define TURTLE_DRIVE_MULTIPLIER 0.7
#define TURTLE_SPIN_MULTIPLIER 0.8

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Drive train Angle PID's on Capn hook
#define PID_COMPETITION_FRONT_LEFT_ANGLE -0.0217, -0.00026, -.0444, 15, 345, -1, 1
#define PID_COMPETITION_FRONT_RIGHT_ANGLE 0.0251, 0.00029, 0.0505, 15, 345, -1, 1
#define PID_COMPETITION_BACK_RIGHT_ANGLE 0.0289, 0.00029, 0.0489, 15, 345, -1, 1
#define PID_COMPETITION_BACK_LEFT_ANGLE 0.0301, 0.00026, 0.0633, 15, 345, -1, 1

// Drive train Velocity PID's on Capn hook
#define PID_COMPETITION_FRONT_LEFT_VELOCITY	0.04, 0, 0, 0
#define PID_COMPETITION_FRONT_RIGHT_VELOCITY 0.04, 0, 0, 0
#define PID_COMPETITION_BACK_LEFT_VELOCITY 0.04, 0, 0, 0
#define PID_COMPETITION_BACK_RIGHT_VELOCITY 0.04, 0, 0, 0

// Drive train Distance PID's on Capn hook
#define PID_COMPETITION_FRONT_LEFT_DISTANCE	0.04, 0, 0
#define PID_COMPETITION_FRONT_RIGHT_DISTANCE 0.04, 0, 0
#define PID_COMPETITION_BACK_LEFT_DISTANCE 0.04, 0, 0
#define PID_COMPETITION_BACK_RIGHT_DISTANCE 0.04, 0, 0

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Drive train Angle PID's on Dragon
#define PID_PRACTICE_FRONT_LEFT_ANGLE 0.0217, 0.000320, 0.0431, 15, 345, -1, 1
#define PID_PRACTICE_FRONT_RIGHT_ANGLE 0.020, 0.000350, 0.0500, 15, 345, -1, 1
#define PID_PRACTICE_BACK_LEFT_ANGLE 0.0217, 0.000250, 0.04500, 15, 345, -1, 1
#define PID_PRACTICE_BACK_RIGHT_ANGLE 0.025, 0.000220, 0.0500, 15, 345, -1, 1

// Drive train Velocity PID's on Dragon
#define PID_PRACTICE_FRONT_LEFT_VELOCITY 0.04, 0.0, 0.0, (0.5 / 515.808)
#define PID_PRACTICE_FRONT_RIGHT_VELOCITY 0.04, 0.0, 0.0, (0.5 / 440.000)
#define PID_PRACTICE_BACK_LEFT_VELOCITY 0.04, 0.0, 0.0, (0.5 / 477.852)
#define PID_PRACTICE_BACK_RIGHT_VELOCITY 0.04, 0.0, 0.0, (0.5 / 476.224)

// Drive train Distance PID's on Dragon
#define PID_PRACTICE_FRONT_LEFT_DISTANCE 0.03, 0, 0.03
#define PID_PRACTICE_FRONT_RIGHT_DISTANCE 0.03, 0, 0.02
#define PID_PRACTICE_BACK_LEFT_DISTANCE 0.03, 0, 0.03
#define PID_PRACTICE_BACK_RIGHT_DISTANCE 0.03, 0, 0.03

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// TODO: Have extra modules PID's as replacements.

#endif
