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
}

// Call this method to begin aiming process - same as manually setting state to first
// phase of aiming process

void Aiming::beginAiming() {
   setCurrentState(ALIGNING);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   // Updates array of current coordinates with data received by client
   for(int i = 0; i < AimingConstants::numXYVals; i++) {
      m_currentCoordinates[i] = m_client->getData(i);
   }
}

// Centers robot about target (based on image-detected coordinates)
void Aiming::align() {

   // Robot is too far left to see target
   // Negative values indicate missing coordinates
   if (m_currentCoordinates[xUpperLeft] < AimingConstants::leftVisionBoundary ||
         m_currentCoordinates[xLowerLeft] < AimingConstants::leftVisionBoundary) {
      // TODO: Call DriveTrainController method to drive robot rightwards a little bit
   }

   // Robot is too far right to see target
   // Negative values indicate missing coordinates
   else if (m_currentCoordinates[xUpperRight] > AimingConstants::rightVisionBoundary ||
         m_currentCoordinates[xLowerRight] > AimingConstants::rightVisionBoundary
         || m_currentCoordinates[xUpperRight] < 0 || m_currentCoordinates[xLowerRight] < 0) {
      // TODO: Call DriveTrainController method to drive robot leftwards a little bit
   }

   else {
      setCurrentState(ROTATING);
   }
}

// Turns robot to line up with target, once target is within field of vision
void Aiming::rotate() {

   // Right side of robot is tilted too far forwards
   if ((m_currentCoordinates[yUpperRight] - m_currentCoordinates[yUpperLeft]) > 20 &&
         (m_currentCoordinates[yLowerLeft] - m_currentCoordinates[yLowerRight]) > 20) {
      // TODO: Call DriveTrainController method to rotate right one degree
   }

   // Left side of robot is tilted too far forwards
   else if ((m_currentCoordinates[yUpperLeft] - m_currentCoordinates[yUpperRight]) > 20 &&
         (m_currentCoordinates[yLowerRight] - m_currentCoordinates[yLowerLeft]) > 20) {
      // TODO: Call DriveTrainController method to rotate left one degree
   }

   else {
      setCurrentState(TARGETED);
   }
}

Aiming::STATE Aiming::getCurrentState() {
   return m_currentState;
}

void Aiming::setCurrentState(Aiming::STATE newState) {
   m_currentState = newState;
}

// This will be called in Robot.cpp to implement all aiming mechanisms
void Aiming::run() {

   switch(getCurrentState()) {
   case IDLE:
      break;
   case ALIGNING:
      align();
      break;
   case ROTATING:
      rotate();
      break;
   case TARGETED:
      break;
   default:
      break;
   }

}

Aiming::~Aiming() {
}


// TODO: add a function to alter state of shooter
