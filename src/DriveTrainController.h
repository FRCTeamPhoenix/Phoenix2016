/*
 * DriveTrainController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_DRIVETRAINCONTROLLER_H_
#define SRC_DRIVETRAINCONTROLLER_H_

#include "BaseController.h"

enum DriveTrainStates{
   DRIVING
};

class DriveTrainController : public BaseController{
public:
   DriveTrainController();
	void run();
   virtual ~DriveTrainController();
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */
