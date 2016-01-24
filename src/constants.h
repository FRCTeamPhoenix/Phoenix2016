#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign{
// Channels for wheels
   const static uint32_t frontLeftWheelMotor   = 1;
   const static uint32_t rearLeftWheelMotor    = 0;
   const static uint32_t frontRightWheelMotor  = 2;
   const static uint32_t rearRightWheelMotor   = 3;

// Channels for wheel encoders
   const static uint32_t leftWheelEncoderChannelA = 2;
   const static uint32_t leftWheelEncoderChannelB = 3;
   const static uint32_t rightWheelEncoderChannelA = 0;
   const static uint32_t rightWheelEncoderChannelB = 1;
   const static float tickPerDegree = 1.06666667;

//Flywheels
   const static uint32_t flywheels = 5; //Both on the same motor controller

// Controllers
   const static uint32_t joystick = 0;
   const static uint32_t gamepad = 1;



};

struct RobotConstants{
   const static float wheelEncoderTicksPerDegree = 1.06666667;
};


#endif /* SRC_CONSTANTS_H_ */
