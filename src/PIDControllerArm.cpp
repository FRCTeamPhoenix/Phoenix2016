/*
 * PIDControllerArm.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: connortess
 */

#include "PIDControllerArm.h"

PIDControllerArm::PIDControllerArm(Talon* armMotor,
      AnalogInput* potentiometer,
      ConfigEditor* configEditor,
      float upperLimit,
      float lowerLimit):
      m_armMotor(armMotor),
      m_potentiometer(potentiometer),
      m_configEditor(configEditor),
      m_upperLimit(upperLimit),
      m_lowerLimit(lowerLimit){
   m_potentiometer->SetPIDSourceType(PIDSourceType::kDisplacement);
   m_controller = new PIDController(m_configEditor->getFloat("armP", 9.00), (m_configEditor->getFloat("armI", 0.001)), 0.00, m_potentiometer, this);
   m_controller->SetTolerance(0);
   m_controller->SetPIDSourceType(PIDSourceType::kDisplacement);
   m_controller->SetOutputRange(-0.5, 0.5);
   m_controller->Enable();
   m_controller->SetSetpoint(m_potentiometer->GetVoltage());
}

void PIDControllerArm::setTarget(float targetPercent){
   m_controller->SetSetpoint(percentToVoltage(targetPercent));
}

void PIDControllerArm::adjustTarget(float increment){
   float newPercent = (voltageToPercent(m_controller->GetSetpoint())) + increment;
   printf("%9.8f\n", newPercent);
   m_controller->SetSetpoint(percentToVoltage(newPercent));
}

float PIDControllerArm::percentToVoltage(float goal){
   float limitGoal = goal;
   if(goal > 1.0){
      limitGoal = 1.0;
   }
   if(goal < 0.0){
      limitGoal = 0.0;
   }
   float range = m_upperLimit - m_lowerLimit;
   return (limitGoal * range) + m_lowerLimit;
}

float PIDControllerArm::voltageToPercent(float volts){
   float range = m_upperLimit - m_lowerLimit;
   float percent = (volts - m_lowerLimit) / range;
   return percent;
}

bool PIDControllerArm::atTarget(float tolerance){
   double setPoint = m_controller->GetSetpoint();
   double targetVoltage = m_potentiometer->GetVoltage();
   return (targetVoltage > (setPoint - setPoint * tolerance)) && (targetVoltage < (setPoint + setPoint * tolerance));
}

void PIDControllerArm::PIDWrite(float output){
   float currentVoltage = m_potentiometer->GetVoltage();

   if(output > 0.0 && currentVoltage > m_upperLimit){
     output = 0.0;
   }
   if(output < 0.0 && currentVoltage < m_lowerLimit){
      output = 0.0;
   }
   m_armMotor->Set(output);
}

PIDControllerArm::~PIDControllerArm() {
}

float PIDControllerArm::getSetpoint(){
   return voltageToPercent(m_controller->GetSetpoint());
}
