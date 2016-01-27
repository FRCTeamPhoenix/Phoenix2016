/*
 * Aiming.cpp
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
   cout << "BEGINNING PHASE 1: ALIGN" << endl;
   setCurrentState(ALIGNING);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   // Updates array of current coordinates with data received by client
   for(int i = 0; i < AimingConstants::numTargetVals; i++) {
      m_currentTargetCoordinates[i] = m_client->getData(i);
   }

}

// Centers robot about target (based on image-detected coordinates)
void Aiming::align() {

   // Robot is too far left to see target
   // Negative values indicate missing coordinates
   if (m_currentTargetCoordinates[AimingConstants::xUpperLeft] < AimingConstants::leftVisionBoundary ||
         m_currentTargetCoordinates[AimingConstants::xLowerLeft] < AimingConstants::leftVisionBoundary) {

      //TESTING
      cout << "Moving right" << endl;

      // TODO: Call DriveTrainController method to drive robot rightwards a little bit
   }

   // Robot is too far right to see target
   // Negative values indicate missing coordinates
   else if (m_currentTargetCoordinates[AimingConstants::xUpperRight] > AimingConstants::rightVisionBoundary ||
         m_currentTargetCoordinates[AimingConstants::xLowerRight] > AimingConstants::rightVisionBoundary ||
         m_currentTargetCoordinates[AimingConstants::xUpperRight] < 0 ||
         m_currentTargetCoordinates[AimingConstants::xLowerRight] < 0) {

      //TESTING
      cout << "Moving left" << endl;

      // TODO: Call DriveTrainController method to drive robot leftwards a little bit
   }

   else {
      setCurrentState(ROTATING);
      cout << "BEGINNING PHASE 2: ROTATE" << endl;
   }
}

// Turns robot to line up with target, once target is within field of vision
void Aiming::rotate() {

   // Right side of robot is tilted too far forwards
   if ((m_currentTargetCoordinates[AimingConstants::yUpperRight] -
         m_currentTargetCoordinates[AimingConstants::yUpperLeft]) > 20 &&
         (m_currentTargetCoordinates[AimingConstants::yLowerLeft] -
               m_currentTargetCoordinates[AimingConstants::yLowerRight]) > 20) {

      //TESTING
      cout << "Rotating clockwise" << endl;

      // TODO: Call DriveTrainController method to rotate right one degree

   }

   // Left side of robot is tilted too far forwards
   else if ((m_currentTargetCoordinates[AimingConstants::yUpperLeft] -
         m_currentTargetCoordinates[AimingConstants::yUpperRight]) > 20 &&
         (m_currentTargetCoordinates[AimingConstants::yLowerRight] -
               m_currentTargetCoordinates[AimingConstants::yLowerLeft]) > 20) {

      //TESTING
      cout << "Rotating counterclockwise" << endl;

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

// Outputs current coordinate values of target corners, in the following format:
// "(xUpperLeft, yUpperLeft), (xUpperRight, yUpperRight), (xLowerLeft, yLowerLeft),
// (xLowerRight, yLowerRight)"
void Aiming::printCurrentCoordinates() {
   cout << "(" << m_currentTargetCoordinates[AimingConstants::xUpperLeft] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yUpperLeft] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xUpperRight] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yUpperRight] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xLowerLeft] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yLowerLeft] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xLowerRight] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yLowerRight] << ")" << endl;
}

// This will be called in Robot.cpp to implement all aiming mechanisms
void Aiming::run() {

   switch(getCurrentState()) {
   case IDLE:
      break;
   case ALIGNING:
      getNewImageData();
      align();
      break;
   case ROTATING:
      getNewImageData();
      rotate();
      break;
   case TARGETED:
      cout << "TARGETED" << endl;
      // Reset the aiming state
      setCurrentState(IDLE);
      break;
   default:
      break;
   }

}

Aiming::~Aiming() {
}
