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

class DriveTrainController : public BaseController{
public:
	enum STATE{
	   IDLE,
	   NORMAL,
	   AIMING_TARGET,
	   AIMING_OBSTACLE,
	   OBSTACLE,
	   TEST,
	   AUTO
	};
   DriveTrainController(RobotDrive*, DriveStation*, Encoder* leftWheelEncoder, Encoder* rightWheelEncoder);
   virtual ~DriveTrainController();
   void run();
   void manualDrive(float throttleRatio);
   void aimRobotRight(float degree);
   void aimRobotLeft(float degree);
   void stopRobot();

   STATE getCurrentState();
private:
   RobotDrive* m_driveTrain;
   DriveStation * m_driveStation;
   Encoder* m_leftWheelEncoder;
   Encoder* m_rightWheelEncoder;
   STATE m_goalState;
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
