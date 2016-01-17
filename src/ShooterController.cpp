/*
 * ShooterController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <ShooterController.h>

ShooterController::ShooterController(Talon * flywheels) {
   m_flywheels = flywheels;
}

ShooterController::~ShooterController() {
}

void ShooterController::run(){

}

void ShooterController::toggleFlywheels() {
   m_flywheels->Set(1);
}
