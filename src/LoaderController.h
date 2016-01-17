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

//Values for the motor speeds might need to be changed
static const float verticalMotorSpeed = 1.0;
static const float intakeMotorSpeed = 1.0;
static const float stationaryMotorSpeed = 1.0;
static const float homingSpeed = 0.1;

class LoaderController : public BaseController{

   Talon* m_verticalMotor;
   Talon* m_intakeMotor;
   Talon* m_stationaryMotor;
   DigitalInput* m_upperLimit;
   DigitalInput* m_lowerLimit;
   DigitalInput* m_loadedSensor;
   Encoder* m_armEncoder;


public:
	enum STATE {
	        HOMING,
		EMPTY,
		LOADING,
		LOADED
	};


   LoaderController(Talon* verticalMotor,
         Talon* intakeMotor,
         Talon* stationaryMotor,
         DigitalInput* uppterLimit,
         DigitalInput* lowerLimit,
         DigitalInput* loadedSensor,
         Encoder* armEncoder);
	void run();
	void moveArm();
	void angleOfArm();
	void homing();
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
