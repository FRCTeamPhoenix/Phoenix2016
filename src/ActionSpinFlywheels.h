/*
 * ActionSpinFlywheels.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 *
 *      This class allows for integration of the initial process of getting
 *      the flywheels up to speed into the Action system.  The defined Action
 *      is speeding up the flywheels based on the distance-linked motor power.
 */

#ifndef SRC_ACTIONSPINFLYWHEELS_H_
#define SRC_ACTIONSPINFLYWHEELS_H_

#pragma once

#include "Action.h"
#include "Flywheel.h"

class ActionSpinFlywheels : public Action
{
private:
   Flywheel* m_flywheel;
   float m_motorPower;
public:
   ActionSpinFlywheels(Flywheel*, float);
   void init(void);
   bool execute(void);
   ~ActionSpinFlywheels();
};



#endif /* SRC_ACTIONSPINFLYWHEELS_H_ */
