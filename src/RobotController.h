/*
 * RobotController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#ifndef SRC_ROBOTCONTROLLER_H_
#define SRC_ROBOTCONTROLLER_H_


#include "DriveStation.h"
#include "BaseController.h"

class RobotController : public BaseController{
public:
   enum STATE{
      AUTO,
      MANUAL
   };

   RobotController(DriveStation * driveStation);
   virtual ~RobotController();
   void run();

private:
   DriveStation * m_driveStation;

};

#endif /* SRC_ROBOTCONTROLLER_H_ */
