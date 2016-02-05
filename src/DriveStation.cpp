/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include "DriveStation.h"

DriveStation::DriveStation(Joystick* joystick, Joystick* gamepad) :
      m_joystick(joystick), m_gamepad(gamepad) {
   snapShot();
}

float DriveStation::getJoystickY() {
   return m_joystickY;
}

float DriveStation::getJoystickZ() {
   return m_joystickZ;
}

float DriveStation::getJoystickThrottle() {
   return m_joystickThrottle;
}

float DriveStation::getYWithDeadzone() {
   float throttle = -getJoystickY();
   if (fabs(throttle) < 0.05f) //This makes a deadzone
         {
      throttle = 0;
   }
   return throttle;
}

float DriveStation::getTwist() {
   float twist = getJoystickZ();
   if (fabs(twist) < 0.05f) //This also makes a deadzone
         {
      twist = 0;
   }
   return twist;
}

bool DriveStation::getGamepadButton(int buttonCode) {
   return m_buttons[buttonCode];
}

bool DriveStation::getJoystickButton(int buttonCode) {
   return m_joystick->GetRawButton(buttonCode);
}

void DriveStation::snapShot() {
   for (int i = 0; i < 12; i++) {
      m_buttons[i] = m_gamepad->GetRawButton(i + 1);
   }

   m_joystickY = m_joystick->GetY();
   m_joystickZ = m_joystick->GetZ();
   m_joystickZ = m_joystick->GetThrottle();

}

void printToDashboard(unsigned long *pointToString, int space){
   std::ostringstream outputS;
   outputS << *pointToString;
   SmartDashboard::PutString("DB/String " + space, outputS.str());
}

DriveStation::~DriveStation() {
}
