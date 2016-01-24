/*
 * Aiming.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Brin Harper
 *
 * The Aiming class will take in the vision data received from the Raspberry Pi by way
 * of the UDP client, and work to implement in order to aim the shooter at the high
 * targets.  Currently, the specific data to be received by the Raspberry Pi is unknown,
 * so the class is configured to take in a character array representing the image data.
 * Optimally, the client will later be set up to only receive highly mandatory data from
 * the Raspberry Pi, giving a coordinate representation of the target's spatial location.
 *
 */

#ifndef SRC_AIMING_H_
#define SRC_AIMING_H_
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
#include "Math.h"
#include "Client.h"
#include "DriveTrainController.h"
#include "Constants.h"

class Aiming {
public:

   enum STATE {
         IDLE,
         ALIGNING,
         ROTATING,
         TARGETED
      };

   Aiming(Client*, DriveTrainController*);
   void getNewImageData();
   void beginAiming();
   void align();
   void rotate();
   STATE getCurrentState();
   void setCurrentState(STATE);
   void printCurrentCoordinates();
   void run();
   virtual ~Aiming();

private:

   Client* m_client;
   DriveTrainController* m_driveTrainController;
   int m_currentCoordinates[8];
   STATE m_currentState;

};

#endif /* SRC_AIMING_H_ */
