/*
 * LidarHandler.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: Ian
 */

#include "LidarHandler.h"

/**
 * All distances in class are in inches
 */
LidarHandler::LidarHandler(Relay * onSwitch, ConfigEditor * configEditor, uint32_t lidarPort):
   m_onSwitch(onSwitch),
   m_configEditor(configEditor),
   m_counter(lidarPort){
   m_onSwitch->Set(Relay::kOn);
   m_counter.SetSemiPeriodMode(true);
   m_resetCount = 0;
   m_storedCounter = 0;
   m_distance = 0;
   m_fastAverage = 0;
   m_mediumAverage = 0;
   m_slowAverage = 0;

   m_offset = m_configEditor->getDouble("lidarOffset");

   for(int i=0;i<LidarConstants::numberStoredValues;i++)
      m_storedDistances[i] = 0;
}

double LidarHandler::getFastAverage() {
   return m_fastAverage;
}


double LidarHandler::getMediumAverageDEPRECATED() {
   return m_mediumAverage;
}

double LidarHandler::getSlowAverage() {
   return m_slowAverage;
}

void LidarHandler::run() {
    double distance = m_counter.GetPeriod() * LidarConstants::periodToInches  - m_offset;

    //this will be true if distance is inf or NaN (i.e. the lidar has crashed)
    bool infDistance = distance - distance != 0;

    if(infDistance) {
       m_resetCount++;
       m_onSwitch->Set(Relay::kOff);
       Wait(0.3);
       m_onSwitch->Set(Relay::kOn);
    } else {
       m_distance = distance;

       m_storedDistances[m_storedCounter % LidarConstants::numberStoredValues] = distance;
       m_storedCounter++;

       double fast = m_configEditor->getDouble("fastAverageFactor");
       m_fastAverage = (fast * m_fastAverage + m_distance) / (fast + 1.0);

       m_mediumAverage = (10 * m_mediumAverage + m_distance) / 11.0;

       double slow = m_configEditor->getDouble("slowAverageFactor");
       m_slowAverage = (slow * m_slowAverage + m_distance) / (slow + 1.0);
    }
}

double LidarHandler::getDistance() {
   return m_distance;
}

int LidarHandler::getResetCount() {
   return m_resetCount;
}

LidarHandler::~LidarHandler() {

}

