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

// IMPORTANT: Call this method to begin aiming process - same as manually setting state to first
// phase of aiming process
void Aiming::beginAiming() {
   setCurrentState(FINDING_TARGET);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   //Check for fresh data
   if(m_client->m_unreadData) {

      //Tests for shooter data
      if(m_client->getData(0) == 0) {

         // Updates array of current coordinates with data received by client
         for(int i = 1; i <= AimingConstants::numTargetVals; i++) {
            m_currentTargetCoordinates[i - 1] = m_client->getData(i);
         }
      } else {
         // Ensures that a non-applicable fresh packet won't be ignored by LoaderSense
         m_client->setPacketStatus(true);
      }
   }
}


void Aiming::findTarget() {

   // Rotate while the first coordinate hasn't been found
   if (m_currentTargetCoordinates[AimingConstants::yUL] < 0) {
      m_driveTrainController->aimRobotClockwise(5, 0.5);
   }

   else {
      setCurrentState(ROTATING);
   }

}

// Turns robot to line up with target, once target is within field of vision
void Aiming::rotate() {

   // Right side of robot is tilted too far forwards
   if ((m_currentTargetCoordinates[AimingConstants::yUR] -
         m_currentTargetCoordinates[AimingConstants::yUL]) > 20 &&
         (m_currentTargetCoordinates[AimingConstants::yLL] -
               m_currentTargetCoordinates[AimingConstants::yLR]) > 20) {

      m_driveTrainController->aimRobotClockwise(1, 0.5);
   }

   // Left side of robot is tilted too far forwards
   else if ((m_currentTargetCoordinates[AimingConstants::yUL] -
         m_currentTargetCoordinates[AimingConstants::yUR]) > 20 &&
         (m_currentTargetCoordinates[AimingConstants::yLR] -
               m_currentTargetCoordinates[AimingConstants::yLL]) > 20) {

      m_driveTrainController->aimRobotClockwise(1, 0.5);
   }

   else if (((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
         < AimingConstants::minTargetWidth) || ((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
               > AimingConstants::maxTargetWidth)) {
      setCurrentState(APPROACHING);
   }

   else {
      setCurrentState(TARGETED);
   }
}

void Aiming::approachTarget() {
   if ((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
         < AimingConstants::minTargetWidth) {
      m_driveTrainController->moveRobotStraight(1, 0.5);
   }

   else if ((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
         < AimingConstants::minTargetWidth) {
      m_driveTrainController->moveRobotStraight(-1, 0.5);
   }

   else {
      setCurrentState(ROTATING);
   }
}

void Aiming::setTargetCoordinateValue(AimingConstants::targetPositionData position, int newValue) {
   m_currentTargetCoordinates[position] = newValue;
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
   cout << "(" << m_currentTargetCoordinates[AimingConstants::xUL] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yUL] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xUR] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yUR] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xLL] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yLL] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xLR] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yLR] << ")" << endl;
}

// Called to implement all aiming mechanisms
void Aiming::run() {

   switch(getCurrentState()) {
   case IDLE:
      break;
   case FINDING_TARGET:
      getNewImageData();
      findTarget();
      break;
   case ROTATING:
      getNewImageData();
      rotate();
      break;
   case APPROACHING:
      getNewImageData();
      approachTarget();
   case TARGETED:
      // Reset the aiming state
      setCurrentState(IDLE);
      break;
   default:
      break;
   }

}

Aiming::~Aiming() {
}
