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
#include "Aiming.h"
#include "Action.h"

class RobotController : public BaseController
{
 public:
   enum STATE {
      ROBOT_AUTO,
      ROBOT_MANUAL
   };

   RobotController(DriveStation*, DriveTrainController*, ShooterController*, LoaderController*, LoaderSense*, Aiming*);
   virtual ~RobotController();

   void run();
   void addAction(ActionType, int, float*);
   void performAction(void);
 private:
   STATE m_state;

   std::vector<Action*> m_queue;

   DriveStation* m_driveStation;
   DriveTrainController* m_driveTrainController;
   ShooterController* m_shooterController;
   LoaderController* m_loaderController;
   LoaderSense* m_loaderSense;
   Aiming* m_aimer;
};

#endif /* SRC_ROBOTCONTROLLER_H_ */
