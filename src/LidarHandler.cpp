/*
 * LidarHandler.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: Ian
 */

#include <LidarHandler.h>

LidarHandler::LidarHandler(Relay * onSwitch, double offset, uint32_t lidarPort):
   m_onSwitch(onSwitch),
   m_counter(lidarPort),
   m_offset(offset) {
   m_onSwitch->Set(Relay::kOn);
   m_counter.SetSemiPeriodMode(true);
   m_resetCount = 0;
   m_storedCounter = 0;

   for(int i=0;i<LidarConstants::numberStoredValues;i++)
      m_storedDistances[i] = 0;
}

void LidarHandler::run() {
    double distance = m_counter.GetPeriod() * 100000;

    //this will be true if distance is inf or NaN (i.e. the lidar has crashed)
    bool infDistance = distance - distance != 0;

    if(infDistance) {
       SmartDashboard::PutBoolean("DB/Button 1",false);
       m_resetCount++;
       m_onSwitch->Set(Relay::kOff);
       SmartDashboard::PutString("DB/String 1", "resetting");
       Wait(0.3);
       SmartDashboard::PutString("DB/String 1", " ");
       m_onSwitch->Set(Relay::kOn);
    } else {
       m_distance = distance;

       m_storedDistances[m_storedCounter % LidarConstants::numberStoredValues] = distance;
       m_storedCounter++;

       m_avDistance = (4 * m_avDistance + m_distance) / 5;
    }
}

double LidarHandler::getDistance() {
   return m_distance - m_offset;
}

int LidarHandler::getResetCount() {
   return m_resetCount;
}

double* LidarHandler::getDistances() {
   return m_storedDistances;
}

LidarHandler::~LidarHandler() {

}

