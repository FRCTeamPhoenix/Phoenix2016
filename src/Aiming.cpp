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

Aiming::Aiming(Client* client) :
   m_client(client)
{

}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
int* Aiming::getNewImageData() {

   //Assuming byte array represents a String
   //TODO: change Client BUFLEN to 248
   char originalBits[] = m_client->getData();



   // This loop will convert each byte to a character (looping through 8 bits at a time;
   // there are 8 bits in a byte)
   for (int i = 0; i < ARRAY_SIZE(originalBits) - 8; i += 8) {

   }
   delete originalBits;
   return *m_coordinateIntData;
}

// Centers the robot about the target (based on image-detected coordinates)
void Aiming::align() {

}

// This will be called in Robot.cpp to implement all aiming mechanisms
void Aiming::run() {

}

Aiming::~Aiming() {
}

