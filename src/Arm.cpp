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
   PDRIVE = false;
}

Arm::~Arm() {

}


void Arm::run(){

   std::ostringstream leftPotentiometer;
   leftPotentiometer << "LP Voltage: ";
   leftPotentiometer << m_leftPotentiometer->GetVoltage();
   SmartDashboard::PutString("DB/String 1", leftPotentiometer.str());

   std::ostringstream rightPotentiometer;
   rightPotentiometer << "RP Voltage: ";
   rightPotentiometer << m_rightPotentiometer->GetVoltage();
   SmartDashboard::PutString("DB/String 2", rightPotentiometer.str());

//   std::ostringstream limitSwitch;
//   limitSwitch << "BL: ";
//   limitSwitch << m_leftLowerLimitSwitch->Get();
//   limitSwitch << " BR: ";
//   limitSwitch << m_rightLowerLimitSwitch->Get();
//   limitSwitch << " FR: ";
//   limitSwitch << m_rightUpperLimitSwitch->Get();
//   limitSwitch << " FL: ";
//   limitSwitch << m_leftUpperLimitSwitch->Get();
//   SmartDashboard::PutString("DB/String 7", limitSwitch.str());

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
   m_armMotorLeft->Set(power);
   m_armMotorRight->Set(power);
}

void Arm::move(float motorPower){
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
   double relativeVoltLeft = (m_leftPotentiometer->GetVoltage() - m_configEditor->getFloat("potLeftValueLow"))/(m_configEditor->getFloat("potLeftValueHigh") - m_configEditor->getFloat("potLeftValueLow"));
   return relativeVoltLeft * (RobotConstants::maxTheta - RobotConstants::minTheta);
}

float Arm::getAngleRight(){
   double relativeVoltRight = (m_rightPotentiometer->GetVoltage() - m_configEditor->getFloat("potRightValueLow"))/(m_configEditor->getFloat("potRightValueHigh") - m_configEditor->getFloat("potRightValueLow"));
   return relativeVoltRight* (RobotConstants::maxTheta - RobotConstants::minTheta);
}
