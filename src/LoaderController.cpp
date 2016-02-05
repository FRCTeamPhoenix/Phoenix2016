/*
 * LoaderController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <LoaderController.h>


LoaderController::LoaderController(
      Talon* armMotorLeft,
      Talon* armMotorRight,
      Talon* intakeMotor,
      Talon* stationaryMotor,
      DigitalInput* upperLimit,
      DigitalInput* lowerLimit,
      DigitalInput* loadedSensor,
      Encoder* armEncoder):

      m_armMotorLeft(armMotorLeft),
      m_armMotorRight(armMotorRight),
      m_intakeMotor(intakeMotor),
      m_stationaryMotor(stationaryMotor),
      m_upperLimit(upperLimit),
      m_lowerLimit(lowerLimit),
      m_loadedSensor(loadedSensor),
      m_armEncoder(armEncoder)
{
   m_goalState = HOMING;
   m_homingState = LOOKINGFORLOWERLIMIT;

}

LoaderController::~LoaderController() {
}

void LoaderController::moveArm(){
   bool atUpperLimit = m_upperLimit->Get();
   bool atLowerLimit = m_lowerLimit->Get();

   if (atUpperLimit /*&& Add direction of the arm*/){
      m_armMotorLeft->Set(0);
      m_armMotorRight->Set(0);
   }
   else if (atLowerLimit /*&& Add direction of the arm*/){
      m_armMotorLeft->Set(0);
      m_armMotorRight->Set(0);
   }
}

int LoaderController::angleOfArm(){
   return 0;
}

void LoaderController::homing(){
   m_armMotorLeft->Set(0.0);
   m_armMotorRight->Set(0.0);

   if (m_homingState == LOOKINGFORLOWERLIMIT){
      if (m_lowerLimit->Get()){
         m_homingState = HOMINGCOMPLETE;
         m_goalState = EMPTY;
         m_armEncoder->Reset();
      }
      else {
         m_armMotorLeft->Set(homingSpeed);
         m_armMotorRight->Set(homingSpeed);
      }
   }
}

void LoaderController::run(){
   //STATE current = getCurrentState();
   switch (getGoalState()){
   case HOMING:
      SmartDashboard::PutString("DB/String 5", "HOMING");
      homing();
   case IDLE:
      //set motors to 0 if loading or loaded
      SmartDashboard::PutString("DB/String 5", "IDLE");
      m_intakeMotor->Set(0);
      m_stationaryMotor->Set(0);
      break;
   case LOADING:
      SmartDashboard::PutString("DB/String 5", "LOADING");
//      if (m_loadedSensor->Get()){
//         SmartDashboard::PutString("DB/String 4", "IN IF LOADING");
//         m_goalState = LOADED;
//      }
//      else{
         m_intakeMotor->Set(-intakeMotorSpeed);
         m_stationaryMotor->Set(-stationaryMotorSpeed);
//      }
      break;
   case LOADED:
      SmartDashboard::PutString("DB/String 5", "LOADED");
      m_intakeMotor->Set(0);
      m_stationaryMotor->Set(0);
      break;
   case SHOOTING:
      m_stationaryMotor->Set(-stationaryMotorSpeed);
      break;
   default:
      SmartDashboard::PutString("DB/String 5", "DEFAULT");
      break;
   }
   moveArm();
}


LoaderController::STATE LoaderController::getCurrentState() {
//   if (m_loadedSensor->Get()){
//      return LOADED;
//   }
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

void LoaderController::setHomed(){
   m_goalState = HOMED;
}

void LoaderController::setLoaded(){
   m_goalState = LOADED;
}

void LoaderController::startLoading(){
   m_goalState = LOADING;
}
void LoaderController::setShooting(){
   m_goalState = SHOOTING;
}

void LoaderController::setIdle(){
   m_goalState = IDLE;
}
