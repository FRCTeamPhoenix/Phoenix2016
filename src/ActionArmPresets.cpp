/*
 * ActionArmPresets.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: connortess
 */

#include "ActionArmPresets.h"

ActionArmPresets::ActionArmPresets(
      Arm* arm,
      float goal):
      Action(),
      m_arm(arm),
      m_goal(goal){
   // TODO Auto-generated constructor stub
}

void ActionArmPresets::init(void){
   m_arm->moveArmToPosition(m_goal);
   m_initialized = true;
}

bool ActionArmPresets::execute(void){
   return true;
}

ActionArmPresets::~ActionArmPresets() {

}
