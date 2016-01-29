/*
 * Aiming.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Brin Harper
 *
 * The Aiming class takes in the vision data received from the Raspberry Pi, by way
 * of the UDP client.  This data is passed to the Aiming class in the form
 * of an integer array, which represents the coordinates of the target's four corners.
 * Aiming implements the received vision data in order to align and rotate the robot,
 * until the the shooter is positioned correctly to shoot at the desired high target.
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
   int m_currentTargetCoordinates[8];
   STATE m_currentState;

};

#endif /* SRC_AIMING_H_ */