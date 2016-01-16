/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include "DriveStation.h"
#include "constants.h"


using namespace std;

DriveStation::DriveStation(Joystick* joystick, Joystick* gamepad) :
   m_joystick(joystick),
   m_gamepad(gamepad)

{

}
float DriveStation::getJoystickY(){
   return m_joystick->GetY();
}
float DriveStation::getJoystickZ(){
   return m_joystick->GetZ();
}
float DriveStation::getJoystickThrottle(){
   return m_joystick->GetThrottle();
}
DriveStation::~DriveStation()
{
}

void DriveStation::printString(int outputSpot, string outputString) {


   //SmartDashboard::PutString()
}
