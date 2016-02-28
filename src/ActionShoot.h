/*
 * ActionShoot.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 *
 *      This class allows for integration of the shooting process into the Action
 *      system. Shooting (releasing the ball) is defined here as its own action.
 */

#ifndef SRC_ACTIONSHOOT_H_
#define SRC_ACTIONSHOOT_H_

#pragma once

#include "Action.h"
#include "ActionShoot.h"
#include "LoaderController.h"

class ActionShoot : public Action
{
private:
   LoaderController* m_loaderController;
public:
   ActionShoot(LoaderController*);
   void init(void);
   bool execute(void);
   ~ActionShoot();
};



#endif /* SRC_ACTIONSPINFLYWHEELS_H_ */
