/*
 * ShooterController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include "ShooterController.h"

ShooterController::ShooterController(LoaderController* loader, Flywheel * flywheel, ConfigEditor* configEditor):
m_loaderController(loader),
m_flywheel(flywheel),
m_configEditor(configEditor)
{
   m_goalState = OFF;
}

ShooterController::~ShooterController() {
}

void ShooterController::run(){
//   switch(getGoalState()){
//   case OFF:
//      m_flywheel->stop();
//      //m_loaderController->stop();
//      break;
//   case ARMED:
//      m_flywheel->start(m_configEditor->getFloat("flywheelMotorPower"));
//      break;
//   case SHOOTING:
//      if (m_loaderController->loaded()) {
//         m_loaderController->start();
//         m_flywheel->start(m_configEditor->getFloat("flywheelMotorPower"));
//      }
//      else {
//         setOff();
//      }
//      break;
//   case ARMING:
//   case STOPPING:
//   case PREPARINGTOSHOOT:
//      break;
  // }

   m_flywheel->run();
   m_loaderController->run();

}

void ShooterController::setArmed(){
   m_goalState = ARMED;
}

void ShooterController::setOff(){
   m_goalState = OFF;
}

void ShooterController::setShooting(){
   m_goalState = SHOOTING;
}

ShooterController::STATE ShooterController::getCurrentState(){
   STATE currentGoal = getGoalState();
   Flywheel::STATE flywheelState = m_flywheel->getCurrentState();


   if (currentGoal == ARMED){
      if(flywheelState == Flywheel::READY && m_loaderController->loaded()){
         return ARMED;
      }
      else {
         return ARMING;
      }
   }
   else if(currentGoal == SHOOTING){
      if(flywheelState == Flywheel::READY){
         return SHOOTING;
      }
      else{
         return PREPARINGTOSHOOT;
      }
   }
   else{
      if(flywheelState == Flywheel::OFF){
         return OFF;
      }
      else{
         return STOPPING;
      }
   }
}

ShooterController::STATE ShooterController::getGoalState(){
   return m_goalState;
}
