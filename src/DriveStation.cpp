/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include "DriveStation.h"
#include "constants.h"

using namespace std;

DriveStation::DriveStation() :
   m_joystick(PortAssign::joystick),
   m_gamepad(PortAssign::gamepad)
{

}

DriveStation::~DriveStation()
{
}

void DriveStation::printString(int outputSpot, string outputString) {


   //SmartDashboard::PutString()
}