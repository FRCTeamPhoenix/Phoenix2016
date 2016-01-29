/*
 * Flywheel.h
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#ifndef SRC_FLYWHEEL_H_
#define SRC_FLYWHEEL_H_
#include "WPILib.h"
#include "BaseController.h"

class Flywheel : BaseController {
private:
   Talon * m_leftFlywheelMotor;
   Talon * m_rightFlywheelMotor;
   Timer m_timer;
   float m_power;
   bool m_running;
public:
   Flywheel(Talon * m_leftFlywheelMotor,Talon * m_rightFlywheelMotor);
   virtual ~Flywheel();

   enum STATE{
      OFF,
      ON,
      STARTING
   };

   void run();
   STATE getCurrentState();
   void startMotors(float power);
   void stopMotors();

};
#endif /* SRC_FLYWHEEL_H_ */
