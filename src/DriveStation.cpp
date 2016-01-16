/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include "DriveStation.h"
#include "constants.h"

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
float DriveStation::getThrottle() {
   float throttle = - getJoystickY();
   if (fabs(throttle) < 0.05f) //This makes a deadzone
   {
      throttle = 0;
   }
   return throttle;
}
float DriveStation::getTwist(){
   float twist = getJoystickZ();
   if (fabs(twist) < 0.05f) //This also makes a deadzone
   {
      twist = 0;
   }
   return twist;
}
DriveStation::~DriveStation()
{
}

