/*
 * LidarHandler.h
 *
 *  Created on: Feb 2, 2016
 *      Author: Ian
 */

#ifndef SRC_LIDARHANDLER_H_
#define SRC_LIDARHANDLER_H_

#include "WPILib.h"

#define HIGH 1
#define LOW 0

class LidarHandler {

   //Relay controlling power cycles
   Relay * m_onSwitch;

   //Counter that gets lidar period
   Counter m_counter;

   //current lidar distance
   double m_distance;

   //robot specific offset
   double m_offset;

   //number of resets since start
   int m_resetCount;

public:
   /**
    * Constructor. Takes in onSwitch analog relay, offset double, and the port number for the lidar.
    */
   LidarHandler(Relay * m_onSwitch, double offset, uint32_t lidarPort);

   /**
    * Updates the public current distance based on lidar input.
    * Also power-cycles it if needed.
    */
   void run();

   /**
    * Return the current distance from the lidar
    */
   double getDistance();

   /**
    * Return the lidar reset count
    */
   int getResetCount();

   virtual ~LidarHandler();
};

#endif /* SRC_LIDARHANDLER_H_ */
