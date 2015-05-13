#ifndef SCHEMATIC_H_
#define SCHEMATIC_H_

// Is this bot the competition bot?
#define COMPETITION_BOT true

// Is this bot the practice bot?
#define PRACTICE_BOT false

// Joystick deadband (how much off center the joystick can be before code takes notice.)
#define JOYDEADBAND 0.25

// Drive train Angle PID's on Capn hook
#define PID_COMPETITION_FRONT_LEFT_ANGLE -0.0217, -0.00026, -0.0444, 15, 345, -1, 1
#define PID_COMPETITION_FRONT_RIGHT_ANGLE 0.0251, 0.00029, 0.0505, 15, 345, -1, 1
#define PID_COMPETITION_BACK_RIGHT_ANGLE 0.0289, 0.00029, 0.0489, 15, 345, -1, 1
#define PID_COMPETITION_BACK_LEFT_ANGLE 0.0301, 0.00026, 0.0633, 15, 345, -1, 1

// Drive train Velocity PID's on Capn hook
#define PID_COMPETITION_FRONT_LEFT_VELOCITY	0.04, 0, 0, 0
#define PID_COMPETITION_FRONT_RIGHT_VELOCITY 0.04, 0, 0, 0
#define PID_COMPETITION_BACK_LEFT_VELOCITY 0.04, 0, 0, 0
#define PID_COMPETITION_BACK_RIGHT_VELOCITY 0.04, 0, 0, 0

// Drive train Distance PID's on Capn hook
#define PID_COMPETITION_FRONT_LEFT_DISTANCE 0.04, 0, 0
#define PID_COMPETITION_FRONT_RIGHT_DISTANCE 0.04, 0, 0
#define PID_COMPETITION_BACK_LEFT_DISTANCE 0.04, 0, 0
#define PID_COMPETITION_BACK_RIGHT_DISTANCE 0.04, 0, 0

// Drive train Angle PID's on Dragon
#define PID_PRACTICE_FRONT_LEFT_ANGLE 0.0217, 0.000320, 0.0431, 15, 345, -1, 1
#define PID_PRACTICE_FRONT_RIGHT_ANGLE 0.020, 0.000350, 0.0500, 15, 345, -1, 1
#define PID_PRACTICE_BACK_LEFT_ANGLE 0.0217, 0.00025, 0.0450, 15, 345, -1, 1
#define PID_PRACTICE_BACK_RIGHT_ANGLE 0.025, 0.000220, 0.0500, 15, 345, -1, 1

// Drive train Velocity PID's on Dragon
#define PID_PRACTICE_FRONT_LEFT_VELOCITY 0.040, 0.0, 0.0, 0.50 / 515.808
#define PID_PRACTICE_FRONT_RIGHT_VELOCITY 0.040, 0.0, 0.0, 0.50 / 440.000
#define PID_PRACTICE_BACK_LEFT_VELOCITY 0.040, 0.0, 0.0, 0.50 / 477.852
#define PID_PRACTICE_BACK_RIGHT_VELOCITY 0.040, 0.0, 0.0, 0.50 / 476.224

// Drive train Distance PID's on Dragon
#define PID_PRACTICE_FRONT_LEFT_DISTANCE 0.03, 0, 0.03
#define PID_PRACTICE_FRONT_RIGHT_DISTANCE 0.03, 0, 0.02
#define PID_PRACTICE_BACK_LEFT_DISTANCE 0.03, 0, 0.03
#define PID_PRACTICE_BACK_RIGHT_DISTANCE 0.03, 0, 0.03

// TODO: Have Replacement Modules PID's as backup

#endif
