/*
 * RobotController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#ifndef SRC_ROBOTCONTROLLER_H_
#define SRC_ROBOTCONTROLLER_H_

#include "DriveStation.h"

class RobotController {


public:
   RobotController(DriveStation * driveStation);

   virtual ~RobotController();

   void run();

private:
   DriveStation * m_driveStation;

};

#endif /* SRC_ROBOTCONTROLLER_H_ */
