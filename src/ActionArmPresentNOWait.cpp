/*
 * ActionArmPresets.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: connortess
 */

#include "ActionArmPresentNOWait.h"

ActionArmPresentNOWait::ActionArmPresentNOWait(
      Arm* arm,
      float goal):
      Action(),
      m_arm(arm),
      m_goal(goal){
   // TODO Auto-generated constructor stub
}

void ActionArmPresentNOWait::init(void){
   m_arm->moveArmToPosition(m_goal);
   m_initialized = true;
}

bool ActionArmPresentNOWait::execute(void){
   return true;
}

ActionArmPresentNOWait::~ActionArmPresentNOWait() {

}
