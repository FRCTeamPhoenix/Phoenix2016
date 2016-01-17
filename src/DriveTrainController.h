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
      DRIVETRAIN_IDLE,
      DRIVETRAIN_NORMAL,
      DRIVETRAIN_AIMING_TARGET,
      DRIVETRAIN_AIMING_OBSTACLE,
      DRIVETRAIN_OBSTACLE,
      DRIVETRAIN_TEST
   };
   DriveTrainController(RobotDrive*, DriveStation*);
   virtual ~DriveTrainController();
   void run();
   void manualDrive(float throttleRatio);

   STATE getCurrentState();
private:
   RobotDrive* m_driveTrain;
   DriveStation * m_driveStation;
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
