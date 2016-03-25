/*
 * ActionArmPresets.h
 *
 *  Created on: Mar 21, 2016
 *      Author: connortess
 */

#ifndef ACTIONARMPRESETS_H_
#define ACTIONARMPRESETS_H_

#include "Action.h"
#include "Arm.h"

class ActionArmPresets : public Action{
public:
   ActionArmPresets(Arm*, float, float tolerance = 0.1);
   void init(void);
   bool execute(void);
   ~ActionArmPresets();
private:
   Arm* m_arm;
   float m_goal;
   float m_tolerance;
};

#endif /* ACTIONARMPRESETS_H_ */
