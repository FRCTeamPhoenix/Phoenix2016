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

}

void LoaderSense::updateBallPositionData() {

   // Placeholder values
   for(int i = 0; i < ARRAY_SIZE(m_currentBallPosition); i++) {
      m_currentBallPosition[i] = 23;
   }

   // TODO: Make sure that the client method is in the appropriate format to correspond with this setup
   // IMPORTANT QUESTIONS for the rest of the vision group: Will all data be sent over in a single packet,
   // or will separate packets be sent over for each data subgroup? --> What kinds of getter methods and
   // arrays will I be working with?

   /*
   for(int i = 0; i < ARRAY_SIZE(m_currentBallPosition); i++) {
      m_currentBallPosition[i] = m_client->getData(i);
   }
   */

}

void LoaderSense::setCurrentState(STATE newState) {
   m_currentState = newState;
}

LoaderSense::STATE LoaderSense::getCurrentState() {
   return m_currentState;
}

void LoaderSense::run() {

   switch(getCurrentState()) {
   case IDLE:
      break;
   case INITIAL_ALIGN:
      // Call to alignment function
      break;
   case APPROACHING:
      // Call to movement function
      break;
   case FINAL_ALIGN:
      // Another call to alignment function
      break;
   case TARGETED:
      // Call to state getter function - pass in parameter IDLE
      break;
   default:
      break;
   }

}

LoaderSense::~LoaderSense() {

}

