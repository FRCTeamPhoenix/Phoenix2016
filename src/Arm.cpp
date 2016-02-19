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
      AnalogPotentiometer* leftPotentiometer,
      AnalogPotentiometer* rightPotentiometer,
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
   PDRIVE = false;
}

Arm::~Arm() {

}


void Arm::run(){

   std::ostringstream leftPotentiometer;
   leftPotentiometer << "L Angle: ";
   leftPotentiometer << m_leftPotentiometer->Get();
   SmartDashboard::PutString("DB/String 3", leftPotentiometer.str());

   std::ostringstream rightPotentiometer;
   rightPotentiometer << "R Angle: ";
   rightPotentiometer << m_rightPotentiometer->Get();
   SmartDashboard::PutString("DB/String 4", rightPotentiometer.str());

   float power = 0.0;
   if (!PDRIVE)
   {
      std::ostringstream outputR;
      outputR << "power: ";
      outputR << (m_armMotorPower);
      SmartDashboard::PutString("DB/String 7", outputR.str() );
      if(m_armMotorPower > 0){
         SmartDashboard::PutString("DB/String 8", "greaterthan0");
         //if (!m_leftUpperLimitSwitch->Get() && !m_rightUpperLimitSwitch->Get()){
         if ((m_leftPotentiometer->Get() < RobotConstants::maxSoftLimitLeft) && (m_rightPotentiometer->Get() < RobotConstants::maxSoftLimitRight)){
            SmartDashboard::PutString("DB/String 8", "intheifUppter");
            power = m_armMotorPower;
         }
         //}
      }
      if(m_armMotorPower < 0 ){
         SmartDashboard::PutString("DB/String 8", "lessthan0");
         //if (!m_leftLowerLimitSwitch->Get() && !m_rightLowerLimitSwitch->Get()){
         if ((m_leftPotentiometer->Get() > RobotConstants::minSoftLimitLeft) && (m_rightPotentiometer->Get() > RobotConstants::minSoftLimitRight)){
            SmartDashboard::PutString("DB/String 8", "intheifLower");
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
   m_armMotorLeft->Set(power);
   m_armMotorRight->Set(power);
}

void Arm::move(float motorPower){
   SmartDashboard::PutString("DB/String 2", "In Move");
   PDRIVE = false;
   m_armMotorPower = motorPower;
}

void Arm::stop(){
   PDRIVE = false;
   m_armMotorPower = 0;
}

void Arm::angle(float angle,float motorpower){
   m_armMotorPower = motorpower;
   pAngle = angle;
   PDRIVE = true;
}

float Arm::getAngleLeft(){
   double relativeVoltLeft = (m_leftPotentiometer->Get() - m_configEditor->getFloat("potLeftValueLow"))/(m_configEditor->getFloat("potLeftValueHigh") - m_configEditor->getFloat("potLeftValueLow"));
   return relativeVoltLeft * (RobotConstants::maxTheta - RobotConstants::minTheta);
}

float Arm::getAngleRight(){
   double relativeVoltRight = (m_rightPotentiometer->Get() - m_configEditor->getFloat("potRightValueLow"))/(m_configEditor->getFloat("potRightValueHigh") - m_configEditor->getFloat("potRightValueLow"));
   return relativeVoltRight* (RobotConstants::maxTheta - RobotConstants::minTheta);
}
