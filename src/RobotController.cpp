/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds,
      DriveTrainController* dt,
      ShooterController* shooter,
      LoaderController* loader,
      Flywheel* flywheel,
      ConfigEditor* configEditor,
      Arm* arm,
      Aiming* aiming):
      m_driveStation(ds),
      m_driveTrain(dt),
      m_shooterController(shooter),
      m_loaderController(loader),
      m_flywheel(flywheel),
      m_configEditor(configEditor),
      m_arm(arm),
      m_aiming(aiming)
{
   m_state = ROBOT_MANUAL;
}

RobotController::~RobotController() {}

void RobotController::run(){
   if (m_state == ROBOT_AUTO){
      // Y button cancels autonomous mode, resetting it to manual controls.
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonY)){
         clearQueue();
         return;
      }
      performAction();
   }
   else if (m_state == ROBOT_MANUAL)
   {

      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonA)){
         m_queue.push(new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
         m_state = ROBOT_AUTO;
      }

      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonRB)){
         m_loaderController->start();
      }
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonLB)){
         m_loaderController->stop();
      }

      if(m_driveStation->getGamepadButton(DriveStationConstants::triggerRT)){
         m_flywheel->start();
      }
      if(m_driveStation->getGamepadButton(DriveStationConstants::triggerLT)){
         m_flywheel->stop();
      }


      m_arm->move(m_driveStation->deadzoneOfGamepadJoystick() / 2);

      return;
   }
}

void RobotController::performAction(void){
   std::ostringstream qSize;
   qSize << "qSize: " << m_queue.size();
   if (m_queue.empty()) {
      m_state = ROBOT_MANUAL;
      return;
   }
   Action *currentAction = m_queue.front();

   if (!currentAction->isInitialized())
      currentAction->init();

   if (currentAction->execute()) {
      printf("Completed action.");
      delete currentAction;
      m_queue.pop();
   }
}

// Push sequence of autonomous actions to the queue
void RobotController::initAutonomousModeQueue(){
   if(SmartDashboard::GetBoolean("Rock Wall", false))
      m_queue.push(new ActionDrive(m_driveTrain, 60, m_configEditor->getFloat("motorPower")));
   else if(SmartDashboard::GetBoolean("Cheval de Frise", false)) {
      //TODO set arm up
      m_queue.push(new ActionDrive(m_driveTrain, 20, m_configEditor->getFloat("motorPower")));//TODO distances
      //TODO set arm down
      m_queue.push(new ActionDrive(m_driveTrain, 40, m_configEditor->getFloat("motorPower")));//TODO distances
   }
   else if(SmartDashboard::GetBoolean("Portcullis", false)) {
      //TODO set arm down
      m_queue.push(new ActionDrive(m_driveTrain, 20, m_configEditor->getFloat("motorPower")));//TODO distances
      //TODO set arm up
      m_queue.push(new ActionDrive(m_driveTrain, 40, m_configEditor->getFloat("motorPower")));//TODO distances
   }
   else if(SmartDashboard::GetBoolean("Rough Terrain", false))
      m_queue.push(new ActionDrive(m_driveTrain, 60, m_configEditor->getFloat("motorPower")));
   else if(SmartDashboard::GetBoolean("Moat", false))
      m_queue.push(new ActionDrive(m_driveTrain, 60, m_configEditor->getFloat("motorPower")));
   else if(SmartDashboard::GetBoolean("Ramparts", false))
      m_queue.push(new ActionDrive(m_driveTrain, 60, m_configEditor->getFloat("motorPower")));
   else if(SmartDashboard::GetBoolean("Sally Port", false)) {
      //TODO set arm up
      m_queue.push(new ActionDrive(m_driveTrain, 20, m_configEditor->getFloat("motorPower")));//TODO distances
      //TODO set arm down
      m_queue.push(new ActionDrive(m_driveTrain, -8, m_configEditor->getFloat("motorPower")));//TODO distances
      //TODO finish the stuff
   }
   else if(SmartDashboard::GetBoolean("Drawbridge", false))
      m_queue.push(new ActionDrive(m_driveTrain, 60, m_configEditor->getFloat("motorPower")));
   //m_queue.push(new ActionDrive(m_driveTrain, 60, m_configEditor->getFloat("motorPower")));
   m_state = ROBOT_AUTO;

}
void RobotController::setManual(){
   m_state = ROBOT_MANUAL;
}

// Simplest way to empty queue while destroying everything.
// Not replacing with empty queue because that may not destroy
// the objects inside.
void RobotController::clearQueue() {
   while (!m_queue.empty())
      m_queue.pop();
   m_driveTrain->stopRobot();
   m_state = ROBOT_MANUAL;
   return;
}
