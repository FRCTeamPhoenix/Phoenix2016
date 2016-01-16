/*
 * DriveTrainController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_DRIVETRAINCONTROLLER_H_
#define SRC_DRIVETRAINCONTROLLER_H_

#include "BaseController.h"

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
	void run();
   virtual ~DriveTrainController();

   STATE getCurrentState();
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
