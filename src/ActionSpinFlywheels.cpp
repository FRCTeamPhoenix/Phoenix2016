/*
 * ActionSpinFlywheels.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 *
 *      This class allows for integration of the initial process of getting
 *      the flywheels up to speed into the Action system.  The defined Action
 *      is speeding up the flywheels based on the distance-linked motor power.
 *
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
   m_flywheel->start();
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



