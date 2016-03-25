/*
 * Climber.cpp
 *
 *  Created on: Mar 25, 2016
 *      Author: connortess
 */
#include "Climber.h"

Climber::Climber(Talon * motorLeft, Talon * motorRight,DriveStation * driveStation, DigitalInput * leftLimit, DigitalInput * rightLimit):
   m_motorLeft(motorLeft),
   m_motorRight(motorRight),
   m_driveStation(driveStation),
   m_leftLimit(leftLimit),
   m_rightLimit(rightLimit)

{

}
void Climber::run(){

   if(m_driveStation->getGamepadButton(DriveStationConstants::buttonB)){

      SmartDashboard::PutString("DB/String 4", "Flipping up");
      if (!m_leftLimit){
         m_motorLeft->Set(0.4f);

      }

      else {
         m_motorLeft->Set(0);
      }
      if (!m_rightLimit){
         m_motorRight->Set(0.4f);
      }
      else {
         m_motorRight->Set(0);

      }

   }
   else if(m_driveStation->getGamepadButton(DriveStationConstants::buttonX)){
      m_motorRight->Set(1.0f);
      m_motorLeft->Set(1.0f);
   }
   else {
      m_motorRight->Set(0);
      m_motorLeft->Set(0);
   }
}

