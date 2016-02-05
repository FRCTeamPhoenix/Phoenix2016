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


//Values for the motor speeds might need to be changed
static const float armMotorLeft = 1.0f;
static const float armMotorRight = 1.0f;
static const float intakeMotorSpeed = 1.0f;
static const float stationaryMotorSpeed = 1.0f;
static const float homingSpeed = 0.1f;

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


public:
   enum STATE {
      IDLE,
      HOMING,
      HOMED,
      EMPTY,
      LOADING,
      LOADINGTOSHOOTER,
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
         DriveStation* driveStation);
   void run();
   void armLimitSwitches(float power);
   int angleOfArm();
   void moveArm();
   void homing();
   void setHomed();
   void setLoaded();
   void setShooting();
   void setIdle();
   void startLoading();
   virtual ~LoaderController();

   STATE getCurrentState();
   STATE getGoalState();

private:
   STATE m_goalState;
   enum HOMINGSTATES{
      LOOKINGFORLOWERLIMIT,
      HOMINGCOMPLETE
   }m_homingState;
};

#endif /* SRC_LOADERCONTROLLER_H_ */
