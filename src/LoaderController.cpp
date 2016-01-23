/*
 * LoaderController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <LoaderController.h>


LoaderController::LoaderController(
      Talon* verticalMotor,
      Talon* intakeMotor,
      Talon* stationaryMotor,
      DigitalInput* upperLimit,
      DigitalInput* lowerLimit,
      DigitalInput* loadedSensor,
      Encoder* armEncoder):

      m_verticalMotor(verticalMotor),
      m_intakeMotor(intakeMotor),
      m_stationaryMotor(stationaryMotor),
      m_upperLimit(upperLimit),
      m_lowerLimit(lowerLimit),
      m_loadedSensor(loadedSensor),
      m_armEncoder(armEncoder)
      {
      m_goalState = HOMING;
      m_homingState = LOOKINGFORLOWERLIMIT;
	// TODO Auto-generated constructor stub

}

LoaderController::~LoaderController() {
	// TODO Auto-generated destructor stub
}

void LoaderController::moveArm(){
   bool atUpperLimit = m_upperLimit->Get();
   bool atLowerLimit = m_lowerLimit->Get();

   if (atUpperLimit /*&& Add direction of the arm*/){
      m_verticalMotor->Set(0);
   }
   else if (atLowerLimit /*&& Add direction of the arm*/){
      m_verticalMotor->Set(0);
   }
}

void LoaderController::angleOfArm(){

}

void LoaderController::homing(){
   m_verticalMotor->Set(0.0);

   if (m_homingState == LOOKINGFORLOWERLIMIT){
      if (m_lowerLimit->Get()){
         m_homingState = HOMINGCOMPLETE;
         m_goalState = EMPTY;
         m_armEncoder->Reset();
      }
      else {
         m_verticalMotor->Set(homingSpeed);
      }
   }
}

void LoaderController::run(){
   STATE current = getCurrentState();
   switch (getGoalState()){
   case HOMING:
      homing();
   case EMPTY:
      //set motors to 0 if loading or loaded
      if (current == LOADING || current == LOADED){
         m_intakeMotor->Set(0);
         m_stationaryMotor->Set(0);
      }
      break;
   case LOADED:
      //if empty turn on motors
      if (current == EMPTY){
         m_intakeMotor->Set(intakeMotorSpeed);
         m_stationaryMotor->Set(stationaryMotorSpeed);
      }
      //if loaded turn off motors
      else if (current == LOADED){
         m_intakeMotor->Set(0);
         m_stationaryMotor->Set(0);
      }
      break;
   default:
      break;
   }
   moveArm();
}


LoaderController::STATE LoaderController::getCurrentState() {
   if (m_loadedSensor->Get()){
      return LOADED;
   }
   if (m_intakeMotor->Get() != 0){
      return LOADING;
   }
   else {
      return EMPTY;
   }
}

LoaderController::STATE LoaderController::getGoalState(){
   return m_goalState;
}
