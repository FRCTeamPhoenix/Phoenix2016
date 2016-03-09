/*
 * Flywheel.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#include "Flywheel.h"

Flywheel::Flywheel(Talon* leftFlywheelMotor, Talon* rightFlywheelMotor, Encoder* leftFlywheelEncoder, Encoder* rightFlywheelEncoder, LidarHandler* lidar, ConfigEditor * configEditor) :
   m_leftFlywheelMotor(leftFlywheelMotor),
   m_rightFlywheelMotor(rightFlywheelMotor),
   m_leftFlywheelEncoder(leftFlywheelEncoder),
   m_rightFlywheelEncoder(rightFlywheelEncoder),
   m_lidar(lidar),
   m_leftFlywheelController(m_leftFlywheelMotor, m_rightFlywheelEncoder),
   m_rightFlywheelController(m_rightFlywheelMotor, m_rightFlywheelEncoder),
   m_configEditor(configEditor)
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
      SmartDashboard::PutString("DB/String 6", "OFF");

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
   m_leftFlywheelController.setRate(-rate);
   m_rightFlywheelController.setRate(rate);
}


float Flywheel::calculateSpeed() {
   float currentDistance = m_lidar->getFastAverage();

   std::ostringstream dist;
   dist << "lidar dist: " << currentDistance;
   SmartDashboard::PutString("DB/String 7", dist.str());

   float farPoint;
   float closePoint;
   float farPointRate;
   float closePointRate;

   if(currentDistance >= m_configEditor->getFloat("maxDistFlywheel", 120)){
      SmartDashboard::PutString("DB/String 6", "To Far");
      return m_configEditor->getFloat("maxDistFlywheelRate", 1900);
   }
   if(currentDistance <= m_configEditor->getFloat("minDistFlywheel", 24)){
      SmartDashboard::PutString("DB/String 6", "To close");
      return m_configEditor->getFloat("minDistFlywheelRate", 1900);
   }

   if((currentDistance >= m_configEditor->getFloat("midDistFlywheel", 72))){
      farPoint = m_configEditor->getFloat("maxDistFlywheel", 120);
      closePoint = m_configEditor->getFloat("midDistFlywheel", 72);
      farPointRate = m_configEditor->getFloat("maxDistFlywheelRate", 1900);
      closePointRate = m_configEditor->getFloat("midDistFlywheelRate", 1000);
   }
   else {
      farPoint = m_configEditor->getFloat("midDistFlywheel", 72);
      closePoint = m_configEditor->getFloat("minDistFlywheel", 24);
      farPointRate = m_configEditor->getFloat("midDistFlywheelRate", 1000);
      closePointRate = m_configEditor->getFloat("minDistFlywheelRate", 1900);
   }



   float deltaDistance = farPoint - closePoint;
   float maxToCurrent = farPoint - currentDistance;
   float minToCurrent = currentDistance - closePoint;


   float farFactor = 1 - (maxToCurrent / deltaDistance);
   float closeFactor = 1 - (minToCurrent / deltaDistance);

   float rate = (farFactor * farPointRate) + (closeFactor * closePointRate);
   SmartDashboard::PutString("DB/String 6", "Correct Range");
   return rate;
}













