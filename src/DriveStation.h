/*
 * DriveStation.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#ifndef SRC_DRIVESTATION_H_
#define SRC_DRIVESTATION_H_
#include "WPILib.h"
#include "constants.h"
#include <string>

class DriveStation {
public:
   DriveStation();
   virtual ~DriveStation();

   void printString(int outputSpot, std::string outputString);

private:
   Joystick m_joystick;
   Joystick m_gamepad;

};

#endif /* SRC_DRIVESTATION_H_ */
