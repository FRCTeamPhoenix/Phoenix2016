/*
 * AutoController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include <AutoController.h>
#include <vector>

AutoController::AutoController(RobotController* parent)
   : m_parent(parent)
{}

AutoController::~AutoController() {}

void AutoController::addAction(ActionType action)
{
   m_queue.insert(m_queue.begin(), action);
}

void AutoController::performAction(void)
{
   if (m_queue.size() == 0)
      {
    // TODO: Change parent (RobotController) state to MANUAL.
    return;
      }
   Action current_action = m_queue.back();
   m_queue.pop_back();
   current_action();
}
