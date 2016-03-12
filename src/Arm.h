/*
 * Arm.h
 *
 *  Created on: Feb 16, 2016
 *      Author: connortess
 */

#ifndef SRC_ARM_H_
#define SRC_ARM_H_
#include "constants.h"
#include "DriveStation.h"
#include "ConfigEditor.h"
//#include "RobotController.h"
#include <cmath>

class Arm {

private:
   Talon* m_armMotorLeft;
   Talon* m_armMotorRight;
   AnalogInput* m_leftPotentiometer;
   AnalogInput* m_rightPotentiometer;
   DigitalInput* m_leftUpperLimitSwitch;
   DigitalInput* m_rightUpperLimitSwitch;
   DigitalInput* m_leftLowerLimitSwitch;
   DigitalInput* m_rightLowerLimitSwitch;
   ConfigEditor* m_configEditor;
   DriveStation* m_driveStation;
   float m_armMotorPower;
public:
   enum STATE{
      POTENTIOMETERDRIVE,
      MANUAL
   };
   Arm(
         Talon* armMotorLeft,
         Talon* armMotorRight,
         AnalogInput* leftPotentiometer,
         AnalogInput* rightPotentiometer,
         DigitalInput* leftUpperLimitSwitch,
         DigitalInput* rightUpperLimitSwitch,
         DigitalInput* leftLowerLimitSwitch,
         DigitalInput* rightLowerLimitSwitch,
         ConfigEditor* configEditor,
         DriveStation* driveStation);

   void move(float);
   void stop();
   void run();
   void moveArmToPosition(float);
   void manualDrive();
   void setMotors();
   float getAngleLeft();
   float getAngleRight();

   STATE getCurrentState();
   void setGoalState(STATE currentState);

   virtual ~Arm();

private:
   STATE m_goalState;
   float m_goalLeftPotentiometerValue;
   float m_goalRightPotentiometerValue;
   bool m_leftPotentiometerComplete;
   bool m_rightPotentiometerComplete;
};

#endif /* SRC_ARM_H_ */
