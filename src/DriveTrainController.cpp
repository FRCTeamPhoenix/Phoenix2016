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
   m_currentState = DriveTrainController::DRIVETRAIN_NORMAL;
}

DriveTrainController::~DriveTrainController() {

}

void DriveTrainController::run() {
if(getCurrentState()== STATE::DRIVETRAIN_NORMAL){
   float throttle = - m_driveStation->getJoystickY();

   if (fabs(throttle) < 0.05f) //This makes a deadzone
   {
       throttle = 0;
   }

   float twist = m_driveStation->getJoystickZ();
   if (fabs(twist) < 0.05f) //This also makes a deadzone
   {
      twist = 0;
   }
   float throttleRatio = 0.6f;// .8 is too high :(
   float twistRatio = 1 - throttleRatio;
   float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
   float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

   m_driveTrain->TankDrive(leftPower, rightPower);
}
else if(getCurrentState()== STATE::DRIVETRAIN_TEST){
   float throttle = - m_driveStation->getJoystickY();

      if (fabs(throttle) < 0.05f) //This makes a deadzone
      {
          throttle = 0;
      }

      float twist = m_driveStation->getJoystickZ();
      if (fabs(twist) < 0.05f) //This also makes a deadzone
      {
         twist = 0;
      }
      float throttleRatio = m_driveStation->getJoystickThrottle();// .8 is too high :(
      float twistRatio = 1 - throttleRatio;
      float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
      float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

      m_driveTrain->TankDrive(leftPower, rightPower);
}
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return m_currentState;
}

void DriveTrainController::setCurrentState(DriveTrainController::STATE state){
   m_currentState = state;

}

