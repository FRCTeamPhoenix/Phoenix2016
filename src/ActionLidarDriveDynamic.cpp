#include "ActionLidarDriveDynamic.h"
#include "DriveTrainController.h"
#include "LidarHandler.h"

const float
ActionLidarDriveDynamic::m_deadzone = 6.0f; // In inches, compatible with DriveTrainController.

ActionLidarDriveDynamic::ActionLidarDriveDynamic(DriveTrainController* dt, LidarHandler* lidar, float distanceFromObject, float power)
   : Action(), m_driveTrain(dt), m_lidar(lidar), m_distance(distanceFromObject), m_power(power)
{
   m_state = INITIAL_DRIVE;
}

void
ActionLidarDriveDynamic::init(void)
{
   m_initialized = true;
}

bool
ActionLidarDriveDynamic::execute(void)
{
   float driveDistance;
   switch (m_state)
      {
      case INITIAL_DRIVE:
	 driveDistance = m_lidar->getFastAverage() - m_distance - m_deadzone;
	 if (driveDistance <= 0)
	    m_state = DEADZONE_CHECK;
	 else
	    m_driveTrain->moveRobotStraight(driveDistance, m_power);
	 break;
      case DEADZONE_CHECK:
	 if (m_lidar->getFastAverage() > m_distance - m_deadzone &&
	     m_lidar->getFastAverage() < m_distance + m_deadzone)
	    m_state = DONE;
	 else
	    m_state = ADJUST;
	 break;
      case ADJUST:
	 driveDistance = (m_lidar->getFastAverage() - m_distance) / 2;
	 if (driveDistance <= 0)
	    m_state = DEADZONE_CHECK;
	 else
	    m_driveTrain->moveRobotStraight(driveDistance, m_power / 2);
	 break;
      case DONE:
	 return true;
      }
   return false;
}
