#pragma once

#include "Action.h"

class LoaderSense;

class ActionBallAim : public Action
{
 public:
   ActionBallAim(LoaderSense*);
   void init(void);
   bool execute(void);
 private:
   LoaderSense* m_loaderSense;
};
