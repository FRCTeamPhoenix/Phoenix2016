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
#include"ConfigEditor.h"



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

   ShooterController(LoaderController * loader, Flywheel * flywheel, ConfigEditor * configEditor);
   virtual ~ShooterController();
   void run();

   //Gets the current state of which the shooter is in and the loader
   STATE getCurrentState();
   //Gets the goal state of the shooter
   STATE getGoalState();

   //Sets the goal state to ARMED
   void setArmed();
   //Sets the goal state to OFF
   void setOff();
   //Sets the goal state to OFF
   void stopShooting();
   //Sets the goal state to SHOOTING
   void setShooting();

private:
   LoaderController * m_loaderController;
   Flywheel * m_flywheel;
   ConfigEditor * m_configEditor;
   STATE m_goalState;
   void firing(); //Not Implemented
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */
