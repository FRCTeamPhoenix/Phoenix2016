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

AutoController::AutoController(DriveStation* ds)
   : m_dstation(ds)
{
   addAction(ACTION_A);
   addAction(ACTION_B);
   addAction(ACTION_X);
   addAction(ACTION_B);
   addAction(ACTION_X);
   addAction(ACTION_A);
   addAction(ACTION_A);
   addAction(ACTION_X);
}

AutoController::~AutoController() {}

void AutoController::run(void)
{
   performAction();
}

void AutoController::addAction(ActionType action)
{
   Action act(m_dstation, action);
   m_queue.insert(m_queue.begin(), act);
}

void AutoController::performAction(void)
{
   if (m_queue.size() == 0)
      {
	 return;
      }
   Action current_action = m_queue.back();
   if (current_action())
      {
	 printf("Completed action.");
	 m_queue.pop_back();
      }
}
