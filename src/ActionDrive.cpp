// This class allows for integration of driving a specific distance
// into the Action system.

#include "ActionDrive.h"
#include "DriveTrainController.h"

ActionDrive::ActionDrive(DriveTrainController* dt, float distance, float power)
   : Action(), m_driveTrain(dt), m_distance(distance), m_power(power)
{
}

// Start the drive process
void ActionDrive::init(void)
{
   m_driveTrain->moveRobotStraight(m_distance, m_power);
   m_initialized = true;
   SmartDashboard::PutString("DB/String 2", "Drive init");
}

// Stop executing and remove from queue when the drive sequence is done
bool ActionDrive::execute(void)
{
   return m_driveTrain->getCurrentState() == DriveTrainController::IDLE;
}
