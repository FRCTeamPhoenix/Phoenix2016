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
      m_driveTrain(robotDrive),
      m_driveStation(driveStation),
      m_leftWheelEncoder(leftWheelEncoder),
      m_rightWheelEncoder(rightWheelEncoder) {
   m_initalEncoderValueLeft = 0;
   m_initalEncoderValueRight = 0;
   m_targetTickRight = 0;
   m_targetTickLeft = 0;
   m_goalState = IDLE;
   m_rightMotorPower = 0.0f;
   m_leftMotorPower = 0.0f;
   m_rightEncoderComplete = true;
   m_leftEncoderComplete = true;
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
   switch (getCurrentState()) {
   case TELEOP:
      manualDrive(0.6f);
      break;
   //case TEST:
      //throttleRatio = (m_driveStation->getJoystickThrottle() + 1) / 2;
      //manualDrive(throttleRatio);
      //break;
   case IDLE:
      m_driveTrain->StopMotor();
      break;
   case ENCODERDRIVE:
      float leftMotorPower = 0.0f;
      float rightMotorPower = 0.0f;
      if (!m_rightEncoderComplete){
         rightMotorPower = m_rightMotorPower;
      }
      if (!m_leftEncoderComplete){
         leftMotorPower = m_leftMotorPower;
      }
      m_driveTrain->TankDrive(leftMotorPower, rightMotorPower);
      break;
   };
}

void DriveTrainController::aimRobotClockwise(float degree, float motorSpeed) {
   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
   //Will have to be changed to make it so the robot will move one degree instead of the wheels moving one degree
   float ticks = degree * RobotConstants::wheelEncoderTicksPerDegree;

   m_targetTickRight = m_initalEncoderValueRight - ticks;
   m_targetTickLeft = m_initalEncoderValueLeft + ticks;
   m_rightEncoderComplete = false;
   m_leftEncoderComplete = false;

   if (degree > 0) {
      m_rightMotorPower = -motorSpeed;
      m_leftMotorPower = motorSpeed;
   }
   else {
      m_rightMotorPower = motorSpeed;
      m_leftMotorPower = -motorSpeed;
   }
   m_goalState = ENCODERDRIVE;
}

void DriveTrainController::aimRobotCounterclockwise(float degree, float motorSpeed) {
   aimRobotClockwise(-degree, motorSpeed);
}

void DriveTrainController::moveRobotStraight(float distance, float motorSpeed){
   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
   //will have to find the diameter of the wheel
   //the 6 is the diameter of the wheel
   float ticks = distance * (M_PI* 6);
   m_targetTickRight = m_initalEncoderValueRight + ticks;
   m_targetTickLeft = m_initalEncoderValueLeft + ticks;
   m_rightEncoderComplete = false;
   m_leftEncoderComplete = false;

   if (distance > 0){
      m_rightMotorPower = motorSpeed;
      m_leftMotorPower = motorSpeed;
   }
   else {
      m_rightMotorPower = -motorSpeed;
      m_leftMotorPower = -motorSpeed;
   }
   m_goalState = ENCODERDRIVE;
}

void DriveTrainController::stopRobot() {
   m_goalState = IDLE;
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   switch(m_goalState){
   case TELEOP:
      return TELEOP;
   case ENCODERDRIVE:
      if (((m_rightMotorPower < 0) && (m_rightWheelEncoder->Get() <= m_targetTickRight)) ||
          ((m_rightMotorPower >= 0) && (m_rightWheelEncoder->Get() >= m_targetTickRight))){
         m_rightEncoderComplete = true;
      }
      if (((m_leftMotorPower < 0) && (m_leftWheelEncoder->Get() <= m_targetTickLeft)) ||
          ((m_leftMotorPower >= 0) && (m_leftWheelEncoder->Get() >= m_targetTickLeft))){
         m_leftEncoderComplete = true;
      }
      if (m_rightEncoderComplete && m_leftEncoderComplete){
         m_goalState = IDLE;
         return IDLE;
      }
      else {
         return ENCODERDRIVE;
      }
   default:
      return IDLE;
   }
}
