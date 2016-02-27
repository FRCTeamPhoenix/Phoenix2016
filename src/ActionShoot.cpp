/*
 * ActionShoot.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 *
 *      This class allows for integration of the shooting process into the Action
 *      system. Shooting (releasing the ball) is defined here as its own action.
 */

#include "ActionShoot.h"

// Constructor
ActionShoot::ActionShoot(ShooterController* shooterController)
   : Action(), m_shooterController(shooterController)
{

}

// Start the shooter running
void ActionShoot::init(void)
{
   m_shooterController->run();
   m_initialized = true;
}

// End the action if the shooter is off (this means shooting is done)
bool ActionShoot::execute(void)
{
   return m_shooterController->getCurrentState() == ShooterController::OFF;
}

// Destructor
ActionShoot::~ActionShoot() {

}




