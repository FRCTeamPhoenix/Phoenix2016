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
      m_driveStation(driveStation){
   m_armMotorPower = 0;
   m_goalState = MANUAL;
   m_goalLeftPotentiometerValue = 0.0f;
   m_goalRightPotentiometerValue = 0.0f;
   m_leftPotentiometerComplete = false;
   m_rightPotentiometerComplete = false;
}

Arm::~Arm() {

}
void Arm::setMotors(){
   SmartDashboard::PutString("DB/String 5", "InSetMotor");
   float powerLeft = 0.0f;
   float powerRight = 0.0f;

   float leftPotentiometer = m_leftPotentiometer->GetVoltage();
   float rightPotentiometer = m_rightPotentiometer->GetVoltage();

   std::ostringstream outputL;
   outputL << "PotL: ";
   outputL << (m_leftPotentiometer->GetVoltage());
   SmartDashboard::PutString("DB/String 2", outputL.str());
   std::ostringstream outputR;
   outputR << "PotR: ";
   outputR << (m_rightPotentiometer->GetVoltage());
   SmartDashboard::PutString("DB/String 3", outputR.str());

//   if((m_configEditor->getFloat("maxSoftLimitRight", 3.68) - m_configEditor->getFloat("minSoftLimitRight", 1.55)) * 0.05 < fabs(leftPotentiometer - rightPotentiometer)){
//      SmartDashboard::PutString("DB/String 5", "FarFromEachOther");
//      if(m_leftArmMotorPower > 0 && m_rightArmMotorPower > 0){
//         if(leftPotentiometer > rightPotentiometer){
//            powerLeft = m_leftArmMotorPower / 2;
//            powerRight = m_rightArmMotorPower;
//         }
//         if(rightPotentiometer > leftPotentiometer){
//            powerLeft = m_leftArmMotorPower;
//            powerRight = m_rightArmMotorPower / 2;
//         }
//      }
//      if(m_leftArmMotorPower < 0 && m_rightArmMotorPower < 0){
//         if(leftPotentiometer < rightPotentiometer){
//            powerLeft = m_leftArmMotorPower / 2;
//            powerRight = m_rightArmMotorPower;
//         }
//         if(rightPotentiometer < leftPotentiometer){
//            powerLeft = m_leftArmMotorPower;
//            powerRight = m_rightArmMotorPower / 2;
//         }
//      }
//   }

   if(m_leftArmMotorPower > 0 && m_rightArmMotorPower > 0){
      SmartDashboard::PutString("DB/String 5", "GoingUp");
      //if (!m_leftUpperLimitSwitch->Get() && !m_rightUpperLimitSwitch->Get()){
      if ((m_leftPotentiometer->GetVoltage() < m_configEditor->getFloat("potLeftValueHigh", 3.6)) &&
            (m_rightPotentiometer->GetVoltage() < m_configEditor->getFloat("potRightValueHigh", 3.68))){
         SmartDashboard::PutString("DB/String 8", "UpSetPower");
         powerLeft = m_leftArmMotorPower;
         powerRight = m_rightArmMotorPower;
      }
      //}
   }
   if(m_leftArmMotorPower < 0 && m_rightArmMotorPower < 0){
      SmartDashboard::PutString("DB/String 5", "GoingDown");
      //if (!m_leftLowerLimitSwitch->Get() && !m_rightLowerLimitSwitch->Get()){
      if ((m_leftPotentiometer->GetVoltage() > m_configEditor->getFloat("potLeftValueLow", 1.55)) &&
            (m_rightPotentiometer->GetVoltage() > m_configEditor->getFloat("potRightValueLow", 1.55))){
         SmartDashboard::PutString("DB/String 8", "DownSetPower");
         powerLeft = m_leftArmMotorPower;
         powerRight = m_rightArmMotorPower;
      }
      //}
   }
   m_armMotorLeft->Set(powerLeft);
   m_armMotorRight->Set(powerRight);
}
void Arm::manualDrive(){
   SmartDashboard::PutString("DB/String 5", "InManuualDrive");
   m_armMotorPower = m_driveStation->getGamepadJoystick() / 2;


   //   else{
   //      if (fabs(pAngle - getAngleLeft()) < RobotConstants::armDeadZone){
   //         //TODO add in limit switch logic
   //         if(pAngle < getAngleLeft()){
   //            if (!m_leftLowerLimitSwitch->Get() && !m_rightLowerLimitSwitch->Get()){
   //               power = m_armMotorPower;
   //            }
   //            //power =-m_armMotorPower;
   //         }
   //         else if(pAngle > getAngleLeft()){
   //            if (!m_leftUpperLimitSwitch->Get() && !m_rightUpperLimitSwitch->Get()){
   //               power = m_armMotorPower;
   //            }
   //            //power= m_armMotorPower;
   //         }
   //      }
   //   }
}

