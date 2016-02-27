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
   m_flywheel->start(m_motorPower);
   m_initialized = true;
}

// Determines whether further execution is necessary (are the motors done spinning?)
bool ActionSpinFlywheels::execute(void)
{
   return m_flywheel->getCurrentState() == Flywheel::OFF;
}

ActionSpinFlywheels::~ActionSpinFlywheels() {

}



