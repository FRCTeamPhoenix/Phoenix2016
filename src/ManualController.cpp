/*
 * ManualController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <ManualController.h>

ManualController::ManualController(DriveTrainController * driveTrain, ShooterController * shooter, LoaderController * loader) {
	m_driveTrain = driveTrain;
	m_shooter = shooter;
	m_loader = loader;
}

ManualController::~ManualController() {
	// TODO Auto-generated destructor stub
}

void ManualController::run() {
   m_driveTrain->run();
   m_shooter->run();
   m_loader->run();
}
