/*
 * ActionShoot.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 */

#include "ActionShoot.h"

ActionShoot::ActionShoot(ShooterController* shooterController)
   : Action(), m_shooterController(shooterController)
{

}

void ActionShoot::init(void)
{
   m_initialized = true;
}

bool ActionShoot::execute(void)
{
   return true;
}

ActionShoot::~ActionShoot() {

}




