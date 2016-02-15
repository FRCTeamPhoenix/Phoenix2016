
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
         m_queue.clear();
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
         //m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         // m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, 180.0f, 0.6f));
         // m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, -180.0f, 0.6f));
         //m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, -18.0f, 0.6f));
//      }
//      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonB)){
//         SmartDashboard::PutString("DB/String 5", "Adding to queue ");
//         m_state = ROBOT_AUTO;
//         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain,  m_configEditor->getFloat("distance"),  m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain,  m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
//         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
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



      m_queue.clear();
      m_state = ROBOT_MANUAL;
      return;
   }
   performAction();
}


void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
   {
      m_state = ROBOT_MANUAL;
      return;
   }
   Action *currentAction = m_queue.back();
   if (!currentAction->isInitialized())
      currentAction->init();
   if (currentAction->execute())
   {
      printf("Completed action.");
      delete currentAction;
      m_queue.pop_back();
   }
}
