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

}

DriveTrainController::~DriveTrainController() {

}
// ThrottleRatio .8 is too high :(
void DriveTrainController::manualDrive(float throttleRatio){
   float throttle = m_driveStation->getThrottle();
   float twist = m_driveStation->getTwist();
   float twistRatio = 1 - throttleRatio;

   float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
   float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

   m_driveTrain->TankDrive(leftPower, rightPower);
}

void DriveTrainController::run() {

   if(getCurrentState()== STATE::DRIVETRAIN_NORMAL){
      manualDrive(0.6f);
   }
   else if(getCurrentState()== STATE::DRIVETRAIN_TEST){
      float throttleRatio = (m_driveStation->getJoystickThrottle() + 1) / 2;// .8 is too high :(
      manualDrive(throttleRatio);
   }
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return STATE::DRIVETRAIN_TEST;
}
