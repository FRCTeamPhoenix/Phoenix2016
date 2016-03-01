/*
 * Arm.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: connortess
 */

#include <Arm.h>

Arm::Arm(
      Talon* armMotorLeft,
      Talon* armMotorRight,
      AnalogInput* leftPotentiometer,
      AnalogInput* rightPotentiometer,
      DigitalInput* leftUpperLimitSwitch,
      DigitalInput* rightUpperLimitSwitch,
      DigitalInput* leftLowerLimitSwitch,
      DigitalInput* rightLowerLimitSwitch,
      ConfigEditor* configEditor):
      m_armMotorLeft (armMotorLeft),
      m_armMotorRight (armMotorRight),
      m_leftPotentiometer (leftPotentiometer),
      m_rightPotentiometer (rightPotentiometer),
      m_leftUpperLimitSwitch (leftUpperLimitSwitch),
      m_rightUpperLimitSwitch (rightUpperLimitSwitch),
      m_leftLowerLimitSwitch (leftLowerLimitSwitch),
      m_rightLowerLimitSwitch (rightLowerLimitSwitch),
      m_configEditor(configEditor){
   m_armMotorPower = 0;
   m_goalState = MANUAL;
   PDRIVE = false;
   m_initalLeftPotentiometerValue = 0.0f;
   m_initalRightPotentiometerValue = 0.0f;
   m_goalLeftPotentiometerValue = 0.0f;
   m_goalRightPotentiometerValue = 0.0f;
   m_leftPotentiometerComplete = false;
   m_rightPotentiometerComplete = false;
}

Arm::~Arm() {

}

float Arm::manualDrive(){
   float power = 0.0;
   if (!PDRIVE){
      if(m_armMotorPower > 0){
         //if (!m_leftUpperLimitSwitch->Get() && !m_rightUpperLimitSwitch->Get()){
         if ((m_leftPotentiometer->GetVoltage() < RobotConstants::maxSoftLimitLeft) && (m_rightPotentiometer->GetVoltage() < RobotConstants::maxSoftLimitRight)){
            power = m_armMotorPower;
         }
         //}
      }
      if(m_armMotorPower < 0 ){
         //if (!m_leftLowerLimitSwitch->Get() && !m_rightLowerLimitSwitch->Get()){
         if ((m_leftPotentiometer->GetVoltage() > RobotConstants::minSoftLimitLeft) && (m_rightPotentiometer->GetVoltage() > RobotConstants::minSoftLimitRight)){
            power = m_armMotorPower;
         }
         //}
      }

   }
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
   return power;
}

void Arm::run(){

   float power = 0.0;

   std::ostringstream leftPotentiometer;
   leftPotentiometer << "LP Voltage: ";
   leftPotentiometer << m_leftPotentiometer->GetVoltage();
   SmartDashboard::PutString("DB/String 1", leftPotentiometer.str());

   std::ostringstream rightPotentiometer;
   rightPotentiometer << "RP Voltage: ";
   rightPotentiometer << m_rightPotentiometer->GetVoltage();
   SmartDashboard::PutString("DB/String 2", rightPotentiometer.str());

   switch (getCurrentState()) {
   case POTENTIOMETERDRIVE:
      if (m_rightPotentiometerComplete || m_leftPotentiometerComplete){
         m_goalState = MANUAL;
      }
      else
      {
         power = m_armMotorPower;
      }
      break;
   case MANUAL:
      power = manualDrive();
      break;
   }
   m_armMotorLeft->Set(power);
   m_armMotorRight->Set(power);
}

//void Arm::move(float motorPower){
//   PDRIVE = false;
//   m_armMotorPower = motorPower;
//}

void Arm::stop(){
   m_goalState = MANUAL;
}

//void Arm::angle(float angle,float motorpower){
//   m_armMotorPower = motorpower;
//   pAngle = angle;
//   PDRIVE = true;
//}

//The left goal needs to be in between 1.5 and 3.6
//The right goal needs to be in between 1.59 and 3.7
void Arm::moveArmToPosition(float leftGoal, float rightGoal){
   m_goalLeftPotentiometerValue = leftGoal;
   m_goalRightPotentiometerValue = rightGoal;
   m_initalLeftPotentiometerValue = m_leftPotentiometer->GetVoltage();
   m_initalRightPotentiometerValue = m_rightPotentiometer->GetVoltage();

   if((m_goalLeftPotentiometerValue < m_initalLeftPotentiometerValue) && (m_goalRightPotentiometerValue < m_initalRightPotentiometerValue)){
      m_armMotorPower = -(m_configEditor->getFloat("armMotorPower"));
   }
   else if((m_goalLeftPotentiometerValue > m_initalLeftPotentiometerValue) && (m_goalRightPotentiometerValue > m_initalRightPotentiometerValue)){
      m_armMotorPower = m_configEditor->getFloat("armMotorPower");
   }
   else{
      m_armMotorPower = 0;
   }
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
      if ((m_leftPotentiometer->GetVoltage() < RobotConstants::maxSoftLimitLeft) && (m_rightPotentiometer->GetVoltage() < RobotConstants::maxSoftLimitRight)){
         return MANUAL;
      }
      //}
      //if (!m_leftLowerLimitSwitch->Get() && !m_rightLowerLimitSwitch->Get()){
      if ((m_leftPotentiometer->GetVoltage() > RobotConstants::minSoftLimitLeft) && (m_rightPotentiometer->GetVoltage() > RobotConstants::minSoftLimitRight)){
         return MANUAL;
      }
      //}
      return MANUAL;
   default:
      return MANUAL;
   }
}
