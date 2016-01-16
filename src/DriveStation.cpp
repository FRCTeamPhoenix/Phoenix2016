/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include <DriveStation.h>
#include "constants.h"
DriveStation::DriveStation() :
   m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad)
{

}

DriveStation::~DriveStation()
{
}

