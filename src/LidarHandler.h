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
#include "ConfigEditor.h"

#define HIGH 1
#define LOW 0

class LidarHandler {

   //Relay controlling power cycles
   Relay * m_onSwitch;

   //Interfaces with the preferences file
   ConfigEditor * m_configEditor;

   //Counter that gets lidar period
   Counter m_counter;

   //current lidar distance
   double m_distance;

   //slow, medium, fast averages
   double m_slowAverage;
   double m_mediumAverage;
   double m_fastAverage;

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
   LidarHandler(Relay * m_onSwitch, ConfigEditor * configEditor, uint32_t lidarPort);

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
    * Return fast, medium, and slow averages
    */
   double getFastAverage();
   double getMediumAverageDEPRECATED();
   double getSlowAverage();

   virtual ~LidarHandler();
};

#endif /* SRC_LIDARHANDLER_H_ */
