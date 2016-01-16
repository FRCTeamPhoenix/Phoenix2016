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

class DriveTrainController : public BaseController{
public:
	enum STATE{
	   DRIVETRAIN_IDLE,
	   DRIVETRAIN_NORMAL,
	   DRIVETRAIN_AIMING_TARGET,
	   DRIVETRAIN_AIMING_OBSTACLE,
	   DRIVETRAIN_OBSTACLE
	};
   DriveTrainController();
   virtual ~DriveTrainController();
   void run();

   STATE getCurrentState();
private:
   Joystick m_joystick;
   RobotDrive m_driveTrain;
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
