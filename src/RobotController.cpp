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
   else if (m_state == ROBOT_MANUAL) {

      //Gamepad button Right Bumper
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonRB)){
         m_loaderController->start();
      }
      //Gamepad button Left Bumper
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonLB)){
         m_loaderController->stop();
      }
      //Gamepad button Right Trigger
      if(m_driveStation->getGamepadButton(DriveStationConstants::triggerRT)){
         m_flywheel->start();
      }
      //Gamepad button Left Trigger
      if(m_driveStation->getGamepadButton(DriveStationConstants::triggerLT)){
         m_flywheel->stop();
      }
      //ArmButtons Bottom Button
      if(m_driveStation->getArmJoystickButton(DriveStationConstants::buttonBottom)){
         m_arm->moveArmToPosition(0);
      }
      //ArmButtons CDF
      if(m_driveStation->getArmJoystickButton(DriveStationConstants::buttonCDF)){
         m_arm->moveArmToPosition(0.25);
      }
      //ArmButtons Middle
      if(m_driveStation->getArmJoystickButton(DriveStationConstants::buttonMiddle)){
         m_arm->moveArmToPosition(0.5);
      }
      //ArmButtons DrawBridge
      if(m_driveStation->getArmJoystickButton(DriveStationConstants::buttonDrawBridge)){
         m_arm->moveArmToPosition(0.75);      }
      //ArmButtons Top
      if(m_driveStation->getArmJoystickButton(DriveStationConstants::buttonTop)){
         m_arm->moveArmToPosition(1);
      }

      m_arm->run();
      m_state = ROBOT_MANUAL;
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonA)){
         m_state = ROBOT_AUTO;
         m_queue.push( new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower", 0.6)));
         //m_queue.push( new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower", 0.6)));
         //m_queue.push( new ActionTurn(m_driveTrain, -m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower", 0.6)));
         //m_queue.push( new ActionDrive(m_driveTrain, -m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower", 0.6)));
      }
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonB)){
         m_state = ROBOT_AUTO;
         m_queue.push( new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionDrive(m_driveTrain, m_configEditor->getFloat("distance"), m_configEditor->getFloat("motorPower", 0.6)));
         m_queue.push( new ActionTurn(m_driveTrain, m_configEditor->getFloat("degree"), m_configEditor->getFloat("motorPower", 0.6)));
      }
      if (m_driveStation->getGamepadButton(DriveStationConstants::buttonX)){
         m_queue.push( new ActionDrive(m_driveTrain, 80, 0.8)); //Goes to defense
         m_queue.push( new ActionDrive(m_driveTrain, 44, 0.6)); //Goes over defense
         m_queue.push( new ActionDrive(m_driveTrain, 51.5, 0.8)); //Goes to alignment line
      }
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
      m_queue.push(new ActionDrive(m_driveTrain, 20, m_configEditor->getFloat("motorPower")));
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

RobotController::STATE RobotController::getState() {
   return m_state;
}
