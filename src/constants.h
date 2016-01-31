#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign {
   // Channels for wheels
   const static uint32_t frontLeftWheelMotor = 1;
   const static uint32_t rearLeftWheelMotor = 0;
   const static uint32_t frontRightWheelMotor = 2;
   const static uint32_t rearRightWheelMotor = 3;

   // Channels for wheel encoders
   const static uint32_t leftWheelEncoderChannelA = 2;
   const static uint32_t leftWheelEncoderChannelB = 3;
   const static uint32_t rightWheelEncoderChannelA = 0;
   const static uint32_t rightWheelEncoderChannelB = 1;

   //Flywheels
   const static uint32_t flywheelLeftMotor = 6; //Both on the same motor controller
   const static uint32_t flywheelRightMotor = 5;

   //Loader
   //Redo lifter motors
   // vertical motor is arm motor
   const static uint32_t verticalMotor = 8;
   const static uint32_t intakeMotor = 9;
   const static uint32_t stationaryMotor = 4;
   const static uint32_t upperLimit = 4;
   const static uint32_t lowerLimit = 5;
   const static uint32_t loadedSensor = 6;
   const static uint32_t armEncoderChannelA = 7;
   const static uint32_t armEncoderChannelB = 8;

   // Controllers
   const static uint32_t joystick = 0;
   const static uint32_t gamepad = 1;

};

struct RobotConstants {
   constexpr static float wheelEncoderTicksPerDegree = 3.2f;
  // 384ticks per wheel rev. three rev. for 360 degrees.
   // (384 *3) / 360 = 3.2
   constexpr static float flywheelMotorSpeed = 0.4f;
};

struct DriveStationConstants {
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

#endif /* SRC_CONSTANTS_H_ */

