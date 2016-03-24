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
   m_controller->SetSetpoint(m_potentiometer->GetAverageVoltage());
   m_currentVelocity = 0.0;
   m_profileSetPoint = voltageToPercent(m_potentiometer->GetAverageVoltage());
   m_desiredSetPoint = m_profileSetPoint;
}

void PIDControllerArm::setTarget(float targetPercent){
   if(targetPercent > 1.0)
      targetPercent = 1.0;
   if(targetPercent < 0.0)
      targetPercent = 0.0;

   m_desiredSetPoint = targetPercent;
}
/*
 * increment range [-1.0 .. 0 .. 1.0]
 */
void PIDControllerArm::adjustTarget(float increment){
   float newPercent = m_desiredSetPoint + (ACCELERATION * increment / (200));
   setTarget(newPercent);


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
   float currentPercent = voltageToPercent(m_potentiometer->GetAverageVoltage());
   return (currentPercent > (m_desiredSetPoint - m_desiredSetPoint * tolerance)) && (currentPercent < (m_desiredSetPoint + m_desiredSetPoint * tolerance));
}

void PIDControllerArm::PIDWrite(float output){
   float currentVoltage = m_potentiometer->GetAverageVoltage();

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


void PIDControllerArm::run(){
   float newSetPoint = accelerationProfile();
   m_controller->SetSetpoint(percentToVoltage(newSetPoint));
}






bool PIDControllerArm::armIsDeccelerating(){
   return (fabs(m_desiredSetPoint - m_profileSetPoint) < ((m_currentVelocity * m_currentVelocity) / (2.0f * ACCELERATION)));

}


float PIDControllerArm::accelerationProfile(){
   static int count = 0;

   //if we are close enough
   if(atTarget(0.05))
   {
      if(count % 10 == 0)
              printf("Count:%d, DSP:%4.5f PSP:%4.5f CVel:%4.5f CV:%4.5f\n ",
                    count, m_desiredSetPoint, m_profileSetPoint, m_currentVelocity, voltageToPercent(m_potentiometer->GetAverageVoltage()));
           count ++;
      m_currentVelocity = 0.0f;
      m_profileSetPoint = m_desiredSetPoint;
      return m_profileSetPoint;
   }

   bool isDeccel = armIsDeccelerating(); // slowing down in either direction????

   bool goingUp = (m_profileSetPoint < m_desiredSetPoint); // are we going up????
   float acceleration = 0.0f;

   //accelerating in either direction.
   if(goingUp && m_currentVelocity < MAX_VELOCITY)
   {
      acceleration = ACCELERATION;
   }
   if(!(goingUp) && m_currentVelocity > -MAX_VELOCITY)
   {
      acceleration = -ACCELERATION;
   }




   //declerating in either direction
   if(isDeccel)
   {
      acceleration = ACCELERATION;
      if(goingUp)
      {
         acceleration = -ACCELERATION;
      }

   }

   if(count % 10 == 0)
         printf("Count:%d, Decel:%c, DSP:%4.5f PSP:%4.5f CVel:%4.5f Acc:%4.5f CV:%4.5f\n ",
               count, isDeccel?'t':'f', m_desiredSetPoint, m_profileSetPoint, m_currentVelocity, acceleration, voltageToPercent(m_potentiometer->GetAverageVoltage()));
      count ++;

   m_currentVelocity += (acceleration / 200); //inches per second
   if(m_currentVelocity > MAX_VELOCITY){
      m_currentVelocity = MAX_VELOCITY;
   }
   if(m_currentVelocity < -MAX_VELOCITY){
      m_currentVelocity = -MAX_VELOCITY;
   }

   m_profileSetPoint += (m_currentVelocity / 200); // called 200 times per second
   if(m_profileSetPoint > 1.0){
      m_profileSetPoint = 1.0;
   }
   if(m_profileSetPoint < 0.0){
      m_profileSetPoint = 0.0;
   }



   return m_profileSetPoint;
}





















