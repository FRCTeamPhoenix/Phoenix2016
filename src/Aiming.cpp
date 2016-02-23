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

Aiming::Aiming(Client* client, DriveTrainController* driveTrainController, DriveStation* driveStation,LidarHandler* lidar,ShooterController* shooter) :
   m_client(client),
   m_driveTrainController(driveTrainController),
   m_driveStation(driveStation),
   m_lidar(lidar),
   m_shooter(shooter)
{

   setCurrentState(IDLE);

   memset(m_currentTargetCoordinates,0,8);

   //Keeps track of the number of blank data sets sent over to Client
   //This represents the number of action cycles for which the target has not been seen
}

// IMPORTANT: Call this method to begin aiming process - same as manually setting state to first
// phase of aiming process
void Aiming::beginAiming() {
   setCurrentState(CENTERING);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   //Check for fresh data
   if(m_client->m_unreadTargetData) {

         // Updates array of current coordinates with data received by client
         for(int i = 0; i < AimingConstants::numTargetVals; i++) {
            m_currentTargetCoordinates[i] = m_client->getTargetData(i+1);
         }

         if(m_currentTargetCoordinates[AimingConstants::yUL] == 0) {
            lastArrayWasNull = true;
         } else {
            lastArrayWasNull = false;
         }

      }

}

// Turns robot to line up with target, once target is within field of vision
void Aiming::centering() {

   double m_targetCenter_x;
   double deviation;

   m_targetCenter_x=((m_currentTargetCoordinates[AimingConstants::xUL] +m_currentTargetCoordinates[AimingConstants::xLR])/2);
   deviation = (m_targetCenter_x - AimingConstants::offsetCenter);

   ostringstream print;
   print << "center: "<<m_targetCenter_x << ":" << deviation;
   SmartDashboard::PutString("DB/String 9", print.str());


   if(deviation< -10){

      SmartDashboard::PutString("DB/String 8","ccw");
      m_driveTrainController->aimRobotCounterclockwise(5,0.6f);

   }
   else if (deviation>10){
      SmartDashboard::PutString("DB/String 8","cw");
      m_driveTrainController->aimRobotClockwise(5,0.6f);
   }
   else {
      setCurrentState(IDLE);
   }

}

void Aiming::approachTarget() {

   m_shooter->setArmed();

   if (m_lidar->getFastAverage() < AimingConstants::aimedDistance - 12){
      m_driveTrainController->moveRobotStraight(-6,0.5f);
   }
   else if (m_lidar->getFastAverage() > AimingConstants::aimedDistance + 12){
         m_driveTrainController->moveRobotStraight(6,0.5f);
   }
   else {
      if (m_shooter->getCurrentState()== m_shooter->ARMED){
         m_shooter->setShooting();
      }
      setCurrentState(IDLE);

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
      SmartDashboard::PutString("DB/String 0", "State: IDLE" );
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonStart)) {
            setCurrentState(CENTERING);
      }
      break;
   case CENTERING:
      SmartDashboard::PutString("DB/String 0", "State: Centering" );
      getNewImageData();
      centering();
      break;
   case APPROACHING:
      SmartDashboard::PutString("DB/String 0", "State: Approaching" );

      getNewImageData();
      approachTarget();
   default:
      break;
   }

}

Aiming::~Aiming() {
}
