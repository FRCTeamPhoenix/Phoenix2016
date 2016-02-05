/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader, LoaderSense* lsense, Aiming* aimer)
   : m_driveStation(ds), m_driveTrainController(dt), m_shooterController(shooter), m_loaderController(loader), m_loaderSense(lsense), m_aimer(aimer)
{
   m_state = ROBOT_AUTO;

   float args[2] = {1.0f, 0.5f};
   addAction(ACTION_DRIVE, 2, args);
}

RobotController::~RobotController() {}

void RobotController::run()
{
   if (m_state == ROBOT_AUTO)
      performAction();
   else if (m_state == ROBOT_MANUAL)
      {
	 // TODO: Set drivetrain state to manual and add button-press handling.
      }
}

void RobotController::addAction(ActionType action, int argc, float* argv)
{
   Action* act = new Action(m_driveStation, m_driveTrainController, m_loaderSense, m_aimer, action, argc, argv);
   m_queue.insert(m_queue.begin(), act);
}

void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
      {
	 //m_driveTrain->setCurrentState(DriveTrainController::NORMAL);
	 return;
      }
   Action *currentAction = m_queue.back();
   if (currentAction->execute())
      {
	 printf("Completed action.");
	 delete currentAction;
	 m_queue.pop_back();
      }
}
