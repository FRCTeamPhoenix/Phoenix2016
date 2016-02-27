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
ActionShoot::ActionShoot(LoaderController* loaderController)
   : Action(), m_loaderController(loaderController)
{

}

// Start the shooter running
void ActionShoot::init(void)
{
   m_loaderController->start();
   m_initialized = true;
}

// End the action if the shooter is off (this means shooting is done)
bool ActionShoot::execute(void)
{
   return m_loaderController->loaded() == false;
}

// Destructor
ActionShoot::~ActionShoot() {

}




