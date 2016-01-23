/*
 * DriveTrainController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include "DriveTrainController.h"

DriveTrainController::DriveTrainController(RobotDrive* robotDrive, DriveStation* driveStation, Encoder* leftWheelEncoder, Encoder* rightWheelEncoder) :
   m_driveTrain(robotDrive),
   m_driveStation(driveStation),
   m_leftWheelEncoder(leftWheelEncoder),
   m_rightWheelEncoder(rightWheelEncoder)
{
   m_goalState = IDLE;
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

   STATE currentState = getCurrentState();

   if(currentState == NORMAL){
      manualDrive(0.6f);
   }
   else if(currentState == TEST){
      float throttleRatio = (m_driveStation->getJoystickThrottle() + 1) / 2;// .8 is too high :(
      manualDrive(throttleRatio);
   }
   else if(currentState == AUTO){

   }
}

void DriveTrainController::aimRobotRight(float degree){
   m_goalState = AUTO;
}

void DriveTrainController::aimRobotLeft(float degree){
   m_goalState = AUTO;
}

void DriveTrainController::stopRobot(){
   m_goalState = IDLE;
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return TEST;
}
