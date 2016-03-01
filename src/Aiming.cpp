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


   // Nothing is happening
   setCurrentState(IDLE);

   // We have not yet approached
   hasApproached=false;

   // By default, we will only be performing a specified part of the aiming process
   // In order to perform the ENTIRE process (including shooting), START should be pressed
   fullProcess=false;

   // "Clean slate" for the target coordinate array!
   memset(m_currentTargetCoordinates,0,8);
}

// Call this method to begin aiming process - same as manually setting state to first phase of aiming process
void Aiming::beginAiming() {
   setCurrentState(CENTERING);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   if (m_client->checkPacketState()){
   // Updates array of current coordinates with data received by client
      newCenter=true;
      for(int i = 0; i < AimingConstants::numTargetVals; i++) {
         m_currentTargetCoordinates[i] = m_client->getTargetData(i+1);
      }
   }
}

// Turns robot to line up with target, once target is within field of vision
void Aiming::centering() {

   driveIdle=false;
   newCenter=false;

   if ((m_driveTrainController->getCurrentState()==DriveTrainController::IDLE
         || m_driveTrainController->getCurrentState()==DriveTrainController::TELEOP )){
      driveIdle=true;
   }

   initialTargetCenterX=m_targetCenter_x;
   m_targetCenter_x=((m_currentTargetCoordinates[AimingConstants::xUL] +m_currentTargetCoordinates[AimingConstants::xLR])/2);
   // Amount of offset from our desired center coordinate (w/ respect to current frame of vision)

   deviation = (m_targetCenter_x - AimingConstants::desiredCenter);

//   if (m_targetCenter_x != initialTargetCenterX){
//      newCenter=true;
//   }

   //only move if the drivtrain is idle and we have received the most recent packet
   if (driveIdle && newCenter){
      newCenter=false;
      //move ccw if target right of desired
      if(deviation< -AimingConstants::rotationVariance){
         m_driveTrainController->aimRobotCounterclockwise(1, 0.6f);

      }
      //move robot cw if target is left of desired
      else if (deviation > AimingConstants::rotationVariance){

         m_driveTrainController->aimRobotClockwise(1, 0.6f);

      }
      //if target is within tolerence move to next state
      else if (deviation <  AimingConstants::rotationVariance && deviation > -AimingConstants::rotationVariance){

         if (!hasApproached && fullProcess){
            setCurrentState(APPROACHING);
         }
         else if (hasApproached && fullProcess){
            setCurrentState(SHOOTING);
         }
         else {
            setCurrentState(IDLE);

         }
      }
   }
}


void Aiming::approachTarget() {


   // Decide if we need to move forward or backwards
   if (m_lidar->getFastAverage() < AimingConstants::aimedDistance - AimingConstants::distanceVariance){
      m_driveTrainController->moveRobotStraight(-6,0.5f);
   }
   else if (m_lidar->getFastAverage() > AimingConstants::aimedDistance + AimingConstants::distanceVariance){
         m_driveTrainController->moveRobotStraight(6,0.5f);
   }

   // We're done approaching and can move to the next phase we need!
   else {
      hasApproached=true;
      if (fullProcess){
         setCurrentState(CENTERING);

      }
      else {
         setCurrentState(IDLE);
      }

   }
}
void Aiming::setTargetCoordinateValue(AimingConstants::targetPositionData position, int newValue) {
   m_currentTargetCoordinates[position] = newValue;
}

Aiming::STATE Aiming::getCurrentState() {
   return m_currentState;
}

void Aiming::setFullProcess(bool processVariant) {
   fullProcess = processVariant;
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

   getNewImageData();
   printCurrentCoordinates();
   m_targetCenter_x=((m_currentTargetCoordinates[AimingConstants::xUL] +m_currentTargetCoordinates[AimingConstants::xLR])/2);
   deviation = (m_targetCenter_x - AimingConstants::desiredCenter);

   ostringstream aimingPrints;
   aimingPrints<< "C: " << m_targetCenter_x << ", " << "D: " << deviation;
   SmartDashboard::PutString("DB/String 9",aimingPrints.str());

   switch(m_currentState) {
   case IDLE:
      m_driveTrainController->setGoalState(m_driveTrainController->TELEOP);
      fullProcess=false;
      hasApproached=false;
      getNewImageData();

      SmartDashboard::PutString("DB/String 0", "State: IDLE" );

      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonStart)) {
            fullProcess=true;
            setCurrentState(CENTERING);
      }
      else if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonB)) {
         setCurrentState(APPROACHING);
      }
      else if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonY)) {
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
      break;
   default:
      break;
   }

}

Aiming::~Aiming() {
}
