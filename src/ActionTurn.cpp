#include "ActionTurn.h"
#include "DriveTrainController.h"

ActionTurn::ActionTurn(DriveTrainController* dt, float angle, float power)
   : Action(), m_driveTrain(dt), m_angle(angle), m_power(power)
{
}

void
ActionTurn::init(void)
{
   m_driveTrain->aimRobotClockwise(m_angle, m_power);
   m_initialized = true;
}

bool
ActionTurn::execute(void)
{
   return m_driveTrain->getCurrentState() == DriveTrainController::IDLE;
}
