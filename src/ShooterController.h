/*
 * ShooterController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_SHOOTERCONTROLLER_H_
#define SRC_SHOOTERCONTROLLER_H_

#include "WPILib.h"
#include "BaseController.h"
#include "constants.h"
#include "LoaderController.h"
//will be have to be changed and put in constants later
static const float leftFlywheelMotorSpeed = 1.0;
static const float rightFlywheelMotorSpeed = 1.0;

class ShooterController : public BaseController{

   Talon * m_leftFlywheelMotor;
   Talon * m_rightFlywheelMotor;
   LoaderController * m_loaderController;

public:
	enum STATE{
	   OFF,
	   ARMING,
	   ARMED,
	   STOPPING,
	   PREPARINGTOSHOOT,
	   SHOOTING
	};

   ShooterController(Talon * leftFlywheelMotor, Talon * rightFlywheelMotor, LoaderController * loader);
   void run();

   STATE getCurrentState();
   STATE getGoalState();

   virtual ~ShooterController();
private:

   STATE m_goalState;
   void firing(); //Not Implemented
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */
