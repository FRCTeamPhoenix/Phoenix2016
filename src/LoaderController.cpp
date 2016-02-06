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
      Encoder* armEncoder,
      DriveStation* driveStation,
      AnalogPotentiometer* potentiometer):

      m_armMotorLeft(armMotorLeft),
      m_armMotorRight(armMotorRight),
      m_intakeMotor(intakeMotor),
      m_stationaryMotor(stationaryMotor),
      m_upperLimit(upperLimit),
      m_lowerLimit(lowerLimit),
      m_loadedSensor(loadedSensor),
      m_armEncoder(armEncoder),
      m_driveStation(driveStation),
      m_potentiometer(potentiometer)
{
   m_goalState = IDLE;
   m_homed = false;
}

LoaderController::~LoaderController() {
}

void LoaderController::moveArm(){
   bool atUpperLimit = m_upperLimit->Get();
   bool atLowerLimit = m_lowerLimit->Get();

   float power = m_driveStation->deadzoneOfGamepadJoystick();

   if (atUpperLimit && (power > 0.0)){
      power = 0;
   }
   if (atLowerLimit && (power < 0.0)){
      power = 0;
   }

   m_armMotorLeft->Set(power / 2);
   m_armMotorRight->Set(power / 2);
}

int LoaderController::angleOfArm(){
   float angle = m_potentiometer->Get();
   angle *= 0.733;
   return angle;
}

bool LoaderController::homed(){
   return m_homed;
}

bool LoaderController::loaded(){
   return m_loadedSensor->Get();
}

void LoaderController::run(){
   switch (getCurrentState()){
   case HOMING:
      m_armMotorLeft->Set(homingSpeed);
      m_armMotorRight->Set(homingSpeed);
      break;
   case IDLE:
      //set motors to 0 if loading or loaded
      m_armMotorLeft->Set(0.0);
      m_armMotorRight->Set(0.0);
      m_intakeMotor->Set(0);
      m_stationaryMotor->Set(0);
      break;
   case LOADING:
      m_intakeMotor->Set(-intakeMotorSpeed);
      m_stationaryMotor->Set(-stationaryMotorSpeed);
      break;
   case LOADED:
      m_intakeMotor->Set(0);
      m_stationaryMotor->Set(0);
      break;
   case SHOOTING:
      m_stationaryMotor->Set(-stationaryMotorSpeed);
      break;
   default:
      break;
   }
   moveArm();
}

LoaderController::STATE LoaderController::getCurrentState() {
   switch(m_goalState){
   case IDLE:
      return IDLE;
      break;
   case HOMING:
      if(m_lowerLimit->Get()){
         m_goalState = IDLE;
         m_homed = true;
         m_armEncoder->Reset();
         return IDLE;
      }
      return HOMING;
      break;
   case LOADING:
      if (loaded()){
         m_goalState = IDLE;
         return IDLE;
      }
      break;
   case SHOOTING:
      if (!loaded()){
         m_goalState = IDLE;
         return IDLE;
      }
      break;
   case LOADED:
      if (loaded()){
         m_goalState = IDLE;
         return IDLE;
      }
      else{
         return LOADED;
      }
      break;
   }
   return IDLE;
}

LoaderController::STATE LoaderController::getGoalState(){
   return m_goalState;
}

void LoaderController::setHoming(){
   m_goalState = HOMING;
   m_homed = false;
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

//Sets the goal state goal to IDLE
void LoaderController::setIdle(){
   m_goalState = IDLE;
}
