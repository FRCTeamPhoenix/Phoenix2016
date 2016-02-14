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
static const float armMotorLeft = 1.0f;
static const float armMotorRight = 1.0f;
static const float intakeMotorSpeed = 1.0f;
static const float stationaryMotorSpeed = 1.0f;
static const float homingSpeed = -0.1f;

class LoaderController : public BaseController{
private:
   Talon* m_armMotorLeft;
   Talon* m_armMotorRight;
   Talon* m_intakeMotor;
   Talon* m_stationaryMotor;
   DigitalInput* m_upperLimit;
   DigitalInput* m_lowerLimit;
   DigitalInput* m_loadedSensor;
   Encoder* m_armEncoder;
   DriveStation* m_driveStation;
   AnalogPotentiometer* m_potentiometer;
   ConfigEditor* m_configEditor;


public:
   enum STATE {
      IDLE,
      HOMING,
      LOADING,
      LOADED,
      SHOOTING
   };


   LoaderController(
         Talon* armMotorLeft,
         Talon* armMotorRight,
         Talon* intakeMotor,
         Talon* stationaryMotor,
         DigitalInput* uppterLimit,
         DigitalInput* lowerLimit,
         DigitalInput* loadedSensor,
         Encoder* armEncoder,
         DriveStation* driveStation,
         AnalogPotentiometer* potentiometer,
         ConfigEditor* configEditor);
   void run();
   void armLimitSwitches(float power);
   //Returns what degree the arm is at
   int angleOfArm();
   //Moves the arm and has the deadzone included
   void moveArm();
   //Sets the goal state to HOMING
   void setHoming();
   //Sets the goal state to LOADED
   void setLoaded();
   //Sets the goal state to SHOOTING
   void setShooting();
   //Sets the goal state goal to IDLE
   void setIdle();
   //Starts the loading process
   void startLoading();
   bool homed();
   bool loaded();
   virtual ~LoaderController();

   //Gets the current state of the robot
   STATE getCurrentState();
   //Returns the goal state of the loader
   STATE getGoalState();

private:
   STATE m_goalState;
   bool m_homed;
};

#endif /* SRC_LOADERCONTROLLER_H_ */
