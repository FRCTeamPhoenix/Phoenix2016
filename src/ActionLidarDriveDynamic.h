#pragma once

#include "Action.h"

class DriveTrainController;
class LidarHandler;

class ActionLidarDriveDynamic : public Action
{
 public:
   ActionLidarDriveDynamic(DriveTrainController*, LidarHandler*, float distanceFromObject, float power);
   void init(void);
   bool execute(void);
 private:
   DriveTrainController* m_driveTrain;
   LidarHandler* m_lidar;
   float m_distance;
   float m_power;

   enum State { INITIAL_DRIVE, DEADZONE_CHECK, ADJUST, DONE };
   State m_state;

   static const float m_deadzone;
};
