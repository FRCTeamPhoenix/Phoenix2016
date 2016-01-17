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
      TEST
   };
   DriveTrainController(RobotDrive*, DriveStation*);
   virtual ~DriveTrainController();
   void run();

   STATE getCurrentState();
   void setCurrentState(STATE currentState);

private:
   RobotDrive* m_driveTrain;
   DriveStation * m_driveStation;
   STATE m_currentState;
   void manualDrive(float throttleRatio);
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
