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
   m_initalEncoderValueLeft = 0;
   m_initalEncoderValueRight = 0;
   m_targetTickRight = 0;
   m_targetTickLeft = 0;
   m_goalState = IDLE;
   m_rightMotorPower = 0.0f;
   m_leftMotorPower = 0.0f;
   m_rightEncoderComplete = true;
   m_leftEncoderComplete = true;
   m_gyroTargetDegree = 0.0f;
   clockwise = false;
   lidarInches = 0.0f;
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


      m_initalEncoderValueRight = m_rightWheelEncoder->Get();
      m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
      float ticks = degree * RobotConstants::wheelEncoderTicksPerDegree;


      m_targetTickRight = m_initalEncoderValueRight - ticks;
      m_targetTickLeft = m_initalEncoderValueLeft + ticks;
      m_rightEncoderComplete = false;
      m_leftEncoderComplete = false;

      std::ostringstream outputTR;
      outputTR << "Target Right Tick " << m_targetTickRight;
      SmartDashboard::PutString("DB/String 8", outputTR.str());

      std::ostringstream outputTL;
      outputTL << "Target Left Tick " << m_targetTickLeft;
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
void DriveTrainController::continuousDrive(float motorSpeed){
   m_continuousDriveTimer.Reset();
   m_rightMotorPower = m_configEditor->getFloat("motorPower");
   m_leftMotorPower = m_configEditor->getFloat("motorPower");
   m_goalState = CONTINUOUSDRIVE;
}
//Moves the robot a desired distance and at a desired motor speed
void DriveTrainController::moveRobotStraight(float distance, float motorSpeed){
   printf("IN TEST THING/n");
   if (m_goalState == ENCODERDRIVE)
      return;

   //   m_initalEncoderValueRight = m_rightWheelEncoder->Get();
   //   m_initalEncoderValueLeft = m_leftWheelEncoder->Get();
   m_initalEncoderValueRight = m_rightWheelEncoder->GetDistance();
   m_initalEncoderValueLeft = m_leftWheelEncoder->GetDistance();
   //will have to find the diameter of the wheel
   //the 6 is the diameter of the wheel
   //  float ticks = distance * (M_PI* 6);
   // float ticks = distance * RobotConstants::ticksPerInch;
   m_targetTickRight = m_initalEncoderValueRight + distance;
   m_targetTickLeft = m_initalEncoderValueLeft + distance;

   std::ostringstream outputTR;
   outputTR << "T-Right " << m_targetTickRight;
   SmartDashboard::PutString("DB/String 2", outputTR.str());
   std::ostringstream outputTL;
   outputTL << "T-Left " << m_targetTickLeft;
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
void DriveTrainController::driveLidar(float inches, float motorSpeed)
{
   m_goalState = LIDARDRIVE;
   lidarInches = inches;
   m_rightMotorPower = motorSpeed;
   m_leftMotorPower = motorSpeed;
}


//Sets the goal state of the robot, used in changing the switch statements
void DriveTrainController::setGoalState(STATE goal){
   m_goalState = goal;
}
