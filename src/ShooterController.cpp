/*
 * ShooterController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <ShooterController.h>

ShooterController::ShooterController(LoaderController* loader, Flywheel * flywheel):
m_loaderController(loader),
m_flywheel(flywheel)
{
   m_goalState = OFF;
}

ShooterController::~ShooterController() {
}

void ShooterController::run(){
   switch(getGoalState()){
   case OFF:
      m_flywheel->stopMotors();
      //m_loaderController->setIdle();
      break;
   case ARMED:
      m_flywheel->startMotors(RobotConstants::flywheelMotorSpeed);
      break;
   case SHOOTING:
      //if (m_loaderController->getCurrentState() == LoaderController::STATE::LOADED) {
         m_loaderController->setShooting();
         m_flywheel->startMotors(RobotConstants::flywheelMotorSpeed);
    //}
      //else {
         //setOff();
      //}
      break;
   case ARMING:
   case STOPPING:
   case PREPARINGTOSHOOT:
      break;
   }
   m_flywheel->run();
}

void ShooterController::setArmed(){
   m_goalState = ARMED;
}

void ShooterController::setOff(){
   m_goalState = OFF;
   m_loaderController->setIdle();
}

void ShooterController::setShooting(){
   m_goalState = SHOOTING;

}

ShooterController::STATE ShooterController::getCurrentState(){
   STATE currentGoal = getGoalState();
   Flywheel::STATE flywheelState = m_flywheel->getCurrentState();
   LoaderController::STATE loaderState = m_loaderController->getCurrentState();
   if (currentGoal == ARMED){
      if(flywheelState == Flywheel::ON && loaderState == LoaderController::LOADED){
         return ARMED;
      }
      else {
         return ARMING;
      }
   }
   else if(currentGoal == SHOOTING){
      if(flywheelState == Flywheel::ON){
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
