/*
 * LoaderSense.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Brin Harper
 */

#ifndef SRC_LOADERSENSE_H_
#define SRC_LOADERSENSE_H_
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
#include "Math.h"
#include "Client.h"
#include "LoaderController.h"
#include "Constants.h"

class LoaderSense {

public:

   enum STATE {
      IDLE,
      INITIAL_ALIGN,
      APPROACHING,
      FINAL_ALIGN,
      TARGETED
   };

   LoaderSense(Client*, LoaderController*);
   void updateBallPositionData();
   int getCurrentRadius();
   int getCurrentXCenter();
   int getCurrentYCenter();
   void setCurrentState(STATE);
   STATE getCurrentState();
   void run();
   ~LoaderSense();

private:

   Client* m_client;
   LoaderController* m_loaderController;

   int m_currentBallPosition[3];
   STATE m_currentState;

};


#endif /* SRC_LOADERSENSE_H_ */
