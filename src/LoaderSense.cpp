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
}

// IMPORTANT: Call to this method will implement the Loader's alignment process
void LoaderSense::beginAligning() {
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

         std::ostringstream LSenseStatus;
         LSenseStatus << "Looking for ball";
         SmartDashboard::PutString("DB/String 9", LSenseStatus.str());
      }

      else {
         setCurrentState(ROTATING);
      }
}

// Called to re-center whenever the ball is too far left or right
// IMPORTANT NOTE: will not rotate until ball is a safe distance away
void LoaderSense::rotate() {

   if (m_currentBallPosition[LoaderSenseConstants::ballCenterX] < LoaderSenseConstants::minGoodCenterX) {

      if (m_currentBallPosition[LoaderSenseConstants::ballRadius] > LoaderSenseConstants::maxSafeRotationRadius) {

         setCurrentState(BACKUP);

      } else {

         //Robot will rotate clockwise 1 degree, at motor speed 0.5
         m_driveTrainController->aimRobotClockwise(1, 0.5);

         std::ostringstream LSenseStatus;
         LSenseStatus << "Rotating clockwise";
         SmartDashboard::PutString("DB/String 9", LSenseStatus.str());

      }

   } else if (m_currentBallPosition[LoaderSenseConstants::ballCenterX] > LoaderSenseConstants::maxGoodCenterX) {

      if(m_currentBallPosition[LoaderSenseConstants::ballRadius] > LoaderSenseConstants::maxSafeRotationRadius) {

         setCurrentState(BACKUP);

      } else {

         //Robot will rotate counterclockwise 1 degree, at motor speed 0.5
         m_driveTrainController->aimRobotCounterclockwise(1, 0.5);

         std::ostringstream LSenseStatus;
         LSenseStatus << "Rotating counterclockwise";
         SmartDashboard::PutString("DB/String 9", LSenseStatus.str());
      }

   } else {

      setCurrentState(APPROACHING);

   }
}

// Approach ball until it is close enough to be loaded
void LoaderSense::approach() {

   if (m_currentBallPosition[LoaderSenseConstants::ballRadius] < LoaderSenseConstants::minGoodRadius) {
      //Robot will move forward an inch, at motor speed 0.5
      m_driveTrainController->moveRobotStraight(1, 0.5);

      std::ostringstream LSenseStatus;
      LSenseStatus << "Moving forwards";
      SmartDashboard::PutString("DB/String 9", LSenseStatus.str());

      setCurrentState(ROTATING);
   } else {
      setCurrentState(IDLE);
   }

}

// Back up until rotation can be safely completed
void LoaderSense::backup() {

   if(m_currentBallPosition[LoaderSenseConstants::ballRadius] < LoaderSenseConstants::maxSafeRotationRadius) {

      setCurrentState(ROTATING);

   } else {

      m_driveTrainController->moveRobotStraight(-1, 0.5);

      std::ostringstream LSenseStatus;
      LSenseStatus << "Backing up";
      SmartDashboard::PutString("DB/String 9", LSenseStatus.str());

   }

}

// Called to implement all LoaderSense mechanisms
void LoaderSense::run() {

   switch(m_currentState) {
   case IDLE:
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
