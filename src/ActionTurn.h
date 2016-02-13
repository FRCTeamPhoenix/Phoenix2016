#pragma once

#include "Action.h"

class DriveTrainController;

class ActionTurn : public Action
{
 public:
   ActionTurn(DriveTrainController*, float, float);
   void init(void);
   bool execute(void);
 private:
   DriveTrainController* m_driveTrain;
   float m_angle;
   float m_power;
};
