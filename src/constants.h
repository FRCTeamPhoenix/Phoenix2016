#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct Port{
// Channels for wheels
   const static uint32_t frontLeftWheelMotor   = 1;
   const static uint32_t rearLeftWheelMotor    = 0;
   const static uint32_t frontRightWheelMotor  = 2;
   const static uint32_t rearRightWheelMotor   = 3;

//Flywheels
   const static uint32_t flywheels = 5; //Both on the same motor controller

// Controllers
   const static uint32_t joystick = 0;
   const static uint32_t gamepad = 1;
};

struct TachometerConstants {
   const static float voltageToInchesPerSecond = 1;
};


#endif /* SRC_CONSTANTS_H_ */
