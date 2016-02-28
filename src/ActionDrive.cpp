#include "ActionDrive.h"
#include "DriveTrainController.h"

ActionDrive::ActionDrive(DriveTrainController* dt, float distance, float power)
   : Action(), m_driveTrain(dt), m_distance(distance), m_power(power)
{
}

void
ActionDrive::init(void)
{
   m_driveTrain->moveRobotStraight(m_distance, m_power);
   m_initialized = true;
}

bool
ActionDrive::execute(void)
{
   return m_driveTrain->getCurrentState() == DriveTrainController::IDLE;
}
