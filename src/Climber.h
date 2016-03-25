/*
 * Climber.h
 *
 *  Created on: Mar 25, 2016
 *      Author: connortess
 */
#include "WPILib.h"
#include "constants.h"
#include "DriveStation.h"
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

class Climber{
public:
   Climber(Talon * motorLeft, Talon * motorRight,DriveStation* driveStation,DigitalInput * leftLimit,DigitalInput * rightLimit);
   void run();
private:
   Talon * m_motorLeft;
   Talon * m_motorRight;
   DriveStation * m_driveStation;
   DigitalInput * m_leftLimit;
   DigitalInput * m_rightLimit;

};



#endif /* SRC_CLIMBER_H_ */
