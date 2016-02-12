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
#include <math.h>
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
         LidarHandler* lidar);
   virtual ~DriveTrainController();
   void run();
   void manualDrive(float throttleRatio);
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
   LidarHandler* m_lidar;
   int32_t m_initalEncoderValueLeft;
   int32_t m_initalEncoderValueRight;
   int32_t m_targetTickRight;
   int32_t m_targetTickLeft;
   float m_rightMotorPower;
   float m_leftMotorPower;
   bool m_rightEncoderComplete;
   bool m_leftEncoderComplete;
   bool clockwise;
   float m_gyroTargetDegree;
   float lidarInches;
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
