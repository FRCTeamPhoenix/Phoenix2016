/*
 * Arm.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: connortess
 */

#include "Arm.h"

Arm::Arm(
      Talon* armMotorLeft,
      Talon* armMotorRight,
      AnalogInput* leftPotentiometer,
      AnalogInput* rightPotentiometer,
      DigitalInput* leftUpperLimitSwitch,
      DigitalInput* rightUpperLimitSwitch,
      DigitalInput* leftLowerLimitSwitch,
      DigitalInput* rightLowerLimitSwitch,
      ConfigEditor* configEditor,
      DriveStation* driveStation):
      m_armMotorLeft (armMotorLeft),
      m_armMotorRight (armMotorRight),
      m_leftPotentiometer (leftPotentiometer),
      m_rightPotentiometer (rightPotentiometer),
      m_leftUpperLimitSwitch (leftUpperLimitSwitch),
      m_rightUpperLimitSwitch (rightUpperLimitSwitch),
      m_leftLowerLimitSwitch (leftLowerLimitSwitch),
      m_rightLowerLimitSwitch (rightLowerLimitSwitch),
      m_configEditor(configEditor),
      m_driveStation(driveStation),
      m_leftControllerArm(m_armMotorLeft, m_leftPotentiometer, m_configEditor, m_configEditor->getFloat("potLeftValueHigh", 5 /*3.6*/), m_configEditor->getFloat("potLeftValueLow", 0/*1.55*/)),
      m_rightControllerArm(m_armMotorRight, m_rightPotentiometer, m_configEditor, m_configEditor->getFloat("potRightValueHigh", 5/*3.68*/), m_configEditor->getFloat("potRightValueLow", 0/*1.5*/))
{
   m_armMotorPower = 0;
   m_goalLeftPotentiometerValue = 0.0f;
   m_goalRightPotentiometerValue = 0.0f;
   m_leftPotentiometerComplete = false;
   m_rightPotentiometerComplete = false;
}

Arm::~Arm() {

}

void Arm::manualDrive(){
   SmartDashboard::PutString("DB/String 5", "InManualDrive");
   float adjust = m_driveStation->getGamepadJoystick();
   if(adjust < 0.1 && adjust > -0.1){
      adjust = 0;
   }
   std::ostringstream adjustSTR;
   adjustSTR << adjust;
   SmartDashboard::PutString("DB/String 5", adjustSTR.str());
   m_leftControllerArm.adjustTarget(adjust);
   m_rightControllerArm.adjustTarget(adjust);

}

void Arm::run(){
   manualDrive();
   m_leftControllerArm.run();
   m_rightControllerArm.run();
}

//left and right goal are between 0 and 1.
void Arm::moveArmToPosition(float goal){
   SmartDashboard::PutString("DB/String 9", "moveArmToPosition");
   m_leftControllerArm.setTarget(goal);
   m_rightControllerArm.setTarget(goal);
}

Arm::STATE Arm::getCurrentState(){
      if(m_rightControllerArm.atTarget(0.05) && m_leftControllerArm.atTarget(0.05)){
      return IDLE;
      }
      return PIDDRIVE;
}
