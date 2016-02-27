/*
 * ActionSpinFlywheels.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Brin Harper
 */

#ifndef SRC_ACTIONSPINFLYWHEELS_H_
#define SRC_ACTIONSPINFLYWHEELS_H_

#pragma once

#include "Action.h"

class ActionSpinFlywheels : public Action
{
 public:
   ActionSpinFlywheels(Flywheel*, float);
   void init(void);
   bool execute(void);
   ~ActionSpinFlywheels();

 private:
   Flywheel* m_flywheel;
   float m_motorPower;
};



#endif /* SRC_ACTIONSPINFLYWHEELS_H_ */
