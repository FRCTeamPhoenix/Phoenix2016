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
