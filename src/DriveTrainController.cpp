/*
 * DriveTrainController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include "DriveTrainController.h"
#include <sstream>

DriveTrainController::DriveTrainController(
      RobotDrive* robotDrive,
      DriveStation* driveStation,
      Encoder* leftWheelEncoder,
      Encoder* rightWheelEncoder,
      AnalogGyro* gyro,
      ConfigEditor* configEditor):
      m_driveTrain(robotDrive),
      m_driveStation(driveStation),
      m_leftWheelEncoder(leftWheelEncoder),
      m_rightWheelEncoder(rightWheelEncoder),
      m_gyro(gyro),
      m_configEditor(configEditor){
   m_initalDistanceLeft = 0;
   m_initalDistanceRight = 0;
   m_targetDistanceRight = 0;
   m_targetDistanceLeft = 0;
   m_goalState = IDLE;
   m_rightMotorPower = 0.0f;
   m_leftMotorPower = 0.0f;
   m_rightEncoderComplete = true;
   m_leftEncoderComplete = true;
   m_gyroTargetDegree = 0.0f;
   clockwise = false;
}

DriveTrainController::~DriveTrainController() {

}

// ThrottleRatio .8 is too high :(
void DriveTrainController::manualDrive(float throttleRatio) {
   float throttle = m_driveStation->getYWithDeadzone();
   float twist = m_driveStation->getZWithDeadzone();
   float twistRatio = 1 - throttleRatio;

   if (fabs(throttle) > 0.01){
      m_leftMotorPower = (throttle * throttleRatio) + (twist * twistRatio);
      m_rightMotorPower = (throttle * throttleRatio) - (twist * twistRatio);
   }
   else{
      m_leftMotorPower = twist * throttleRatio;
      m_rightMotorPower = -twist * throttleRatio;
   }
}

void DriveTrainController::run() {
   switch (getCurrentState()) {

   //Goal state with the drivers are driving the robot
   case TELEOP:
      manualDrive(m_configEditor->getFloat("motorPower"));
      break;
      //Goal state of when the robot is not doing anything
   case IDLE:
      m_rightMotorPower = 0.0f;
      m_leftMotorPower = 0.0f;
      break;
      //Goal state of when the robot is moving by its self
   case ENCODERDRIVE:
      if (m_rightEncoderComplete){
         m_goalState = IDLE;

      }
      if (m_leftEncoderComplete){
         m_goalState = IDLE;

      }
      break;
   case GYROTURN:
      if (clockwise){
         if(m_gyroTargetDegree <= m_gyro->GetAngle())
            m_goalState = IDLE;
      }
      else{
         if(m_gyroTargetDegree >= m_gyro->GetAngle())
            m_goalState = IDLE;
      }
   };
   m_driveTrain->TankDrive(m_leftMotorPower, m_rightMotorPower);
}

//For aiming the robot clockwise, pass in the desired degree and the desired motor speed
void DriveTrainController::aimRobotClockwise(float degree, float motorSpeed) {
   if (m_goalState == ENCODERDRIVE || m_goalState == GYROTURN){
      return;
   }
   if (!RobotConstants::gyro){
      m_gyroTargetDegree = m_gyro->GetAngle() + degree;

      if (degree > 0) {
         clockwise = true;
         m_rightMotorPower = -(m_configEditor->getFloat("motorPower"));
         m_leftMotorPower = m_configEditor->getFloat("motorPower");
      }
      else {
         clockwise = false;
         m_rightMotorPower = m_configEditor->getFloat("motorPower");
         m_leftMotorPower = -(m_configEditor->getFloat("motorPower"));
      }
      m_goalState = GYROTURN;

   }
   else{


      m_initalDistanceRight = m_rightWheelEncoder->GetDistance();
      m_initalDistanceLeft = m_leftWheelEncoder->GetDistance();
      float distanceToRotate = degree * (RobotConstants::distancePerDegree / m_configEditor->getFloat("slipConstant"));


      m_targetDistanceRight = m_initalDistanceRight - distanceToRotate;
      m_targetDistanceLeft = m_initalDistanceLeft + distanceToRotate;
      m_rightEncoderComplete = false;
      m_leftEncoderComplete = false;

      std::ostringstream outputTR;
      outputTR << "Target Right Tick " << m_targetDistanceRight;
      SmartDashboard::PutString("DB/String 8", outputTR.str());

      std::ostringstream outputTL;
      outputTL << "Target Left Tick " << m_targetDistanceLeft;
      SmartDashboard::PutString("DB/String 9", outputTL.str());

      if (degree > 0) {
         m_rightMotorPower = -(m_configEditor->getFloat("motorPower"));
         m_leftMotorPower = m_configEditor->getFloat("motorPower");
      }
      else {
         m_rightMotorPower = m_configEditor->getFloat("motorPower");
         m_leftMotorPower = -(m_configEditor->getFloat("motorPower"));
      }
      m_goalState = ENCODERDRIVE;

   }
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

//   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
//   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
   m_initalDistanceRight = m_rightWheelEncoder->GetDistance();
   m_initalDistanceLeft = m_leftWheelEncoder->GetDistance();
   //will have to find the diameter of the wheel
   //the 6 is the diameter of the wheel
 //  float ticks = distance * (M_PI* 6);
  // float ticks = distance * RobotConstants::ticksPerInch;
   m_targetDistanceRight = m_initalDistanceRight + distance;
   m_targetDistanceLeft = m_initalDistanceLeft + distance;

   std::ostringstream outputTR;
   outputTR << "T-Right " << m_targetDistanceRight;
   SmartDashboard::PutString("DB/String 2", outputTR.str());
   std::ostringstream outputTL;
   outputTL << "T-Left " << m_targetDistanceLeft;
   SmartDashboard::PutString("DB/String 3", outputTL.str());

   m_rightEncoderComplete = false;
   m_leftEncoderComplete = false;

   if (distance > 0){
      m_rightMotorPower = m_configEditor->getFloat("motorPower");
      m_leftMotorPower = m_configEditor->getFloat("motorPower");
   }
   else {
      m_rightMotorPower = -(m_configEditor->getFloat("motorPower"));
      m_leftMotorPower = -(m_configEditor->getFloat("motorPower"));
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
      if (((m_rightMotorPower < 0) && (m_rightWheelEncoder->GetDistance() <= m_targetDistanceRight)) ||
            ((m_rightMotorPower >= 0) && (m_rightWheelEncoder->GetDistance() >= m_targetDistanceRight))){
         m_rightEncoderComplete = true;
      }
      if (((m_leftMotorPower < 0) && (m_leftWheelEncoder->GetDistance() <= m_targetDistanceLeft)) ||
            ((m_leftMotorPower >= 0) && (m_leftWheelEncoder->GetDistance() >= m_targetDistanceLeft))){
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
   case GYROTURN:

      return GYROTURN;
   default:
      return IDLE;
   }
}

//Sets the goal state of the robot, used in changing the switch statements
void DriveTrainController::setGoalState(STATE goal){
   m_goalState = goal;
}
