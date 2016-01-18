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

class AutoController;

class RobotController : public BaseController{
public:
   enum STATE{
      AUTO,
      MANUAL
   };

   RobotController(DriveStation*, AutoController*);
   virtual ~RobotController();
   void run();
   DriveStation* getDriveStation(void);

private:
   DriveStation* m_driveStation;
   AutoController* m_auto;
};

#endif /* SRC_ROBOTCONTROLLER_H_ */
