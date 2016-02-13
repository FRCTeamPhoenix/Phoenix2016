#pragma once

#include "Action.h"

class DriveTrainController;

class ActionDrive : public Action
{
 public:
   ActionDrive(DriveTrainController*, float, float);
   void init(void);
   bool execute(void);
 private:
   DriveTrainController* m_driveTrain;
   float m_distance;
   float m_power;
};
