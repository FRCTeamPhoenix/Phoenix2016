#pragma once

#include "Action.h"

class DriveTrainController;
class LidarHandler;

class ActionLidarDriveStatic : public Action
{
 public:
   ActionLidarDriveStatic(DriveTrainController*, LidarHandler*, float distanceFromObject, float power);
   void init(void);
   bool execute(void);
 private:
   DriveTrainController* m_driveTrain;
   float m_distance;
   float m_power;
};
