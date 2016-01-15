/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include <DriveStation.h>

DriveStation::DriveStation() :
   m_joystick(Port::joystick),
   m_gamepad(Port::gamepad)

{

}

DriveStation::~DriveStation()
{
}

