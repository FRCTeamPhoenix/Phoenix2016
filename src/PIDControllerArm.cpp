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
   // TODO Auto-generated constructor stub
   m_potentiometer->SetPIDSourceType(PIDSourceType::kDisplacement);
   m_controller = new PIDController(0.00021, 0.00, 0.00, m_potentiometer, this);
   m_controller->SetTolerance(0.5);
   m_controller->SetPIDSourceType(PIDSourceType::kDisplacement);
}

void PIDControllerArm::setTarget(float target){
   m_controller->SetSetpoint(target);
}

bool PIDControllerArm::atTarget(float tolerance){
   double setPoint = m_controller->GetSetpoint();
   double target = m_potentiometer->GetVoltage();
   return (target > (setPoint - setPoint * tolerance)) && (target < (setPoint + setPoint * tolerance));
}

void PIDControllerArm::PIDWrite(float output){
   float currentVoltage = m_potentiometer->GetVoltage();

   if(output > 0 && currentVoltage > m_upperLimit){
     output = 0.0;
   }
   if(output < 0 && currentVoltage < m_upperLimit){
      output = 0.0;
   }
   m_armMotor->Set(output);
}

PIDControllerArm::~PIDControllerArm() {
   // TODO Auto-generated destructor stub
}

