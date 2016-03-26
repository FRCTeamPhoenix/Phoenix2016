/*
 * LoaderController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include "LoaderController.h"


LoaderController::LoaderController(
      Talon* intakeMotor,
      Talon* stationaryMotor,
      DigitalInput* loadedSensor,
      DriveStation* driveStation,
      ConfigEditor* configEditor):


      m_intakeMotor(intakeMotor),
      m_stationaryMotor(stationaryMotor),

      m_loadedSensor(loadedSensor),

      m_driveStation(driveStation),

      m_configEditor(configEditor)
{
   m_ballInRobot = loaded();
}

LoaderController::~LoaderController() {
}

//void LoaderController::moveArm(){
//   bool atUpperLimit = m_upperLimit->Get();
//   bool atLowerLimit = m_lowerLimit->Get();
//
//   float power = m_driveStation->deadzoneOfGamepadJoystick();
//
//   if (atUpperLimit && (power > 0.0)){
//      power = 0;
//   }
//   if (atLowerLimit && (power < 0.0)){
//      power = 0;
//   }
//
//   m_armMotorLeft->Set(power / 2);
//   m_armMotorRight->Set(power / 2);
//}
//
//int LoaderController::angleOfArm(){
//   float angle = m_potentiometer->Get();
//   angle *= 0.733;
//   return angle;
//}
//
//bool LoaderController::homed(){
//   return m_homed;
//}

bool LoaderController::loaded(){
   return !(m_loadedSensor->Get());
}
void LoaderController::run(){

   bool isLoaded = loaded();
      if (m_ballInRobot != isLoaded){
         stop();
      }


}
void LoaderController::start(){

      m_ballInRobot = loaded();
      m_stationaryMotor->Set(-(m_configEditor->getFloat("innerIntakeMotorPower", 1)));
      //m_intakeMotor->Set((m_configEditor->getFloat("outerIntakeMotorPower", 1)));

}
void LoaderController::lowGoal(){

      m_ballInRobot = loaded();
      m_stationaryMotor->Set(1);
     // m_intakeMotor->Set( -1);

}
void LoaderController::stop(){
   m_stationaryMotor->Set(0);
   m_intakeMotor->Set(0);
}
