/*
 * Flywheel.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#include "Flywheel.h"

Flywheel::Flywheel(Talon* leftFlywheelMotor, Talon* rightFlywheelMotor, Encoder* leftFlywheelEncoder, Encoder* rightFlywheelEncoder, LidarHandler* lidar) :
   m_leftFlywheelMotor(leftFlywheelMotor),
   m_rightFlywheelMotor(rightFlywheelMotor),
   m_leftFlywheelEncoder(leftFlywheelEncoder),
   m_rightFlywheelEncoder(rightFlywheelEncoder),
   m_lidar(lidar),
   m_leftFlywheelController(m_leftFlywheelMotor, m_leftFlywheelEncoder),
   m_rightFlywheelController(m_rightFlywheelMotor, m_rightFlywheelEncoder)
{
   m_spinning = false;

}

Flywheel::~Flywheel() {
}

void Flywheel::run(){
   switch(getCurrentState()){
      case OFF:
         setRate(0.0);
         break;
      case NOTREADY:
      case READY:
         setRate(calculateSpeed());
         break;
   }
}
Flywheel::STATE Flywheel::getCurrentState(){
   if(!m_spinning){
      SmartDashboard::PutString("DB/String 5", "OFF");
      SmartDashboard::PutString("DB/String 6", " ");

      return OFF;
   }

   if(upToSpeed(0.05)){
      SmartDashboard::PutString("DB/String 5", "Ready To Fire");
      return READY;
   }
   else{
      SmartDashboard::PutString("DB/String 5", "Not Ready To Fire");
      return NOTREADY;
   }



}
void Flywheel::start(){
   m_spinning = true;
}

void Flywheel::stop(){
   m_spinning = false;
}

bool Flywheel::upToSpeed(float tolerance) {
   return m_leftFlywheelController.atTarget(tolerance) && m_rightFlywheelController.atTarget(tolerance);
}

void Flywheel::setRate(float rate) {
   m_leftFlywheelController.setRate(rate);
   m_rightFlywheelController.setRate(rate);
}


float Flywheel::calculateSpeed() {
   float currentDistance = m_lidar->getFastAverage();

   if(currentDistance < m_minDistance){
      SmartDashboard::PutString("DB/String 6", "To Close");
      return m_minDistanceRate;
   }
   if(currentDistance > m_maxDistance){
      SmartDashboard::PutString("DB/String 6", "To Far");
      return m_maxDistanceRate;
   }

   SmartDashboard::PutString("DB/String 6", "Correct Range");

   float deltaDistance = m_maxDistance - m_minDistance;
   float maxToCurrent = m_maxDistance - currentDistance;
   float minToCurrent = currentDistance - m_minDistance;


   float maxFactor = 1 - (maxToCurrent / deltaDistance);
   float minFactor = 1 - (minToCurrent / deltaDistance);

   float speed = (maxFactor * m_maxDistanceRate) + (minFactor * m_minDistanceRate);

   return speed;
}













