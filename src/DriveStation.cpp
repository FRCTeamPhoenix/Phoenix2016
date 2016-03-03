/*
 * DriveStation.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#include "DriveStation.h"
#include <sstream>

DriveStation::DriveStation(Joystick* joystick, Joystick* gamepad) :
m_joystick(joystick), m_gamepad(gamepad) {
   //can't do this in constructor because drive station hasn't been initialized yet.
   //a call is now in robot.cpp constructor.
   //snapShot();
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

float DriveStation::getGamepadJoystick(){
   return -m_gamepadJoystickY;
}

float DriveStation::deadzoneOfGamepadJoystick(){
   float power = -m_gamepadJoystickY;
   if (fabs(power) < 0.05f){
      return 0;
   }
   else{
      return power;
   }
}

float DriveStation::getYWithDeadzone() {
   float throttle = -getJoystickY();
   if (fabs(throttle) < 0.05f) //This makes a deadzone
   {
      throttle = 0;
   }
   return throttle;
}

float DriveStation::getZWithDeadzone() {
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

   for(int i=0; i<12; i++){
      m_buttons[i]=m_gamepad->GetRawButton(i+1);
   }

   for(int j=0; j<13; j++){
      m_stringInputs[j]=SmartDashboard::GetString(DriveStationConstants::textBoxNames[j],"");
   }


   for(int k=0;k<6;k++){
      m_buttonInputs[k]=SmartDashboard::GetBoolean(DriveStationConstants::dashButtonNames[k],false);
   }

   m_joystickY = m_joystick->GetY();
   m_joystickZ = m_joystick->GetZ();
   m_joystickThrottle = m_joystick->GetThrottle();
   m_gamepadJoystickY = m_gamepad->GetY();
}

void DriveStation::printToDashboard(unsigned long *pointToString, int space){
   std::ostringstream outputS;
   outputS << &pointToString;
   SmartDashboard::PutString("DB/String " + space, outputS.str());
}
std::string DriveStation::getStringInput(int inputCode) {
   return m_stringInputs[inputCode];
}

bool DriveStation::getButtonInput(int buttonCode) {
   return m_buttonInputs[buttonCode];
}

void DriveStation::setString(int stringNumber, std::string value) {
   SmartDashboard::PutString(DriveStationConstants::textBoxNames[stringNumber], value);

}

void DriveStation::setButton(int buttonNumber, bool value) {
   SmartDashboard::PutBoolean(DriveStationConstants::dashButtonNames[buttonNumber], value);

}

void DriveStation::clearDriveStation() {
   SmartDashboard::PutString("DB/String 0", " ");
   SmartDashboard::PutString("DB/String 1", " ");
   SmartDashboard::PutString("DB/String 2", " ");
   SmartDashboard::PutString("DB/String 3", " ");
   SmartDashboard::PutString("DB/String 4", " ");
   SmartDashboard::PutString("DB/String 5", " ");
   SmartDashboard::PutString("DB/String 6", " ");
   SmartDashboard::PutString("DB/String 7", " ");
   SmartDashboard::PutString("DB/String 8", " ");
   SmartDashboard::PutString("DB/String 9", " ");
}

DriveStation::~DriveStation() {
}
