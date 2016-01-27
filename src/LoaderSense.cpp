/*
 * LoaderSense.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Brin Harper
 */

#include "LoaderSense.h"

LoaderSense::LoaderSense(Client* client, LoaderController* loaderController) :
   m_client(client),
   m_loaderController(loaderController)
{
   setCurrentState(IDLE);
}

// Call to this method will implement the Loader's alignment process
void LoaderSense::beginAligning() {
   setCurrentState(ROTATING);
}

void LoaderSense::updateBallPositionData() {

   // TODO: Make sure that this array setup is in the appropriate format to match the client getter method

   for(int i = 0; i < LoaderSenseConstants::numBallVals; i++) {

      // Parameter passed to getData() corresponds to appropriate index of integer array received by client;
      // ball position values immediately follow target position values in received array
      m_currentBallPosition[i] = m_client->getData(AimingConstants::numTargetVals - 1 + i);

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


void LoaderSense::setCurrentState(STATE newState) {
   m_currentState = newState;
}

LoaderSense::STATE LoaderSense::getCurrentState() {
   return m_currentState;
}

//TODO: translate the following three methods from pseudocode to actual code

void LoaderSense::rotate() {
   //Check if rotation is needed
      //If YES, then check if you'll hit the ball when you rotate (too close?)
         //If YES, set state to BACKUP
         //If NO, perform necessary rotation - rotate small amounts, and continually check for completion
            //-Call to the DriveTrainController rotation function
      //If NO, then set state to APPROACHING
}

void LoaderSense::approach() {
   //Check if you need to move towards the ball
      //If YES, go gradually - move forwards a small amount, then set state to ROTATING
         //(possible logical flaw? examine more closely later...)
            //-Call to the DriveTrainController forward movement function
      //If NO, set state to TARGETED
}

void LoaderSense::backup() {
   //Back up, then check if you have backed up enough to have a "safe" margin of rotational space
         //(-Call to the DriveTrainController backward movement function)
      //If YES, set state to ROTATING
      //If NO, continue backing up
         //-Call to the backup travel function
}

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

