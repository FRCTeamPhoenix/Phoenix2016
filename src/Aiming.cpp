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

Aiming::Aiming(Client* client, DriveTrainController* driveTrainController, DriveStation* driveStation) :
   m_client(client),
   m_driveTrainController(driveTrainController),
   m_driveStation(driveStation)
{
   setCurrentState(IDLE);
   m_currentTargetCoordinates[0] = AimingConstants::targetFlag;
   for (int i = 1; i <= AimingConstants::numTargetVals; i++) {
      m_currentTargetCoordinates[i] = 0;
   }

}

// IMPORTANT: Call this method to begin aiming process - same as manually setting state to first
// phase of aiming process
void Aiming::beginAiming() {
   setCurrentState(FINDING_TARGET);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   //Check for fresh data
   if(m_client->m_unreadTargetData) {

         // Updates array of current coordinates with data received by client
         for(int i = 1; i <= AimingConstants::numTargetVals; i++) {
            m_currentTargetCoordinates[i - 1] = m_client->getTargetData(i);
         }

      }

}


void Aiming::findTarget() {

   // Rotate while the first coordinate hasn't been found
   if (m_currentTargetCoordinates[AimingConstants::targetPositionData::yUL] == 0) {
      m_driveTrainController->aimRobotClockwise(5, 0.5);

      SmartDashboard::PutString("DB/String 8", "Looking for target");
   }

   else {
      setCurrentState(ROTATING);
   }

}

// Turns robot to line up with target, once target is within field of vision
void Aiming::rotate() {

   // Right side of robot is tilted too far forwards
   if ((m_currentTargetCoordinates[AimingConstants::yUR] -
         m_currentTargetCoordinates[AimingConstants::yUL]) > AimingConstants::maxTiltingFactor &&
         (m_currentTargetCoordinates[AimingConstants::yLL] -
               m_currentTargetCoordinates[AimingConstants::yLR]) > AimingConstants::maxTiltingFactor) {

      m_driveTrainController->aimRobotClockwise(1, 0.5);

      SmartDashboard::PutString("DB/String 8", "Rotating clockwise");
   }

   // Left side of robot is tilted too far forwards
   else if ((m_currentTargetCoordinates[AimingConstants::yUL] -
         m_currentTargetCoordinates[AimingConstants::yUR]) > AimingConstants::maxTiltingFactor &&
         (m_currentTargetCoordinates[AimingConstants::yLR] -
               m_currentTargetCoordinates[AimingConstants::yLL]) > AimingConstants::maxTiltingFactor) {

      m_driveTrainController->aimRobotCounterclockwise(1, 0.5);

      SmartDashboard::PutString("DB/String 8", "Rotating counterclockwise");
   }

   else if (((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
         < AimingConstants::minTargetWidth) || ((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
               > AimingConstants::maxTargetWidth)) {
      setCurrentState(APPROACHING);
   }

   else {
      SmartDashboard::PutString("DB/String 8", "Done aiming!");
      setCurrentState(IDLE);
   }
}

void Aiming::approachTarget() {

   if ((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
         < AimingConstants::minTargetWidth) {
      m_driveTrainController->moveRobotStraight(1, 0.5);

      SmartDashboard::PutString("DB/String 8", "Moving forwards");
   }

   else if ((m_currentTargetCoordinates[AimingConstants::xLR] - m_currentTargetCoordinates[AimingConstants::xLL])
         > AimingConstants::maxTargetWidth) {
      m_driveTrainController->moveRobotStraight(-1, 0.5);

      SmartDashboard::PutString("DB/String 8", "Moving backwards");
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

   if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonA)) {
         setCurrentState(IDLE);
   }

   switch(m_currentState) {
   case IDLE:
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonStart)) {
            setCurrentState(FINDING_TARGET);
      }
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
   default:
      break;
   }

}

Aiming::~Aiming() {
}
