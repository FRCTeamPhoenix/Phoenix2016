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
#include "Actions.h"
#include "ConfigEditor.h"
#include "constants.h"
#include "Arm.h"
#include "ActionSpinFlywheels.h"
#include "ActionTargetAim.h"
#include "ActionShoot.h"
#include "ActionDrive.h"
#include "Aiming.h"
#include <queue>

class RobotController : public BaseController
{
public:
   enum STATE {
      ROBOT_AUTO,
      ROBOT_MANUAL
   };

   RobotController(DriveStation*, DriveTrainController*, ShooterController*, LoaderController*, Flywheel*,
         ConfigEditor*, Arm*, Aiming*);
   virtual ~RobotController();
   void initAutonomousModeQueue();
   void setManual();
   void run();
   void performAction(void);
   void clearQueue();
private:
   STATE m_state;

   std::queue<Action*> m_queue;

   DriveStation* m_driveStation;
   DriveTrainController* m_driveTrain;
   ShooterController * m_shooterController;
   LoaderController * m_loaderController;
   Flywheel * m_flywheel;
   ConfigEditor * m_configEditor;
   Arm* m_arm;
   Aiming* m_aiming;
};

#endif /* SRC_ROBOTCONTROLLER_H_ */