void Arm::run(){

   switch (getCurrentState()) {
   case POTENTIOMETERDRIVE:
      if (m_rightPotentiometerComplete && m_leftPotentiometerComplete){
         SmartDashboard::PutString("DB/String 4", "Complete");
         m_goalState = MANUAL;
      }
      else{
         SmartDashboard::PutString("DB/String 4", "Not Complete");
      }
      break;
   case MANUAL:
      manualDrive();
      break;
   }
   setMotors();
}

//void Arm::move(float motorPower){
//   PDRIVE = false;
//   m_armMotorPower = motorPower;
//}

void Arm::stop(){
   m_goalState = MANUAL;
}

//left and right goal are between 0 and 1.
void Arm::moveArmToPosition(float goal){
   float leftLowerLimit = m_configEditor->getFloat("potLeftValueLow");
   float rightLowerLimit = m_configEditor->getFloat("potRightValueLow");
   float leftUpperLimit = m_configEditor->getFloat("potLeftValueHigh");
   float rightUpperLimit = m_configEditor->getFloat("potRightValueHigh");

   float leftRange = leftUpperLimit - leftLowerLimit;
   float rightRange = rightUpperLimit - rightLowerLimit;


   m_goalLeftPotentiometerValue = (goal * leftRange) + leftLowerLimit;
   m_goalRightPotentiometerValue = (goal * rightRange) + rightLowerLimit;
   m_leftPotentiometerComplete = false;
   m_leftPotentiometerComplete = false;

   float initalLeftPotentiometerValue = m_leftPotentiometer->GetVoltage();
   float initalRightPotentiometerValue = m_rightPotentiometer->GetVoltage();

   if(m_leftPotentiometer->GetVoltage())

      if((m_goalLeftPotentiometerValue < initalLeftPotentiometerValue) &&
            (m_goalRightPotentiometerValue < initalRightPotentiometerValue)){
         m_armMotorPower = -(m_configEditor->getFloat("armMotorPower", 0.5));
      }
   if((m_goalLeftPotentiometerValue > initalLeftPotentiometerValue) &&
         (m_goalRightPotentiometerValue > initalRightPotentiometerValue)){
      m_armMotorPower = m_configEditor->getFloat("armMotorPower", 0.5);
   }
   //   else{
   //      m_armMotorPower = 0;
   //   }
   m_goalState = POTENTIOMETERDRIVE;
}

float Arm::getAngleLeft(){
   double relativeVoltLeft = (m_leftPotentiometer->GetVoltage() - m_configEditor->getFloat("potLeftValueLow"))/(m_configEditor->getFloat("potLeftValueHigh") - m_configEditor->getFloat("potLeftValueLow"));
   return relativeVoltLeft * (RobotConstants::maxTheta - RobotConstants::minTheta);
}

float Arm::getAngleRight(){
   double relativeVoltRight = (m_rightPotentiometer->GetVoltage() - m_configEditor->getFloat("potRightValueLow"))/(m_configEditor->getFloat("potRightValueHigh") - m_configEditor->getFloat("potRightValueLow"));
   return relativeVoltRight* (RobotConstants::maxTheta - RobotConstants::minTheta);
}

Arm::STATE Arm::getCurrentState(){
   switch(m_goalState){
   case POTENTIOMETERDRIVE:
      if ((((m_armMotorPower < 0) && (m_rightPotentiometer->GetVoltage() <= m_goalRightPotentiometerValue))) ||
            (((m_armMotorPower >= 0) && (m_rightPotentiometer->GetVoltage() >= m_goalRightPotentiometerValue)))){
         m_rightPotentiometerComplete = true;
      }
      if ((((m_armMotorPower < 0) && (m_leftPotentiometer->GetVoltage() <= m_goalLeftPotentiometerValue))) ||
            (((m_armMotorPower >= 0) && (m_leftPotentiometer->GetVoltage() >= m_goalLeftPotentiometerValue)))){
         m_leftPotentiometerComplete = true;
      }
      //if (!m_leftUpperLimitSwitch->Get() && !m_rightUpperLimitSwitch->Get()){
      //      if ((m_leftPotentiometer->GetVoltage() < RobotConstants::maxSoftLimitLeft) && (m_rightPotentiometer->GetVoltage() < RobotConstants::maxSoftLimitRight)){
      //         m_leftPotentiometerComplete = true;
      //      }
      //      //}
      //      //if (!m_leftLowerLimitSwitch->Get() && !m_rightLowerLimitSwitch->Get()){
      //      if ((m_leftPotentiometer->GetVoltage() > RobotConstants::minSoftLimitLeft) && (m_rightPotentiometer->GetVoltage() > RobotConstants::minSoftLimitRight)){
      //         return MANUAL;
      //      }
      //}
      return POTENTIOMETERDRIVE;
   default:
      return MANUAL;
   }
}
