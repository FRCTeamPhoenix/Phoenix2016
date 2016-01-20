/*
 * Flywheel.h
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#ifndef SRC_FLYWHEEL_H_
#define SRC_FLYWHEEL_H_
#include "WPILib.h"

class Flywheel : BaseController {
   Talon * m_leftFlywheelMotor;
   Talon * m_rightFlywheelMotor;
private:
   Timer m_timer;
public:

   enum STATE{
      OFF,
      ON,
      STARTING
   };
   Flywheel(Talon * m_leftFlywheelMotor,Talon * m_rightFlywheelMotor);
   void run();

   STATE getCurrentState();
   STATE getGoalState();

   bool getFlywheelMotorRunning(Talon *);
   virtual ~Flywheel();
};

#endif /* SRC_FLYWHEEL_H_ */
