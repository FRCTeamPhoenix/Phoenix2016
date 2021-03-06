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
   const static uint32_t leftFlywheelEncoderChannelA = 6;
   const static uint32_t leftFlywheelEncoderChannelB = 7;
   const static uint32_t rightFlywheelEncoderChannelA = 4;
   const static uint32_t rightFlywheelEncoderChannelB = 5;


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
   const static uint32_t armJoystick = 2;

   //Analog
   const static uint32_t gyroscope = 0;
   const static uint32_t rightPotentiometer = 1;
   const static uint32_t leftPotentiometer = 2;

   //DIO
   const static uint32_t rightLowerLimitSwitch = 12;
   const static uint32_t rightUpperLimitSwitch = 13;
   const static uint32_t leftLowerLimitSwitch = 10; //how do you do extensions
   const static uint32_t leftUpperLimitSwitch = 11; //how do you do extensions
};

struct RobotConstants {
   constexpr static float wheelEncoderDistancePerDegree = 0.1406f;//4.5
   constexpr static float ticksPerInch = 32;
   // 384ticks per wheel rev. three rev. for 360 degrees.
   // (384 *3) / 360 = 3.2
   constexpr static float flywheelMotorSpeed = 1.0f;
   constexpr static bool gyro = false; //Determines which mode we use for turning.

   constexpr static double distancePerDegree = 0.2093;

   constexpr static int lidarErrorRange = 4;

   constexpr static const float armMotorLeftPower = 1.0f;
   constexpr static const float armMotorRightPower = 1.0f;
   constexpr static const float homingPower = -0.1f;

   //Constants for potentiometer
   constexpr static const float angleOffset = 9.14;
   constexpr static const float minTheta = 9.14;
   constexpr static const float maxTheta = 20.02;
   constexpr static const float minPotentiometerV = 0;
   constexpr static const float maxPotentiometerV = 0;
   constexpr static const double armDeadZone = 2;
   constexpr static const float maxSoftLimitLeft = 3.6;
   constexpr static const float maxSoftLimitRight = 3.68;
   constexpr static const float minSoftLimitLeft = 1.55;
   constexpr static const float minSoftLimitRight = 1.55;


   constexpr static const float maxDistFlywheelRate = 1950;
   constexpr static const float midDistFlywheelRate = 1550;
   constexpr static const float minDistFlywheelRate = 1950;

   constexpr static const float maxDistFlywheel = 10 * 12;
   constexpr static const float midDistFlywheel = 7 * 12;
   constexpr static const float minDistFlywheel = 4 * 12;

};
struct LidarConstants {
   const static int numberStoredValues = 100;
   constexpr static double periodToInches = 100000.0 / 2.54;
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

enum armButtons{
   buttonBottom = 1,
   buttonCDF = 2,
   buttonMiddle = 3,
   buttonDrawBridge = 4,
   buttonTop = 5

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

/*
struct AimingConstants{

   //Deteced corners of target
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

   const static int desiredCenter = 275; //untuned value not correct
   constexpr static double aimedDistance=84;//untuned value not correct

   const static int distanceVariance = 12; //in inches
   const static int rotationVariance = 15 ; //in pixels

   constexpr static double rotateCorrect=15; // in degrees

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
namespace ConfigVariables {
   const static int numberOfVars = 22;
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
         "potLeftValueLow",
         "potRightValueLow",
         "potLeftValueHigh",
         "potRightValueHigh",
         "wheelEncoderDistancePerDegree",
         "fastAverageFactor",
         "slowAverageFactor",
         "lidarOffset"
         "slipConstant",
         "PID_p",
         "PID_i",
         "PID_d"
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
         "float", //potLeftValueLow
         "float", //potRightValueLow
         "float", //potLeftValueHigh
         "float", //potRightValueHigh
         "float", //wheelEncoderDistancePerDegree
         "double", //fastAverageFactor
         "double", //slowAverageFactor,
         "double" //lidarOffset
   };
};
*/

struct AimingConstants{

   //Deteced corners of target
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

   const static int desiredCenter = 275; //untuned value not correct
   constexpr static double aimedDistance=84;//untuned value not correct

   const static int distanceVariance = 12; //in inches
   const static int rotationVariance = 15 ; //in pixels

   constexpr static double rotateCorrect=15; // in degrees

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
namespace ConfigVariables {
   const static int numberOfVars = 33;
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
      "potLeftValueLow",
      "potRightValueLow",
      "potLeftValueHigh",
      "potRightValueHigh",
      "wheelEncoderDistancePerDegree",
      "fastAverageFactor",
      "slowAverageFactor",
      "lidarOffset",
      "shooterPower",
      "maxDistFlywheel",
      "midDistFlywheel",
      "minDistFlywheel",
      "maxDistFlywheelRate",
      "midDistFlywheelRate",
      "minDistFlywheelRate",
      "armButtonBottom",
      "armButtonCDF",
      "armButtonMiddle",
      "armButtonDrawBridge",
      "armButtonTop",
      "armP",
      "armSensitivity"
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
      "float", //potLeftValueLow
      "float", //potRightValueLow
      "float", //potLeftValueHigh
      "float", //potRightValueHigh
      "float", //wheelEncoderDistancePerDegree
      "double", //fastAverageFactor
      "double", //slowAverageFactor,
      "double", //lidarOffset
      "float", //shooterPower
      "float", //maxDistFlywheel
      "float", //midDistFlywheel
      "float", //minDistFlywheel
      "float", //maxDistFlywheelRate
      "float", //midDistFlywheelRate
      "float", //minDistFlywheelRate
      "float", //armButtonBottom
      "float", //armButtonCDF
      "float", //armButtonMiddle
      "float", //armButtonDrawBridge
      "float", //armButtonTop
      "float", //armP
      "float", //armSensitivity
   };
};

#endif /* SRC_CONSTANTS_H_ */

