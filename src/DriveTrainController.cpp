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
      Encoder* rightWheelEncoder) :
      m_driveTrain(robotDrive), m_driveStation(driveStation),
      m_leftWheelEncoder(leftWheelEncoder),
      m_rightWheelEncoder(rightWheelEncoder) {
   m_initalEncoderValueLeft = 0;
   m_initalEncoderValueRight = 0;
   m_targetTickRight = 0;
   m_targetTickLeft = 0;
   m_goalState = IDLE;
}

DriveTrainController::~DriveTrainController() {

}
// ThrottleRatio .8 is too high :(
void DriveTrainController::manualDrive(float throttleRatio) {
   float throttle = m_driveStation->getJoystickThrottle();
   float twist = m_driveStation->getTwist();
   float twistRatio = 1 - throttleRatio;

   float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
   float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

   m_driveTrain->TankDrive(leftPower, rightPower);
}

void DriveTrainController::run() {
   float throttleRatio = 0;
   switch (getCurrentState()) {
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

void DriveTrainController::aimRobotClockwise(float degree, float motorSpeed) {
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
   if (degree > 0) {
      if (m_targetTickRight > m_initalEncoderValueRight) {
         rightPower = -motorSpeed;
      }
      if (m_targetTickLeft < m_initalEncoderValueLeft) {
         leftPower = motorSpeed;
      }
   } else {
      if (m_targetTickRight < m_initalEncoderValueRight) {
         rightPower = motorSpeed;
      }
      if (m_targetTickLeft > m_initalEncoderValueLeft) {
         leftPower = -motorSpeed;
      }
   }
   m_driveTrain->TankDrive(leftPower, rightPower);
   m_goalState = AUTO;
}

void DriveTrainController::aimRobotCounterclockwise(float degree,
      float motorSpeed) {
   aimRobotClockwise(-degree, motorSpeed);
}

void DriveTrainController::stopRobot() {
   m_goalState = IDLE;
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return m_currentState;
}

void DriveTrainController::setCurrentState(STATE currentState) {
   m_currentState = currentState;
}
