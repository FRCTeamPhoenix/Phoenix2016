/*
 * LoaderSense.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Brin Harper
 */

#ifndef SRC_LOADERSENSE_H_
#define SRC_LOADERSENSE_H_
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
#include <cmath>
#include "Client.h"
#include "DriveTrainController.h"
#include "constants.h"

class LoaderSense {

public:

   enum STATE {
      IDLE,
      FINDING_BALL,
      ROTATING,
      APPROACHING,
      BACKUP
   };

   LoaderSense(Client*, DriveTrainController*, DriveStation*);
   void beginAiming();
   void updateBallPositionData();
   int getCurrentRadius();
   int getCurrentXCenter();
   int getCurrentYCenter();
   void setCurrentState(STATE);
   STATE getCurrentState();
   void findBall();
   void rotate();
   void approach();
   void backup();
   void run();
   ~LoaderSense();

private:

   Client* m_client;
   DriveTrainController* m_driveTrainController;
   DriveStation* m_driveStation;

   int m_currentBallPosition[4];
   STATE m_currentState;
   bool lastArrayWasNull;
   int nullArraysInARow;

};


#endif /* SRC_LOADERSENSE_H_ */
