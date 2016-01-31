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
   const static uint32_t flywheelLeftMotor = 4; //Both on the same motor controller
   const static uint32_t flywheelRightMotor = 5;
   
   //Loader
   const static uint32_t verticalMotor = 6;
   const static uint32_t intakeMotor = 7;
   const static uint32_t stationaryMotor = 8;
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
   constexpr static float wheelEncoderTicksPerDegree = 1.06666667f;
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

};

#endif /* SRC_CONSTANTS_H_ */
