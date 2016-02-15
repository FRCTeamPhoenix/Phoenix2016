
/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader, ConfigEditor* configEditor)
: m_driveStation(ds), m_driveTrain(dt), m_shooterController(shooter), m_loaderController(loader), m_configEditor(configEditor)
{
   m_state = ROBOT_MANUAL;
}

RobotController::~RobotController() {}

void RobotController::run(){
   if (m_state == ROBOT_AUTO){
      // Y button cancels autonomous mode, resetting it to manual controls.
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonY)){
         m_queue.clear();
         m_state = ROBOT_MANUAL;
         return;
      }
      performAction();
   }
   else if (m_state == ROBOT_MANUAL)
   {
      m_queue.clear();
      m_state = ROBOT_MANUAL;

      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonA)){
         SmartDashboard::PutString("DB/String 5", "Adding to queue ");
         m_state = ROBOT_AUTO;
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
         //m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         //m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, -m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         //m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, -m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
      }
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonB)){
         SmartDashboard::PutString("DB/String 5", "Adding to queue ");
         m_state = ROBOT_AUTO;
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower")));
         m_queue.insert(m_queue.begin(), new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower")));
      }
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonX)){
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, 80, 0.8)); //Goes to defense
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, 44, 0.6)); //Goes over defense
         m_queue.insert(m_queue.begin(), new ActionDrive(m_driveTrain, 51.5, 0.8)); //Goes to alignment line
      }
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
