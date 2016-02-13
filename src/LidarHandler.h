/*
 * LidarHandler.h
 *
 *  Created on: Feb 2, 2016
 *      Author: Ian
 */

#ifndef SRC_LIDARHANDLER_H_
#define SRC_LIDARHANDLER_H_

#include "WPILib.h"

#include "constants.h"

#define HIGH 1
#define LOW 0

class LidarHandler {

   //Relay controlling power cycles
   Relay * m_onSwitch;

   //Counter that gets lidar period
   Counter m_counter;

   //current lidar distance
   double m_distance;

   //current lidar distance - smooted out average
   double m_avDistance;

   //slow, medium, fast averages
   double slowAverage;
   double mediumAverage;
   double fastAverage;


   //previous stored distances
   double m_storedDistances[LidarConstants::numberStoredValues];

   //robot specific offset
   double m_offset;

   //number of resets since start
   int m_resetCount;

   //counter for distance number
   int m_storedCounter;

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

   /**
    * Return the array of previous distances
    */
   double* getDistances();

   virtual ~LidarHandler();
};

#endif /* SRC_LIDARHANDLER_H_ */
