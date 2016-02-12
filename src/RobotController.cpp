/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"

RobotController::RobotController(DriveStation* ds, DriveTrainController* dt, ShooterController* shooter, LoaderController* loader)
   : m_driveStation(ds), m_driveTrainController(dt), m_shooterController(shooter), m_loaderController(loader)
{
   m_state = ROBOT_MANUAL;
}

RobotController::~RobotController() {}

void RobotController::run()
{
   if (m_state == ROBOT_AUTO){
      SmartDashboard::PutString("DB/String 3", "Preform Action");
      performAction();
   }
   else if (m_state == ROBOT_MANUAL)
      {
	 if (m_driveStation->getGamepadButton(DriveStationConstants::buttonB))
	    {
	       m_state = ROBOT_AUTO;
	       SmartDashboard::PutString("DB/String 3", "Drive Straight");
	       float args[2] = {12.0, 0.5};
	       addAction(ACTION_DRIVE, 2, args);
	    }
	 if (m_driveStation->getGamepadButton(DriveStationConstants::buttonA)){
	    m_state = ROBOT_AUTO;
	    SmartDashboard::PutString("DB/String 3", "Clockwise");
	    float args[2] = {90.0, 0.5};
	    addAction(ACTION_CLOCKWISE, 2, args);
	 }
	 if (m_driveStation->getGamepadButton(DriveStationConstants::buttonX)){
	    m_state = ROBOT_AUTO;
	    SmartDashboard::PutString("DB/String 3", "Counter Clockwise");
	    float args[2] = {90.0, 0.5};
	    addAction(ACTION_COUNTERCLOCKWISE, 2, args);
	 }
      }
   m_driveTrainController->run();
}

void RobotController::addAction(ActionType action, int argc, float* argv)
{
   Action* act = new Action(m_driveStation, m_driveTrainController, action, argc, argv);
   SmartDashboard::PutString("DB/String 4", "Adding Action");
   m_queue.insert(m_queue.begin(), act);
}

void RobotController::performAction(void)
{
   if (m_queue.size() == 0)
      {
      SmartDashboard::PutString("DB/String 3", "Manual :)");
	 m_state = ROBOT_MANUAL;
	 return;
      }
   SmartDashboard::PutString("DB/String 3", "Preform Action");
   Action *currentAction = m_queue.back();
   if (currentAction->execute())
      {
	 printf("Completed action.");
	 SmartDashboard::PutString("DB/String 4", "DONE");
	 delete currentAction;
	 m_queue.pop_back();
      }
}
