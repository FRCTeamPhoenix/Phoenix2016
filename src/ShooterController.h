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

class ShooterController : public BaseController{
public:
	enum STATE{
	   SHOOTER_OFF,
	   SHOOTER_STARTING,
	   SHOOTER_ON,
	   SHOOTER_STOPPING,
	   SHOOTER_SHOOTING
	};
   ShooterController(Talon * flywheels);
   void run();
   virtual ~ShooterController();
private:
   bool flywheelsOn;
   Talon * m_flywheels;

   void toggleFlywheels();
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */
