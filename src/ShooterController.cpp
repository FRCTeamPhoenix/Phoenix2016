/*
 * ShooterController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <ShooterController.h>

ShooterController::ShooterController(Talon* leftFlywheelMotor, Talon* rightFlywheelMotor, LoaderController* loader):
   m_leftFlywheelMotor(leftFlywheelMotor),
   m_rightFlywheelMotor(rightFlywheelMotor),
   m_loaderController(loader)
{
   m_goalState = OFF;
}

ShooterController::~ShooterController() {
	// TODO Auto-generated destructor stub
}

void ShooterController::run(){
STATE current = getCurrentState();
LoaderController::STATE loaderState = m_loaderController->getCurrentState();

switch(getGoalState()){
   case OFF:
      if(current == ARMING ||current == SHOOTING){
         m_leftFlywheelMotor->Set(0.0f);
         m_rightFlywheelMotor->Set(0.0f);
      }
      break;
   case ARMED:
      if(current == ARMING ||current == SHOOTING){
         m_leftFlywheelMotor->Set(leftFlywheelMotorSpeed);
         m_rightFlywheelMotor->Set(rightFlywheelMotorSpeed);
      }
      break;
   case SHOOTING:
      if((current == ARMED ||current == ARMING) && loaderState == LoaderController::LOADED){
         m_leftFlywheelMotor->Set(leftFlywheelMotorSpeed);
         m_rightFlywheelMotor->Set(rightFlywheelMotorSpeed);
      }
      break;
   default:
      break;
   }
}
ShooterController::STATE ShooterController::getCurrentState(){
   STATE currentGoal = getGoalState();
   float leftFlywheel = m_leftFlywheelMotor->Get();
   float rightFlywheel = m_rightFlywheelMotor->Get();
   switch(currentGoal){
   case ARMED:
      if(leftFlywheel != 0 && rightFlywheel != 0 && m_loaderController->getCurrentState() == LoaderController::LOADED){
         return ARMED;
      }
      else {
         return ARMING;
      }
      break;
   case SHOOTING:
      if(leftFlywheel !=0 && rightFlywheel !=0){
         return SHOOTING;
      }
      else{
         return PREPARINGTOSHOOT;
      }
      break;
   case OFF:
      if(leftFlywheel == 0 && rightFlywheel == 0){
         return OFF;
      }
      else{
         return STOPPING;
      }
      break;
   }

}
ShooterController::STATE ShooterController::getGoalState(){
   return m_goalState;
}

