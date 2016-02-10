#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign {
   // Channels for wheels
   const static uint32_t rearLeftWheelMotor = 0;
   const static uint32_t frontLeftWheelMotor = 1;
   const static uint32_t frontRightWheelMotor = 2;
   const static uint32_t rearRightWheelMotor = 3;

   // Channels for wheel encoders
   const static uint32_t leftWheelEncoderChannelA = 0;
   const static uint32_t leftWheelEncoderChannelB = 1;
   const static uint32_t rightWheelEncoderChannelA = 2;
   const static uint32_t rightWheelEncoderChannelB = 3;

   //Flywheels
   const static uint32_t flywheelRightMotor = 5;
   const static uint32_t flywheelLeftMotor = 6; //Both on the same motor controller


   //Loader
   //Redo lifter motors
   const static uint32_t armMotorRight = 8;
   const static uint32_t armMotorLeft = 7;
   const static uint32_t intakeMotor = 4;
   const static uint32_t stationaryMotor = 9;
   const static uint32_t upperLimit = 4;
   const static uint32_t lowerLimit = 5;
   const static uint32_t loadedSensor = 6;
   const static uint32_t armEncoderChannelA = 7;
   const static uint32_t armEncoderChannelB = 8;

   // Controllers
   const static uint32_t joystick = 0;
   const static uint32_t gamepad = 1;

   //Analog
   const static uint32_t gyroscope = 0;
   const static uint32_t potentiometer = 1;


};

struct RobotConstants {
   constexpr static float wheelEncoderTicksPerDegree = 9.0f;
   // 384ticks per wheel rev. three rev. for 360 degrees.
   // (384 *3) / 360 = 3.2
   constexpr static float flywheelMotorSpeed = 1.0f;
};

struct DriveStationConstants {
   enum buttonNames {
      buttonX = 0,
      buttonA = 1,
      buttonB = 2,
      buttonY = 3,
      buttonLB = 4,
      buttonRB = 5,
      triggerLT = 6,
      triggerRT = 7,
      buttonBack = 8,
      buttonStart = 9,
      joystickLeftButton = 10,
      joystickRightButton = 11

   };
   const static uint32_t gamepadButtons = 12;
};

#endif /* SRC_CONSTANTS_H_ */

