/*
 * ActionSpinFlywheels.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 */


#include "ActionSpinFlywheels.h"

ActionSpinFlywheels::ActionSpinFlywheels(Flywheel* flywheel, float motorPower)
   : Action(), m_flywheel(flywheel), m_motorPower(motorPower)
{

}

// Sets up the flywheels for action
void ActionSpinFlywheels::init(void)
{
   // won't need a parameter later (the start function will be changed so that the proper
   // speed will be selected, based on distance from the target
   m_flywheel->start(m_motorPower);
   m_initialized = true;
}

// Return true immediately, to start the next action in the queue (aiming)
bool ActionSpinFlywheels::execute(void)
{
   return true;
         //m_flywheel->getCurrentState() == Flywheel::OFF;
}

ActionSpinFlywheels::~ActionSpinFlywheels() {

}



