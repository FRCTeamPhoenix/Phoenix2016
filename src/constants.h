#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign {
   // Channels for wheels
   const static uint32_t rearLeftWheelMotor = 0;
   const static uint32_t frontLeftWheelMotor = 1;
   const static uint32_t frontRightWheelMotor = 2;
   const static uint32_t rearRightWheelMotor = 3;
   const static uint32_t stationaryMotor = 4;
   const static uint32_t flywheelRightMotor = 5;
   const static uint32_t flywheelLeftMotor = 6; //Both on the same motor controller
   const static uint32_t armMotorLeft = 7;
   const static uint32_t armMotorRight = 8;
   const static uint32_t intakeMotor = 9;

   // Channels for wheel encoders
   const static uint32_t leftWheelEncoderChannelA = 0;
   const static uint32_t leftWheelEncoderChannelB = 1;
   const static uint32_t rightWheelEncoderChannelA = 2;
   const static uint32_t rightWheelEncoderChannelB = 3;

   //Flywheels


   //Loader
   //Redo lifter motors
   const static uint32_t upperLimit = 4;
   const static uint32_t lowerLimit = 5;
   const static uint32_t loadedSensor = 8;
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
   constexpr static float wheelEncoderTicksPerDegree = 4.5f;
   constexpr static float ticksPerInch = 32;
   // 384ticks per wheel rev. three rev. for 360 degrees.
   // (384 *3) / 360 = 3.2
   constexpr static float flywheelMotorSpeed = 1.0f;
   constexpr static bool gyro = true;

   constexpr static double rightDistancePerPulse = 1720/66;
   constexpr static double leftDistancePerPulse = 2475/66;
   constexpr static int lidarErrorRange = 4;
};

struct LidarConstants {
   const static int numberStoredValues = 100;
};

namespace DriveStationConstants {
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
   const static std::string dashButtonNames[6] = {
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

struct AimingConstants{

   //Detected corners of target
   enum targetPositionData {
      xUL = 1, // upper left x-coordinate
      yUL = 2, // upper left y-coordinate
      xUR = 3, // upper right x-coordinate
      yUR = 4, // upper right y-coordinate
      xLL = 5, // lower left x-coordinate
      yLL = 6, // lower left y-coordinate
      xLR = 7, // lower right x-coordinate
      yLR = 8, // lower right y-coordinate
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
      ballRadius = 1,
      ballCenterX = 2,
      ballCenterY = 3
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
namespace ConfigVariables {
const static int numberOfVars = 10;
   const static std::string variables[numberOfVars] = {
         "motorPower",
         "degree",
         "distance",
         "leftDistancePerPulse",
         "rightDistancePerPulse",
         "armMotorPower",
         "homingPower",
         "outerIntakeMotorPower",
         "innerIntakeMotorPower",
         "flywheelMotorPower",

   };
   const static std::string types[numberOfVars] = {
         "float", //motorPower
         "float", //degree
         "float", //distance
         "double", //leftDistancePerPulse
         "double", //rightDistancePerPulse
         "float", //armMotorPower
         "float", //homingPower
         "float", //outerIntakeMotorPower
         "float", //innerIntakeMotorPower
         "float", //flywheelMotorPower
   };
};

#endif /* SRC_CONSTANTS_H_ */

