/*
 * DriveTrainController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include "DriveTrainController.h"

DriveTrainController::DriveTrainController(
      RobotDrive* robotDrive,
      DriveStation* driveStation,
      Encoder* leftWheelEncoder,
      Encoder* rightWheelEncoder,
      int32_t m_initalEncoderValueLeft,
      int32_t m_initalEncoderValueRight,
      int32_t m_targetTickRight,
      int32_t m_targetTickLeft
      ) :
   m_driveTrain(robotDrive),
   m_driveStation(driveStation),
   m_leftWheelEncoder(leftWheelEncoder),
   m_rightWheelEncoder(rightWheelEncoder),
   m_initalEncoderValueLeft(m_initalEncoderValueLeft),
   m_initalEncoderValueRight(m_initalEncoderValueRight),
   m_targetTickRight(m_targetTickRight),
   m_targetTickLeft(m_targetTickLeft)
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

void DriveTrainController::aimRobotClockwise(float degree, float motorSpeed){
   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
   float ticks = degree * RobotConstants::wheelEncoderTicksPerDegree;

   m_targetTickRight = m_initalEncoderValueRight - ticks;
   m_targetTickLeft = m_initalEncoderValueLeft + ticks;

   float rightPower = 0.0;
   float leftPower = 0.0;
   /*
    * For motor direction true means forward and false means backward
    */
   if (degree > 0){
      int m_rightMotorTurnDirection = -1;
      int m_leftMotorTurnDirection = 1;
      if (m_targetTickRight > m_initalEncoderValueRight){
         rightPower = -motorSpeed;
      }
      if (m_targetTickLeft < m_initalEncoderValueLeft){
         leftPower = motorSpeed;
      }
   }
   else {
      int m_rightMotorTurnDirection = 1;
      int m_leftMotorTurnDirection = -1;
      if (m_targetTickRight < m_initalEncoderValueRight){
         rightPower = motorSpeed;
      }
      if (m_targetTickLeft > m_initalEncoderValueLeft){
         leftPower = -motorSpeed;
      }
   }
   m_driveTrain->TankDrive(leftPower, rightPower);
   m_goalState = AUTO;
}

void DriveTrainController::aimRobotCounterclockwise(float degree, float motorSpeed){
   aimRobotClockwise(-degree, motorSpeed);
}

void DriveTrainController::stopRobot(){
   m_goalState = IDLE;
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return TEST;
}
