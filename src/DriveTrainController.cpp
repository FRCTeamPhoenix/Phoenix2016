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

   //Goal state with the drivers are driving the robot
   case TELEOP:
      manualDrive(0.6f);
      break;
      //Goal state of when the robot is not doing anything
   case IDLE:
      m_rightMotorPower = 0.0f;
      m_leftMotorPower = 0.0f;
      break;
      //Goal state of when the robot is moving by its self
   case ENCODERDRIVE:
      float rightMotorPower = m_rightMotorPower;
      float leftMotorPower = m_leftMotorPower;

      if (m_rightEncoderComplete){
         m_goalState = IDLE;

      }
      if (m_leftEncoderComplete){
         m_goalState = IDLE;

      }
      m_driveTrain->TankDrive(leftMotorPower, rightMotorPower);
      break;
   };
}

//For aiming the robot clockwise, pass in the desired degree and the desired motor speed
void DriveTrainController::aimRobotClockwise(float degree, float motorSpeed) {
   if (m_goalState == ENCODERDRIVE){
      return;
   }

   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
   float ticks = degree * RobotConstants::wheelEncoderTicksPerDegree;


   m_targetTickRight = m_initalEncoderValueRight - ticks;
   m_targetTickLeft = m_initalEncoderValueLeft + ticks;
   m_rightEncoderComplete = false;
   m_leftEncoderComplete = false;

   std::ostringstream outputTR;
   outputTR << "Target Right Tick " << m_targetTickRight;
   SmartDashboard::PutString("DB/String 3", outputTR.str());

   std::ostringstream outputTL;
   outputTL << "Target Left Tick " << m_targetTickLeft;
   SmartDashboard::PutString("DB/String 4", outputTL.str());

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
//For aiming the robot counter clockwise, pass in the desired degree and the desired motor speed
//Uses aimRobotClockwise but passes in a negative degree
void DriveTrainController::aimRobotCounterclockwise(float degree, float motorSpeed) {
   aimRobotClockwise(-degree, motorSpeed);
}

//Moves the robot a desired distance and at a desired motor speed
void DriveTrainController::moveRobotStraight(float distance, float motorSpeed){
   printf("IN TEST THING/n");
   if (m_goalState == ENCODERDRIVE)
      return;

   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();

   //will have to find the diameter of the wheel
   //the 6 is the diameter of the wheel
   float ticks = distance * (M_PI* 6);
   m_targetTickRight = m_initalEncoderValueRight + ticks;
   m_targetTickLeft = m_initalEncoderValueLeft + ticks;

   std::ostringstream outputTR;
   outputTR << "T-Right " << m_targetTickRight;
   SmartDashboard::PutString("DB/String 2", outputTR.str());
   std::ostringstream outputTL;
   outputTL << "T-Left " << m_targetTickLeft;
   SmartDashboard::PutString("DB/String 3", outputTL.str());

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

//Set the goal state to IDLE
void DriveTrainController::stopRobot() {
   m_goalState = IDLE;
}

//Gets the current state of the robot
DriveTrainController::STATE DriveTrainController::getCurrentState() {
   switch(m_goalState){
   //Goal state of TELEOP, return TELEOP
   case TELEOP:
      return TELEOP;
      //Goal state of ENCODERDRIVE, tests if the encoders are where they are supposed to be
   case ENCODERDRIVE:
      if (((m_rightMotorPower < 0) && (m_rightWheelEncoder->Get() <= m_targetTickRight)) ||
          ((m_rightMotorPower >= 0) && (m_rightWheelEncoder->Get() >= m_targetTickRight))){
         m_rightEncoderComplete = true;
      }
      if (((m_leftMotorPower < 0) && (m_leftWheelEncoder->Get() <= m_targetTickLeft)) ||
          ((m_leftMotorPower >= 0) && (m_leftWheelEncoder->Get() >= m_targetTickLeft))){
         m_leftEncoderComplete = true;
      }
      if (m_rightEncoderComplete || m_leftEncoderComplete){
         m_goalState = IDLE;
         return IDLE;
      }
      else {
         m_goalState = ENCODERDRIVE;
         return ENCODERDRIVE;
      }
   default:
      return IDLE;
   }
}

//Sets the goal state of the robot, used in changing the switch statements
void DriveTrainController::setGoalState(STATE goal){
   m_goalState = goal;
}
