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
      ConfigEditor* configEditor,
      LidarHandler* lidar):
      m_driveTrain(robotDrive),
      m_driveStation(driveStation),
      m_leftWheelEncoder(leftWheelEncoder),
      m_rightWheelEncoder(rightWheelEncoder),
      m_gyro(gyro),
      m_configEditor(configEditor),
      m_lidar(lidar){
   m_initalEncoderDistanceLeft = 0;
   m_initalEncoderDistanceRight = 0;
   m_targetDistanceRight = 0;
   m_targetDistanceLeft = 0;
   m_goalState = IDLE;
   m_rightMotorPower = 0.0f;
   m_leftMotorPower = 0.0f;
   m_targetDistanceRight = 0;
   m_targetDistanceLeft = 0;
   m_rightEncoderComplete = true;
   m_leftEncoderComplete = true;
   m_gyroTargetDegree = 0.0f;
   clockwise = false;
   lidarInches = 0.0f;


   //   m_leftDriveTrainController = new PIDController(0.2, 0, 0, m_leftWheelEncoder, this);
   //   m_rightDriveTrainController = new PIDController(0.2, 0, 0, m_rightWheelEncoder, this);
}

DriveTrainController::~DriveTrainController() {

}

// ThrottleRatio .8 is too high :(
void DriveTrainController::manualDrive() {

   float range = 0.7;

   float throttleRatio = (-m_driveStation->getJoystickThrottle()+ 1)/2;
   float throttle = m_driveStation->getYWithDeadzone();
   float twist = m_driveStation->getZWithDeadzone();
   float maxPower = (throttleRatio * range) + 0.3;

   m_leftMotorPower = (throttle * maxPower) + (twist * maxPower);
   m_rightMotorPower = (throttle * maxPower) - (twist * maxPower);

}

void DriveTrainController::run() {
   switch (getCurrentState()) {
   case CONTINUOUSDRIVE:
      break;
      //Goal state with the drivers are driving the robot
   case TELEOP:
      manualDrive();
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
      break;
   case LIDARDRIVE:
      if(lidarInches >= (m_lidar->getDistance() *2.54 + RobotConstants::lidarErrorRange))
      {
         if(m_leftMotorPower<0){
            m_leftMotorPower *= -1;
            m_rightMotorPower *= -1;
         }

      }
      else if (lidarInches <= (m_lidar->getDistance() *2.54 - RobotConstants::lidarErrorRange))
      {
         if(m_leftMotorPower>0){
            m_leftMotorPower *= -1;
            m_rightMotorPower *= -1;
         }
      }
      else{
         m_goalState = IDLE;
      }
      break;
   };
   m_driveTrain->TankDrive(m_leftMotorPower, m_rightMotorPower);
}

//For aiming the robot clockwise, pass in the desired degree and the desired motor speed
void DriveTrainController::aimRobotClockwise(float degree, float motorSpeed) {
   if (m_goalState == ENCODERDRIVE || m_goalState == GYROTURN){
      return;
   }
   if (RobotConstants::gyro){
      m_gyroTargetDegree = m_gyro->GetAngle() + degree;

      if (degree > 0) {
         clockwise = true;
         m_rightMotorPower = - motorSpeed;
         m_leftMotorPower = motorSpeed;
      }
      else {
         clockwise = false;
         m_rightMotorPower = motorSpeed;
         m_leftMotorPower = -motorSpeed;
      }
      m_goalState = GYROTURN;

   }
   else{
      m_initalEncoderDistanceRight = m_rightWheelEncoder->GetDistance();
      m_initalEncoderDistanceLeft = m_leftWheelEncoder->GetDistance();
      float distance = degree * m_configEditor->getFloat("wheelEncoderDistancePerDegree", 0.2093);

      m_targetDistanceRight = m_initalEncoderDistanceRight - distance;
      m_targetDistanceLeft = m_initalEncoderDistanceLeft + distance;
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
}
//For aiming the robot counter clockwise, pass in the desired degree and the desired motor speed
//Uses aimRobotClockwise but passes in a negative degree
void DriveTrainController::aimRobotCounterclockwise(float degree, float motorSpeed) {
   aimRobotClockwise(-degree, motorSpeed);
}
void DriveTrainController::continuousDrive(float motorSpeed){
   m_continuousDriveTimer.Reset();
   m_rightMotorPower = m_configEditor->getFloat("motorPower", 0.6);
   m_leftMotorPower = m_configEditor->getFloat("motorPower", 0.6);
   m_goalState = CONTINUOUSDRIVE;
}
//Moves the robot a desired distance and at a desired motor speed
void DriveTrainController::moveRobotStraight(float distance, float motorSpeed){

   if (m_goalState == ENCODERDRIVE){
      return;
   }
   m_initalEncoderDistanceRight = m_rightWheelEncoder->GetDistance();
   m_initalEncoderDistanceLeft = m_leftWheelEncoder->GetDistance();
   m_targetDistanceRight = m_initalEncoderDistanceRight + distance;


   m_targetDistanceLeft = m_initalEncoderDistanceLeft + distance;

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
      case ENCODERDRIVE:{
         if ((((m_rightMotorPower < 0) && (m_rightWheelEncoder->GetDistance() <= m_targetDistanceRight))) || (
               ((m_rightMotorPower >= 0) && (m_rightWheelEncoder->GetDistance() >= m_targetDistanceRight)))){
            m_rightEncoderComplete = true;
         }
         if ((((m_leftMotorPower < 0) && (m_leftWheelEncoder->GetDistance() <= m_targetDistanceLeft))) ||
               (((m_leftMotorPower >= 0) && (m_leftWheelEncoder->GetDistance() >= m_targetDistanceLeft)))){
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
      case LIDARDRIVE:
         return LIDARDRIVE;
      case CONTINUOUSDRIVE:
         if(m_continuousDriveTimer.HasPeriodPassed(.1)){
            return IDLE;
         }
         break;
      default:
         return IDLE;
      }
   }
   return IDLE;
}

void DriveTrainController::driveLidar(float inches, float motorSpeed){
   m_goalState = LIDARDRIVE;
   lidarInches = inches;
   m_rightMotorPower = motorSpeed;
   m_leftMotorPower = motorSpeed;
}


//Sets the goal state of the robot, used in changing the switch statements
void DriveTrainController::setGoalState(STATE goal){
   m_goalState = goal;
}
