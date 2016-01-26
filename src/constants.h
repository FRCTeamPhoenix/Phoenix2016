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

namespace DriveStationConstants{
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

   const static std::string buttonNames[6] = {
         "New Name",
         "DB/Button 1",
         "DB/Button 2",
         "DB/Button 3",
         "Get Value",
         "Set Value"
   };

   const static std::string textBoxNames[13] = {
         "DB/String 0",
         "DB/String 1",
         "DB/String 2",
         "DB/String 3",
         "DB/String 4",
         "DB/String 5",
         "DB/String 6",
         "DB/String 7",
         "DB/String 8",
         "DB/String 9",
         "Key Name",
         "Key Value",
         "New Value"
   };

   const static uint32_t gamepadButtons = 12;
};
namespace ConfigVariables {
const static int numberOfVars = 1;
   const static std::string variables[numberOfVars] = {
         "teamNumber"
   };
   const static std::string types[numberOfVars] = {
         "int"
   };
};

#endif /* SRC_CONSTANTS_H_ */
