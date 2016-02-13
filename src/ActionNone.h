#pragma once

#include "Action.h"

class ActionNone : public Action
{
 public:
   ActionNone(void);
   void init(void);
   bool execute(void);
};
