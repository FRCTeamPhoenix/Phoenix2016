/*
 * RobotController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#include "RobotController.h"
#include "AutoController.h"

RobotController::RobotController(DriveStation* driveStation, AutoController* autoC) :
   m_driveStation(driveStation), m_auto(autoC)
{}

void RobotController::run()
{
   // TODO: Put functionality for both manual and auto, not just autonomous
   m_auto->run();
}

DriveStation* RobotController::getDriveStation()
{
   return m_driveStation;
}

RobotController::~RobotController() {

}
