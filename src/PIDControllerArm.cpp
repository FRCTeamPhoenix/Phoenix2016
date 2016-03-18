/*
 * PIDControllerArm.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: connortess
 */

#include "PIDControllerArm.h"

PIDControllerArm::PIDControllerArm(Talon* armMotor,
      AnalogInput* potentiometer,
      float upperLimit,
      float lowerLimit):
      m_armMotor(armMotor),
      m_potentiometer(potentiometer),
      m_upperLimit(upperLimit),
      m_lowerLimit(lowerLimit){
   m_potentiometer->SetPIDSourceType(PIDSourceType::kDisplacement);
   m_controller = new PIDController(0.21, 0.00, 0.00, m_potentiometer, this);
   m_controller->SetTolerance(0.5);
   m_controller->SetPIDSourceType(PIDSourceType::kDisplacement);
   m_controller->SetOutputRange(-0.5, 0.5);
   m_controller->Enable();
}

void PIDControllerArm::setTarget(float target){
   m_controller->SetSetpoint(target);
}

void PIDControllerArm::adjustTarget(float increment){
   float newTarget = ((float)m_controller->GetSetpoint()) + increment;
   printf("%3.8f\n", newTarget);
   m_controller->SetSetpoint(newTarget);
}

bool PIDControllerArm::atTarget(float tolerance){
   double setPoint = m_controller->GetSetpoint();
   double target = m_potentiometer->GetVoltage();
   return (target > (setPoint - setPoint * tolerance)) && (target < (setPoint + setPoint * tolerance));
}

void PIDControllerArm::PIDWrite(float output){
   float currentVoltage = m_potentiometer->GetVoltage();

   if(output > 0.0 && currentVoltage > m_upperLimit){
     output = 0.0;
   }
   if(output < 0.0 && currentVoltage < m_upperLimit){
      output = 0.0;
   }
   m_armMotor->Set(output);
}

PIDControllerArm::~PIDControllerArm() {
}

float PIDControllerArm::getSetpoint(){
   return m_controller->GetSetpoint();
}
