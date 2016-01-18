/*
 * DriveTrainController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include "DriveTrainController.h"

DriveTrainController::DriveTrainController(RobotDrive* robotDrive, DriveStation* driveStation) :
   m_driveTrain(robotDrive),
   m_driveStation(driveStation)
{
   m_currentState = IDLE;
}

DriveTrainController::~DriveTrainController() {

}
// ThrottleRatio .8 is too high :(
void DriveTrainController::manualDrive(float throttleRatio){
   float throttle = m_driveStation->getYWithDeadzone();
   float twist = m_driveStation->getTwist();
   float twistRatio = 1 - throttleRatio;

   float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
   float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

   m_driveTrain->TankDrive(leftPower, rightPower);
}

void DriveTrainController::run() {
   float throttleRatio = 0;
   switch(getCurrentState()){
   case NORMAL:
      manualDrive(0.6f);
      break;
   case TEST:
      throttleRatio = (m_driveStation->getJoystickThrottle() + 1) / 2;
      manualDrive(throttleRatio);
      break;
   case IDLE:
      m_driveTrain->StopMotor();
      break;
   case AIMING_TARGET:
      manualDrive(0.6f);
      break;
   case AIMING_OBSTACLE:
      manualDrive(0.6f);
      break;
   case OBSTACLE:
      manualDrive(0.6f);
      break;
   default:
      break;
   };
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return m_currentState;
}
void DriveTrainController::setCurrentState(STATE currentState){
   m_currentState = currentState;
}
