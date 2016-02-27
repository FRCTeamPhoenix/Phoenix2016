/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader, Flywheel* flywheel, ConfigEditor* configEditor, Arm* arm, Aiming* aiming)
   : m_driveStation(ds), m_driveTrain(dt), m_shooterController(shooter), m_loaderController(loader), m_flywheel(flywheel), m_configEditor(configEditor), m_arm(arm), m_aiming(aiming)
{
   m_state = ROBOT_MANUAL;
}

RobotController::~RobotController() {}

void RobotController::run(void)
{
   if (m_state == ROBOT_AUTO)
      {
	 /* Y button cancels autonomous mode, resetting it to manual controls. */
	 if (m_driveStation->getGamepadButton(DriveStationConstants::buttonY)){
	    /* Simplest way to empty queue while destroying everything.
	       Not replacing with empty queue because that may not destroy
	       the objects inside. */
	    while (!m_queue.empty())
	       m_queue.pop();
	    m_driveTrain->stopRobot();
	    m_state = ROBOT_MANUAL;
	    return;
	 }
	 performAction();
      }
   else if (m_state == ROBOT_MANUAL)
      {
         if(m_driveStation->getGamepadButton(DriveStationConstants::buttonRB)){
            m_loaderController->start();
         }
         if(m_driveStation->getGamepadButton(DriveStationConstants::buttonLB)){
            m_loaderController->stop();
         }

         if(m_driveStation->getGamepadButton(DriveStationConstants::triggerRT)){
            m_flywheel->start();
         }
         if(m_driveStation->getGamepadButton(DriveStationConstants::triggerLT)){
            m_flywheel->stop();
         }

         m_arm->move(m_driveStation->deadzoneOfGamepadJoystick() / 2);

         return;
      }
}

void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
      {
         m_state = ROBOT_MANUAL;
         return;
      }

   Action *currentAction = m_queue.front();
   if (!currentAction->isInitialized())
      currentAction->init();

   if (currentAction->execute())
      {
         printf("Completed action.");
         delete currentAction;
         m_queue.pop();
      }
}
