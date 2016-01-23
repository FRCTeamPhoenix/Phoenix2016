/*
 * Aiming.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Brin Harper
 *
 * The Aiming class will take in the vision data received from the Raspberry Pi by way
 * of the UDP client, and work to implement in order to aim the shooter at the high
 * targets.  Currently, the specific data to be received by the Raspberry Pi is unknown,
 * so the class is configured to take in a character array representing the image data.
 * Optimally, the client will later be set up to only receive highly mandatory data from
 * the Raspberry Pi, giving a coordinate representation of the target's spatial location.
 *
 */

#include <Aiming.h>

Aiming::Aiming(Client* client, DriveTrainController* driveTrainController) :
   m_client(client),
   m_driveTrainController(driveTrainController)
{

}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
int* Aiming::getNewImageData() {

   char m_originalBits[128];
   strcpy(m_originalBits, m_client->getData());
   // Goes through original array of bits as chars and converts to an integer array (easier to work with)
   for (unsigned int i = 0; i < ARRAY_SIZE(m_originalBits); i++) {
      m_bitsAsInts[i] = (unsigned int) m_originalBits[i];
   }

   // Goes through array of bits and splits into groups of 16 bits (2 bytes),
   // then converts each group of 2 bytes into an integer
   for (unsigned int i = 0; i < ARRAY_SIZE(m_bitsAsInts)/16; i += 16) {
      for (unsigned int j = i*16 + 15; j >= i*16; j--) {
         m_currentCoordinates[i] += m_bitsAsInts[j] * pow(2, (j - i*16));
      }
   }

   // Cleans up memory space
   delete m_originalBits;

   return m_currentCoordinates;
}

// Centers robot about target (based on image-detected coordinates)
void Aiming::align() {

}

// Turns robot to line up with target, once target is within field of vision
void Aiming::rotate() {

   // Checks if right side of robot is tilted too far forwards
   if ((m_currentCoordinates[yUpperRight] - m_currentCoordinates[yUpperLeft]) > 20 &&
         (m_currentCoordinates[yLowerLeft] - m_currentCoordinates[yLowerRight]) > 20) {
      // TODO: Call DriveTrainController method to rotate right one degree
   }

   // Checks if left side of robot is tilted too far forwards
   else if ((m_currentCoordinates[yUpperLeft] - m_currentCoordinates[yUpperRight]) > 20 &&
         (m_currentCoordinates[yLowerRight] - m_currentCoordinates[yLowerLeft]) > 20) {
      // TODO: Call DriveTrainController method to rotate left one degree
   }
}

// This will be called in Robot.cpp to implement all aiming mechanisms
void Aiming::run() {
   getNewImageData();
   align();
   rotate();
}

Aiming::~Aiming() {
}

