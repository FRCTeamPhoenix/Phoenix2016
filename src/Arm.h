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
#include "Math.h"

class Arm {

private:
   Talon* m_armMotorLeft;
   Talon* m_armMotorRight;
   AnalogPotentiometer* m_leftPotentiometer;
   AnalogPotentiometer* m_rightPotentiometer;
   DigitalInput* m_leftUpperLimitSwitch;
   DigitalInput* m_rightUpperLimitSwitch;
   DigitalInput* m_leftLowerLimitSwitch;
   DigitalInput* m_rightLowerLimitSwitch;
   ConfigEditor* m_configEditor;
   float m_armMotorPower;
   bool PDRIVE;
   float pAngle;
public:
   Arm(
         Talon* armMotorLeft,
         Talon* armMotorRight,
         AnalogPotentiometer* leftPotentiometer,
         AnalogPotentiometer* rightPotentiometer,
         DigitalInput* leftUpperLimitSwitch,
         DigitalInput* rightUpperLimitSwitch,
         DigitalInput* leftLowerLimitSwitch,
         DigitalInput* rightLowerLimitSwitch,
         ConfigEditor* configEditor);

   void move(float);
   void stop();
   void run();
   void angle(float,float);
   float getAngleLeft();
   float getAngleRight();
   virtual ~Arm();

};

#endif /* SRC_ARM_H_ */
