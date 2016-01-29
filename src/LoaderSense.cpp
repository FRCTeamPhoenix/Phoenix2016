/*
 * LoaderSense.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Brin Harper
 */

#include "LoaderSense.h"

LoaderSense::LoaderSense(Client* client, DriveTrainController* driveTrainController) :
   m_client(client),
   m_driveTrainController(driveTrainController)
{
   setCurrentState(IDLE);
}

// IMPORTANT: Call to this method will implement the Loader's alignment process
void LoaderSense::beginAligning() {
   setCurrentState(ROTATING);
}

// Refreshes array containing received client data (ball's radius and center coordinates)
void LoaderSense::updateBallPositionData() {

   // TODO: Make sure that this array setup is in the appropriate format to match the client getter method

   // Checks if data is fresh
   if (m_client->m_unreadData) {

      // Tests for loader data
      if(m_client->getData[0] == 1) {

         for(int i = 1; i <= LoaderSenseConstants::numBallVals; i++) {

                     // Parameter passed to getData() corresponds to appropriate index of integer array received by client;
                     // ball position values (are presumed to) immediately follow target position values in received array
                     m_currentBallPosition[i - 1] = m_client->getData(AimingConstants::numTargetVals - 1 + i);
         }

      } else {
         // Avoids causing data to be ignored by Aiming class
         m_client->setPacketStatus(true);
      }
   }
}

int LoaderSense::getCurrentRadius() {
   return m_currentBallPosition[LoaderSenseConstants::ballRadius];
}

int LoaderSense::getCurrentXCenter() {
   return m_currentBallPosition[LoaderSenseConstants::ballCenterX];
}

int LoaderSense::getCurrentYCenter() {
   return m_currentBallPosition[LoaderSenseConstants::ballCenterY];
}

// Alter current state of LoaderSense module (possible parameters: IDLE, ROTATING, APPROACHING, BACKUP, TARGETED)
void LoaderSense::setCurrentState(STATE newState) {
   m_currentState = newState;
}

// Returns current state of LoaderSense module
LoaderSense::STATE LoaderSense::getCurrentState() {
   return m_currentState;
}

// Called to re-center whenever the ball is too far left or right
// IMPORTANT NOTE: will not rotate until ball is a safe distance away
void LoaderSense::rotate() {

   if (m_currentBallPosition[LoaderSenseConstants::ballCenterX] < LoaderSenseConstants::minGoodCenterX) {
      if (m_currentBallPosition[LoaderSenseConstants::ballRadius] > LoaderSenseConstants::maxSafeRotationRadius) {
         setCurrentState(BACKUP);
      } else {
         //TODO:Call DriveTrainController function to rotate clockwise a little bit
      }
   } else if (m_currentBallPosition[LoaderSenseConstants::ballCenterY] > LoaderSenseConstants::maxGoodCenterX) {
      if(m_currentBallPosition[LoaderSenseConstants::ballRadius] > LoaderSenseConstants::maxSafeRotationRadius) {
         setCurrentState(BACKUP);
      } else {
         //TODO:Call DriveTrainController function to rotate counterclockwise a little bit
      }
   } else {
      setCurrentState(APPROACHING);
   }
}

// Approach ball until it is close enough to be loaded
void LoaderSense::approach() {

   if (m_currentBallPosition[LoaderSenseConstants::ballRadius] < LoaderSenseConstants::minGoodRadius) {
      //TODO:Call to DriveTrainController function to move forwards a little bit
      setCurrentState(ROTATING);
   } else {
      setCurrentState(TARGETED);
   }
}

// Back up until rotation can be safely completed
void LoaderSense::backup() {

   // FIRST THING THAT SHOULD BE EXECUTED IS A SLIGHT BACKUP
   //TODO:Call to DriveTrainController function to back up a little bit

   if(m_currentBallPosition[LoaderSenseConstants::ballRadius] < LoaderSenseConstants::maxSafeRotationRadius) {
      setCurrentState(ROTATING);
   } else {
      //TODO:Call to the DriveTrainController function to back up a little bit
   }
}

// Called to implement all LoaderSense mechanisms
void LoaderSense::run() {

   switch(getCurrentState()) {
   case IDLE:
      break;
   case ROTATING:
      rotate();
      break;
   case APPROACHING:
      approach();
      break;
   case BACKUP:
      backup();
      break;
   case TARGETED:
      // Reset loader alignment state
      setCurrentState(IDLE);
      break;
   default:
      break;
   }

}

LoaderSense::~LoaderSense() {

}
