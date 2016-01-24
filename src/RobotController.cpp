/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader)
   : m_dstation(ds), m_drivet(dt), m_shooter(shooter), m_loader(loader)
{
   m_state = ROBOT_AUTO;
}

RobotController::~RobotController() {}

void RobotController::run()
{
   if (m_state == ROBOT_AUTO)
      performAction();
   else if (m_state == ROBOT_MANUAL)
      {
	 m_drivet->run();
	 m_shooter->run();
	 m_loader->run();
      }
}

void RobotController::addAction(ActionType action, float pow, int ms, float turn)
{
   Action* act = new Action(m_dstation, m_drivet, action, pow, ms, turn);
   m_queue.insert(m_queue.begin(), act);
}

void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
      {
	 m_drivet->setCurrentState(DriveTrainController::NORMAL);
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
