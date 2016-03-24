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
   m_currentVelocity = 0.0;
   m_profileSetPoint = voltageToPercent(m_potentiometer->GetVoltage());
}

void PIDControllerArm::setTarget(float targetPercent){
   m_controller->SetSetpoint(percentToVoltage(targetPercent));
}

/*
 * increment range [-1.0 .. 0 .. 1.0]
 */
void PIDControllerArm::adjustTarget(float increment){
   float newPercent = (voltageToPercent(m_controller->GetSetpoint())) + (ACCELERATION * increment);


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


void PIDControllerArm::run(){
   setTarget(accelerationProfile());
}





float ACCELERATION = 0.5;
float MAX_VELOCITY = 0.5;
bool PIDControllerArm::armIsDeccelerating(){
   return (fabs(m_desiredSetPoint - m_profileSetPoint) < ((m_currentVelocity * m_currentVelocity) / (2.0f * ACCELERATION)));

}


float PIDControllerArm::accelerationProfile(){
    //if we are close enough
    if(atTarget(0.3))
    {
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

    if(goingUp && m_currentVelocity > MAX_VELOCITY){
       m_currentVelocity = MAX_VELOCITY;
    }
    if(!goingUp && m_currentVelocity < -MAX_VELOCITY){
       m_currentVelocity = -MAX_VELOCITY;
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


    m_currentVelocity += (acceleration / 200); //inches per second
    m_profileSetPoint += (m_currentVelocity / 200); // called 200 times per second
    return m_profileSetPoint;
}





















