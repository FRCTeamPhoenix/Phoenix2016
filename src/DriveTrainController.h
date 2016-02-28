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
#include <cmath>
#include "LidarHandler.h"

class DriveTrainController: public BaseController {
public:
   enum STATE {
      IDLE,
      TELEOP,
      ENCODERDRIVE,
      GYROTURN,
      LIDARDRIVE
   };
   DriveTrainController(RobotDrive* m_driveTrain,
         DriveStation* m_driveStation,
         Encoder* leftWheelEncoder,
         Encoder* rightWheelEncoder,
         AnalogGyro* gyro,
         ConfigEditor* configEditor,
         LidarHandler* lidar);
   virtual ~DriveTrainController();
   void run();
   void manualDrive();
   void aimRobotClockwise(float degree, float motorSpeed);
   void aimRobotCounterclockwise(float degree, float motorSpeed);
   void moveRobotStraight(float distance, float motorSpeed);
   void stopRobot();
   void driveLidar(float meters, float motorSpeed);

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
   double m_initalEncoderDistanceLeft;
   double m_initalEncoderDistanceRight;
   double m_targetDistanceRight;
   double m_targetDistanceLeft;
   float m_rightMotorPower;
   float m_leftMotorPower;
   bool m_rightEncoderComplete;
   bool m_leftEncoderComplete;
   bool clockwise;
   float m_gyroTargetDegree;
   float lidarInches;

};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
