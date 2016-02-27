// This class allows for integration of the target aiming process into the Action
// system. Aiming at the target is defined here as its own action.

#pragma once

#include "Action.h"

class Aiming;

class ActionTargetAim : public Action
{
 public:
   ActionTargetAim(Aiming*);
   void init(void);
   bool execute(void);
 private:
   Aiming* m_aimer;
};
