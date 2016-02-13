#pragma once

#include "Action.h"

class DriveStation;

class ActionButtonWait : public Action
{
 public:
   ActionButtonWait(DriveStation*, int);
   void init(void);
   bool execute(void);
 private:
   DriveStation* m_driveStation;
   int m_button;
};
