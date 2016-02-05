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

   //Flywheels
   const static uint32_t flywheelLeftMotor = 6; //Both on the same motor controller
   const static uint32_t flywheelRightMotor = 5;
   
   //Loader
   //Redo lifter motors
   const static uint32_t armMotorRight = 8;
   const static uint32_t armMotorLeft = 7;
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

struct DriveStationConstants{
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

// TARGET VALUES (SHOOTER)
struct AimingConstants {

   // Detected corners of target
   enum targetPositionData {
         xUL, // upper left x-coordinate
         yUL, // upper left y-coordinate
         xUR, // upper right x-coordinate
         yUR, // upper right y-coordinate
         xLL, // lower left x-coordinate
         yLL, // lower left y-coordinate
         xLR, // lower right x-coordinate
         yLR, // lower right y-coordinate
      };

   const static int numTargetVals = 8;

   // These are all educated guesses and may need to be changed,
   // depending upon the chosen coordinate system
   const static int leftTargetVisionBoundary = 30;
   const static int rightTargetVisionBoundary = 290;
   const static int maxTiltingFactor = 20;
   const static int minTargetWidth = 250;
   const static int maxTargetWidth = 350;

   // First array element passed in a target data array
   const static int targetFlag = 1;

};


// BALL VALUES (LOADER)
struct LoaderSenseConstants {

   enum ballPositionData {
         ballRadius,
         ballCenterX,
         ballCenterY
      };

   const static int numBallVals = 3;

   // All of these are basically placeholder values (educated guesses)

   const static int minGoodCenterX = 100;
   const static int maxGoodCenterX = 220;

   const static int minGoodRadius = 90;
   const static int maxGoodRadius = 120;

   const static int maxSafeRotationRadius = 50;

   // First array element passed in a loader data array
   const static int loaderFlag = 2;

};

#endif /* SRC_CONSTANTS_H_ */
