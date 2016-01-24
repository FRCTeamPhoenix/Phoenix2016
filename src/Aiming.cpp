/*
 * Aiming.cpp
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

#include <Aiming.h>

Aiming::Aiming(Client* client, DriveTrainController* driveTrainController) :
   m_client(client),
   m_driveTrainController(driveTrainController)
{
   setCurrentState(IDLE);
   //TESTING
   int testingArray[8] = {170, 180, 340, 200, 170, 80, 340, 40};
      for(int i = 0; i < AimingConstants:: numXYVals; i++) {
         m_currentCoordinates[i] = testingArray[i];
      }
   beginAiming();
}

// Call this method to begin aiming process - same as manually setting state to first
// phase of aiming process

void Aiming::beginAiming() {
   cout << "BEGINNING PHASE 1: ALIGN" << endl;
   setCurrentState(ALIGNING);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   /*
   // Updates array of current coordinates with data received by client
   for(int i = 0; i < AimingConstants::numXYVals; i++) {
      m_currentCoordinates[i] = m_client->getData(i);
   }
   */

}

// Centers robot about target (based on image-detected coordinates)
void Aiming::align() {

   // Robot is too far left to see target
   // Negative values indicate missing coordinates
   if (m_currentCoordinates[AimingConstants::xUpperLeft] < AimingConstants::leftVisionBoundary ||
         m_currentCoordinates[AimingConstants::xLowerLeft] < AimingConstants::leftVisionBoundary) {

      //TESTING
      cout << "Moving right" << endl;

      // TODO: Call DriveTrainController method to drive robot rightwards a little bit
   }

   // Robot is too far right to see target
   // Negative values indicate missing coordinates
   else if (m_currentCoordinates[AimingConstants::xUpperRight] > AimingConstants::rightVisionBoundary ||
         m_currentCoordinates[AimingConstants::xLowerRight] > AimingConstants::rightVisionBoundary ||
         m_currentCoordinates[AimingConstants::xUpperRight] < 0 ||
         m_currentCoordinates[AimingConstants::xLowerRight] < 0) {
      // TODO: Call DriveTrainController method to drive robot leftwards a little bit

      //TESTING
      cout << "Moving left" << endl;

   }

   else {
      setCurrentState(ROTATING);
      cout << "BEGINNING PHASE 2: ROTATE" << endl;
   }

   setCurrentState(ROTATING);
   cout << "BEGINNING PHASE 2: ROTATE" << endl;
}

// Turns robot to line up with target, once target is within field of vision
void Aiming::rotate() {

   // Right side of robot is tilted too far forwards
   if ((m_currentCoordinates[AimingConstants::yUpperRight] -
         m_currentCoordinates[AimingConstants::yUpperLeft]) > 20 &&
         (m_currentCoordinates[AimingConstants::yLowerLeft] -
               m_currentCoordinates[AimingConstants::yLowerRight]) > 20) {
      // TODO: Call DriveTrainController method to rotate right one degree

      //TESTING
      cout << "Rotating clockwise" << endl;


   }

   // Left side of robot is tilted too far forwards
   else if ((m_currentCoordinates[AimingConstants::yUpperLeft] -
         m_currentCoordinates[AimingConstants::yUpperRight]) > 20 &&
         (m_currentCoordinates[AimingConstants::yLowerRight] -
               m_currentCoordinates[AimingConstants::yLowerLeft]) > 20) {
      // TODO: Call DriveTrainController method to rotate left one degree

      //TESTING
     cout << "Rotating counterclockwise" << endl;

   }

   else {
      setCurrentState(TARGETED);
   }
   setCurrentState(TARGETED);
}

Aiming::STATE Aiming::getCurrentState() {
   return m_currentState;
}

void Aiming::setCurrentState(Aiming::STATE newState) {
   m_currentState = newState;
}

// Outputs current coordinate values of target corners, in the following format:
// "(xUpperLeft, yUpperLeft), (xUpperRight, yUpperRight), (xLowerLeft, yLowerLeft),
// (xLowerRight, yLowerRight)"

void Aiming::printCurrentCoordinates() {
   cout << "(" << m_currentCoordinates[AimingConstants::xUpperLeft] << ", " <<
         m_currentCoordinates[AimingConstants::yUpperLeft] << "), (" <<
         m_currentCoordinates[AimingConstants::xUpperRight] << ", " <<
         m_currentCoordinates[AimingConstants::yUpperRight] << "), (" <<
         m_currentCoordinates[AimingConstants::xLowerLeft] << ", " <<
         m_currentCoordinates[AimingConstants::yLowerLeft] << "), (" <<
         m_currentCoordinates[AimingConstants::xLowerRight] << ", " <<
         m_currentCoordinates[AimingConstants::yLowerRight] << ")" << endl;
}

// This will be called in Robot.cpp to implement all aiming mechanisms
void Aiming::run() {

   switch(getCurrentState()) {
   case IDLE:
      break;
   case ALIGNING:
   //   getNewImageData();
      align();
      break;
   case ROTATING:
   //   getNewImageData();
      rotate();
      break;
   case TARGETED:
      cout << "TARGETED" << endl;
      setCurrentState(IDLE);
      break;
   default:
      break;
   }

}

Aiming::~Aiming() {
}


// TODO: add a function to alter state of shooter
