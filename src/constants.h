#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign {
   // Channels for wheels
   const static uint32_t rearLeftWheelMotor = 0;
   const static uint32_t frontLeftWheelMotor = 1;
   const static uint32_t frontRightWheelMotor = 2;
   const static uint32_t rearRightWheelMotor = 3;
   const static uint32_t stationaryMotor = 400;
   const static uint32_t flywheelRightMotor = 5;
   const static uint32_t flywheelLeftMotor = 6; //Both on the same motor controller
   const static uint32_t armMotorLeft = 7;
   const static uint32_t armMotorRight = 8;
   const static uint32_t intakeMotor = 4;
   const static uint32_t leftClimberMotor =20;
   const static uint32_t rightClimberMotor = 16;

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

   const static uint32_t leftClimberLimitSwitch =14;
   const static uint32_t rightClimberLimitSwitch =15;
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
};


#endif /* SRC_CONSTANTS_H_ */

