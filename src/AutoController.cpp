#include "AutoController.h"
#include "BaseController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "ShooterController.h"
#include "LoaderController.h"
#include "ConfigEditor.h"
#include "Arm.h"
#include "Aiming.h"

#include "constants.h"
#include "Actions.h"

AutoController::AutoController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader, Flywheel* flywheel, ConfigEditor* configEditor, Arm* arm, Aiming* aiming)
   : m_driveStation(ds), m_driveTrain(dt), m_shooterController(shooter), m_loaderController(loader), m_flywheel(flywheel), m_configEditor(configEditor), m_arm(arm), m_aiming(aiming)
{
   // Drive forwards 5 feet
   m_queue.push(new ActionDrive(m_driveTrain, 144, m_configEditor->getFloat("motorPower")));

   // Start spinning flywheels to get them up to speed
   //TODO: Only one parameter will be needed in the future, due to motor power calculation
   // being handled by lidar/flywheels

   //m_queue.push(new ActionSpinFlywheels(m_flywheel, m_configEditor->getFloat("flywheelMotorPower")));

   // As soon as the flywheels are spinning, begin the aiming process
   m_queue.push(new ActionTargetAim(m_aiming));

   // Shoot, after flywheels are up to speed and robot is centered
   m_queue.push(new ActionShoot(m_loaderController));
}

void AutoController::run(void)
{
   performAction();
}

/*
 * Utility function that cancels all actions in queue
 * and returns everything to the normal state.
 */
void AutoController::cancel(void)
{
   /* Simplest way to empty queue while destroying everything.
      Not replacing with empty queue because that may not destroy
      the objects inside. */
   while (!m_queue.empty())
      m_queue.pop();
   m_driveTrain->stopRobot();
   return;
}

void AutoController::performAction(void)
{
   if (m_queue.size() == 0)
      return;

   Action *currentAction = m_queue.front();
   if (!currentAction->isInitialized())
      currentAction->init();

   if (currentAction->execute())
      {
         printf("Completed action.");
         delete currentAction;
         m_queue.pop();
      }
}
