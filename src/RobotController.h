/*
 * RobotController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#ifndef SRC_ROBOTCONTROLLER_H_
#define SRC_ROBOTCONTROLLER_H_

#include "WPILib.h"
#include "BaseController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "ShooterController.h"
#include "LoaderController.h"
#include "Action.h"

class RobotController : public BaseController
{
 public:
   enum STATE {
      ROBOT_AUTO,
      ROBOT_MANUAL
   };

   RobotController(DriveStation*, DriveTrainController*, ShooterController*, LoaderController*);
   virtual ~RobotController();

   void run();
   void performAction(void);
 private:
   STATE m_state;

   std::vector<Action*> m_queue;

   DriveStation* m_driveStation;
   DriveTrainController* m_driveTrain;
   ShooterController * m_shooterController;
   LoaderController * m_loaderController;
};

#endif /* SRC_ROBOTCONTROLLER_H_ */
