/*
 * LoaderSense.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Brin Harper
 */

#include "LoaderSense.h"

LoaderSense::LoaderSense(Client* client, DriveTrainController* driveTrainController, DriveStation* driveStation) :
   m_client(client),
   m_driveTrainController(driveTrainController),
   m_driveStation(driveStation)
{
   setCurrentState(IDLE);
   m_currentBallPosition[0] = LoaderSenseConstants::loaderFlag;
   for (int i = 1; i <= LoaderSenseConstants::numBallVals; i++) {
      m_currentBallPosition[i] = 0;
   }

   lastArrayWasNull = true;

   //Keeps track of the number of blank data sets sent over to Client
   //This represents the number of action cycles for which the ball has not been seen
   nullArraysInARow = 0;

}

// IMPORTANT: Call to this method will implement the Loader's alignment process
void LoaderSense::beginAiming() {
   setCurrentState(FINDING_BALL);
}

// Refreshes array containing received client data (ball's radius and center coordinates)
void LoaderSense::updateBallPositionData() {

   // TODO: Make sure that this array setup is in the appropriate format to match the client getter method

   // Checks if data is fresh
   if (m_client->m_unreadBallData) {

      for(int i = 1; i <= LoaderSenseConstants::numBallVals; i++) {

       // Parameter passed to getData() corresponds to appropriate index of integer array received by client;
       // ball position values (are presumed to) immediately follow target position values in received array
       m_currentBallPosition[i - 1] = m_client->getBallData(i);

         }

      if(m_currentBallPosition[LoaderSenseConstants::ballRadius] == 0) {
         lastArrayWasNull = true;
      } else {
         lastArrayWasNull = false;
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

// Alter current state of LoaderSense module (possible parameters: IDLE, ROTATING, APPROACHING, BACKUP)
void LoaderSense::setCurrentState(STATE newState) {
   m_currentState = newState;
}

// Returns current state of LoaderSense module
LoaderSense::STATE LoaderSense::getCurrentState() {
   return m_currentState;
}

// Called upon invocation of LoaderSense aiming mechanism, in order to get ball within field of vision
void LoaderSense::findBall() {
   // Rotate while the first coordinate hasn't been found
      if (m_currentBallPosition[LoaderSenseConstants::ballCenterX] == 0) {
         m_driveTrainController->aimRobotClockwise(5, 0.5);

         SmartDashboard::PutString("DB/String 9", "Looking for ball");
      }

      else {
         setCurrentState(ROTATING);
      }
}

// Called to re-center whenever the ball is too far left or right
// IMPORTANT NOTE: will not rotate until ball is a safe distance away
void LoaderSense::rotate() {

   if (lastArrayWasNull) {
      nullArraysInARow++;
      //Goes back to trying to find the ball, if three cycles in a row yield no data
      if (nullArraysInARow >= 3) {
         nullArraysInARow = 0;
         setCurrentState(FINDING_BALL);
      }
   }

   else {

      nullArraysInARow = 0;

      if (m_currentBallPosition[LoaderSenseConstants::ballCenterX] < LoaderSenseConstants::minGoodCenterX) {

         if (m_currentBallPosition[LoaderSenseConstants::ballRadius] > LoaderSenseConstants::maxSafeRotationRadius) {

            setCurrentState(BACKUP);

         } else {

            //Robot will rotate clockwise 1 degree, at motor speed 0.5
            m_driveTrainController->aimRobotClockwise(1, 0.5);

            SmartDashboard::PutString("DB/String 9", "Rotating clockwise");

         }

      } else if (m_currentBallPosition[LoaderSenseConstants::ballCenterX] > LoaderSenseConstants::maxGoodCenterX) {

         if(m_currentBallPosition[LoaderSenseConstants::ballRadius] > LoaderSenseConstants::maxSafeRotationRadius) {

            setCurrentState(BACKUP);

         } else {

            //Robot will rotate counterclockwise 1 degree, at motor speed 0.5
            m_driveTrainController->aimRobotCounterclockwise(1, 0.5);

            SmartDashboard::PutString("DB/String 9", "Rotating counterclockwise");
         }

      } else {

         setCurrentState(APPROACHING);

      }

   }

}

// Approach ball until it is close enough to be loaded
void LoaderSense::approach() {

   if (lastArrayWasNull) {
         nullArraysInARow++;
         //Goes back to trying to find the ball, if three cycles in a row yield no data
         if (nullArraysInARow >= 3) {
            nullArraysInARow = 0;
            setCurrentState(FINDING_BALL);
         }
      }

   else {

      nullArraysInARow = 0;

      if (m_currentBallPosition[LoaderSenseConstants::ballRadius] < LoaderSenseConstants::minGoodRadius) {
         //Robot will move forward an inch, at motor speed 0.5
         m_driveTrainController->moveRobotStraight(1, 0.5);

         SmartDashboard::PutString("DB/String 9", "Moving forwards");

         setCurrentState(ROTATING);
      } else {
         setCurrentState(IDLE);
      }

   }

}

// Back up until rotation can be safely completed
void LoaderSense::backup() {

   if (lastArrayWasNull) {
         nullArraysInARow++;
         //Goes back to trying to find the ball, if three cycles in a row yield no data
         if (nullArraysInARow >= 3) {
            nullArraysInARow = 0;
            setCurrentState(FINDING_BALL);
         }
      }

   else {

      nullArraysInARow = 0;

      if(m_currentBallPosition[LoaderSenseConstants::ballRadius] < LoaderSenseConstants::maxSafeRotationRadius) {

         setCurrentState(ROTATING);

      } else {

         m_driveTrainController->moveRobotStraight(-1, 0.5);

         SmartDashboard::PutString("DB/String 9", "Backing up");

      }

   }

}

// Called to implement all LoaderSense mechanisms
void LoaderSense::run() {

   if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonA)) {
      setCurrentState(IDLE);
   }

   switch(m_currentState) {
   case IDLE:
      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonBack)) {
            setCurrentState(FINDING_BALL);
      }
      break;
   case FINDING_BALL:
      updateBallPositionData();
      findBall();
      break;
   case ROTATING:
      updateBallPositionData();
      rotate();
      break;
   case APPROACHING:
      updateBallPositionData();
      approach();
      break;
   case BACKUP:
      updateBallPositionData();
      backup();
      break;
   default:
      break;
   }

}

LoaderSense::~LoaderSense() {

}
