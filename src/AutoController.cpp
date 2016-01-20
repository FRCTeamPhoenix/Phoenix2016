/*
 * AutoController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include "AutoController.h"
#include "RobotController.h"
#include <vector>
#include <cstdio>

AutoController::AutoController(DriveStation* ds, DriveTrainController* dt)
   : m_dstation(ds), m_drivet(dt)
{
   addAction(ACTION_DRIVE, 0.5f, 1000, 0.0f);
   addAction(ACTION_BRAKE);
}

AutoController::~AutoController() {}

void AutoController::run(void)
{
   performAction();
}

void AutoController::addAction(ActionType action, float pow, int ms, float turn)
{
   Action act(m_dstation, m_drivet, action, pow, ms, turn);
   m_queue.insert(m_queue.begin(), act);
}

void AutoController::performAction(void)
{
   if (m_queue.size() == 0)
      {
	 m_drivet->setCurrentState(DriveTrainController::NORMAL);
	 return;
      }
   Action current_action = m_queue.back();
   if (current_action())
      {
	 printf("Completed action.");
	 m_queue.pop_back();
      }
}
