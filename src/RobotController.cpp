/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader, Flywheel* flywheel, ConfigEditor* configEditor)
: m_driveStation(ds), m_driveTrain(dt), m_shooterController(shooter), m_loaderController(loader), m_flywheel(flywheel), m_configEditor(configEditor)
{
   m_state = ROBOT_MANUAL;
}

RobotController::~RobotController() {}

void RobotController::run(){
   if (m_state == ROBOT_AUTO){
      // Y button cancels autonomous mode, resetting it to manual controls.
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonY)){
	 // Simplest way to empty queue while destroying everything.
	 // Not replacing with empty queue because that may not destroy
	 // the objects inside.
	 while (!m_queue.empty())
	    m_queue.pop();
	 m_driveTrain->stopRobot();
         m_state = ROBOT_MANUAL;
         return;
      }
      performAction();
   }
   else if (m_state == ROBOT_MANUAL)
   {
      SmartDashboard::PutString("DB/String 5", "MANUAL");
//      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonA)){
//
//         m_state = ROBOT_AUTO;
         //m_queue.push(new ActionDrive(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         // m_queue.push(new ActionTurn(m_driveTrain, 180.0f, 0.6f));
         // m_queue.push(new ActionTurn(m_driveTrain, -180.0f, 0.6f));
         //m_queue.push(new ActionDrive(m_driveTrain, -18.0f, 0.6f));
//      }
//      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonB)){
//         SmartDashboard::PutString("DB/String 5", "Adding to queue ");
//         m_state = ROBOT_AUTO;
//         m_queue.push(new ActionDrive(m_driveTrain,  m_configEditor->getFloat("distance"),  m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionDrive(m_driveTrain,  m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
//         m_queue.push(new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//      }
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonB)){
         m_loaderController->start();
      }
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonY)){
         m_loaderController->stop();
      }
      if(m_driveStation->getGamepadButton(DriveStationConstants::triggerRT)){
         m_flywheel->start(1.0f);
      }
      else{
         m_flywheel->stop();
      }
      return;
   }
}

void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
   {
      m_state = ROBOT_MANUAL;
      return;
   }
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
