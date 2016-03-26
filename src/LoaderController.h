/*
 * LoaderController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_LOADERCONTROLLER_H_
#define SRC_LOADERCONTROLLER_H_

#include "BaseController.h"
#include "WPILib.h"
#include "constants.h"
#include "DriveStation.h"
#include "ConfigEditor.h"

//Values for the motor speeds might need to be changed
static const float intakeMotorSpeed = 1.0f;
static const float stationaryMotorSpeed = 1.0f;

class LoaderController : public BaseController{
private:
   Talon* m_intakeMotor;
   Talon* m_stationaryMotor;
   DigitalInput* m_loadedSensor;
   DriveStation* m_driveStation;
   ConfigEditor* m_configEditor;

public:
   LoaderController(
         Talon* intakeMotor,
         Talon* stationaryMotor,
         DigitalInput* loadedSensor,
         DriveStation* driveStation,
         ConfigEditor* configEditor);
   void run();
   //Starts the loading process
   void start();
   void lowGoal();
   void stop();
   bool loaded();
   virtual ~LoaderController();


private:
   bool m_ballInRobot;
};

#endif /* SRC_LOADERCONTROLLER_H_ */
