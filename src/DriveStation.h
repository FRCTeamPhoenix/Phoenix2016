/*
 * DriveStation.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#ifndef SRC_DRIVESTATION_H_
#define SRC_DRIVESTATION_H_
#include "WPILib.h"

class DriveStation {
public:
   DriveStation();
   virtual ~DriveStation();
private:
   Joystick m_joystick;
   Joystick m_gamepad;

};

#endif /* SRC_DRIVESTATION_H_ */
