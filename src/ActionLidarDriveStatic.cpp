#include "ActionLidarDriveStatic.h"
#include "DriveTrainController.h"
#include "LidarHandler.h"

ActionLidarDriveStatic::ActionLidarDriveStatic(DriveTrainController* dt, LidarHandler* lidar, float distanceFromObject, float power)
   : Action(), m_driveTrain(dt), m_power(power)
{
   m_distance = lidar->getFastAverage() - distanceFromObject;
}

void
ActionLidarDriveStatic::init(void)
{
   m_driveTrain->moveRobotStraight(m_distance, m_power);
   m_initialized = true;
}

bool
ActionLidarDriveStatic::execute(void)
{
   return m_driveTrain->getCurrentState() == DriveTrainController::IDLE;
}
