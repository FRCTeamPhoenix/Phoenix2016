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
   ActionArmPresets(Arm*, float);
   void init(void);
   bool execute(void);
   ~ActionArmPresets();
private:
   Arm* m_arm;
   float m_goal;
};

#endif /* ACTIONARMPRESETS_H_ */
