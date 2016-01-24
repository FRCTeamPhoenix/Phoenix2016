#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign{
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

struct DriveStationConstants{
   enum buttonNames {
          buttonX = 1,
          buttonA = 2,
          buttonB = 3,
          buttonY = 4,
          buttonLB = 5,
          buttonRB = 6,
          triggerLT = 7,
          triggerRT = 8,
          buttonBack = 9,
          buttonStart = 10,
          joystickLeftButton = 11,
          joystickRightButton = 12
      };
   const static uint32_t gamepadButtons = 12;
};

struct AimingConstants {

   // Detected corners of target
   enum m_Coordinates {
         xUpperLeft,
         yUpperLeft,
         xUpperRight,
         yUpperRight,
         xLowerLeft,
         yLowerLeft,
         xLowerRight,
         yLowerRight
      };

   const static int numXYVals = 8;

   // These may need to be changed depending upon the chosen coordinate system
   const static int leftVisionBoundary = 30;
   const static int rightVisionBoundary = 225;
   const static int maxTiltingFactor = 20;

};

#endif /* SRC_CONSTANTS_H_ */
