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
#include "Flywheel.h"



class ShooterController : public BaseController{
public:
   enum STATE{
      OFF,
      ARMING,
      ARMED,
      STOPPING,
      PREPARINGTOSHOOT,
      SHOOTING
   };

   ShooterController(LoaderController * loader, Flywheel * flywheel);
   virtual ~ShooterController();
   void run();

   STATE getCurrentState();
   STATE getGoalState();

   void setArmed();
   void setOff();
   void setShooting();

private:
   LoaderController * m_loaderController;
   Flywheel * m_flywheel;
   STATE m_goalState;
   void firing(); //Not Implemented
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */
