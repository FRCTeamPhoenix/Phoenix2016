/*
 * DriveTrainController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_DRIVETRAINCONTROLLER_H_
#define SRC_DRIVETRAINCONTROLLER_H_

#include "BaseController.h"
#include "WPILib.h"
#include "constants.h"
#include "DriveStation.h"
#include "ConfigEditor.h"
#include "Math.h"
#include "LidarHandler.h"

class DriveTrainController: public BaseController, public PIDOutput {
public:
   enum STATE {
      IDLE,
      TELEOP,
      ENCODERDRIVE,
      GYROTURN,
      LIDARDRIVE,
      CONTINUOUSDRIVE
   };
   DriveTrainController(RobotDrive* m_driveTrain,
         DriveStation* m_driveStation,
         Encoder* leftWheelEncoder,
         Encoder* rightWheelEncoder,
         AnalogGyro* gyro,
         ConfigEditor* configEditor,
         LidarHandler* lidar);
   virtual ~DriveTrainController();

//   PIDController* m_leftDriveTrainController;
//   PIDController* m_rightDriveTrainController;

   void run();
   void manualDrive(float throttleRatio);
   void aimRobotClockwise(float degree, float motorSpeed);
   void aimRobotCounterclockwise(float degree, float motorSpeed);
   void moveRobotStraight(float distance, float motorSpeed);
   void stopRobot();
   void driveLidar(float meters, float motorSpeed);
   void continuousDrive(float motorSpeed);
//   void PIDWrite(float output);

   STATE getCurrentState();

   void setGoalState(STATE currentState);
   void setDriveConstants(float, float);

private:
   STATE m_goalState;
   RobotDrive* m_driveTrain;
   DriveStation * m_driveStation;
   Encoder* m_leftWheelEncoder;
   Encoder* m_rightWheelEncoder;
   AnalogGyro* m_gyro;
   ConfigEditor* m_configEditor;
   LidarHandler* m_lidar;
   int32_t m_initalDistanceLeft;
   int32_t m_initalDistanceRight;
   int32_t m_targetDistanceRight;
   int32_t m_targetDistanceLeft;
   Timer m_continuousDriveTimer;
   float m_rightMotorPower;
   float m_leftMotorPower;
   bool m_rightEncoderComplete;
   bool m_leftEncoderComplete;
   bool clockwise;
   float m_gyroTargetDegree;
   float lidarInches;

};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
