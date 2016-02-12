/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader)
   : m_driveStation(ds), m_driveTrain(dt), m_shooterController(shooter), m_loaderController(loader)
{
   m_state = ROBOT_MANUAL;
}

RobotController::~RobotController() {}

void RobotController::run()
{
   if (m_state == ROBOT_AUTO)
      performAction();
   else if (m_state == ROBOT_MANUAL)
      {
	 if (m_driveStation->getGamepadButton(2))
	    {
	       m_state = ROBOT_AUTO;
	       m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, 12.0f, 0.5f));
	    }
      }
}

void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
      {
	 m_state = ROBOT_MANUAL;
	 return;
      }
   Action *currentAction = m_queue.back();
   if (!currentAction->isInitialized())
      currentAction->init();
   if (currentAction->execute())
      {
	 printf("Completed action.");
	 delete currentAction;
	 m_queue.pop_back();
      }
}
