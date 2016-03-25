/*
 * ActionArmPresets.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: connortess
 */

#include "ActionArmPresets.h"

ActionArmPresets::ActionArmPresets(
      Arm* arm,
      float goal,
      float tolerance):
      Action(),
      m_arm(arm),
      m_goal(goal),
      m_tolerance(tolerance){
   // TODO Auto-generated constructor stub
}

void ActionArmPresets::init(void){
   m_arm->moveArmToPosition(m_goal);
   m_initialized = true;
}

bool ActionArmPresets::execute(void){
   return m_arm->getCurrentState(m_tolerance) == m_arm->STATE::IDLE;
}

ActionArmPresets::~ActionArmPresets() {

}
