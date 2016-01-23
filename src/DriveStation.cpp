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
   SmartDashboard::init();
   snapShot();
}

float DriveStation::getJoystickY(){
   return m_joystickY;
}

float DriveStation::getJoystickZ(){
   return m_joystickZ;
}

float DriveStation::getJoystickThrottle(){
   return m_joystickThrottle;
}

float DriveStation::getYWithDeadzone() {
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

bool DriveStation::getGamepadButton(int buttonCode)
{
   return m_buttons[buttonCode];
}

bool DriveStation::getJoystickButton(int buttonCode)
{
   return m_joystick->GetRawButton(buttonCode);
}

std::string DriveStation::getStringInput(int inputCode) {
   return m_stringInputs[inputCode];
}

bool DriveStation::getButtonInput(int buttonCode) {
   return m_buttonInputs[buttonCode];
}

void DriveStation::setString(int stringNumber, std::string value) {
   std::stringstream ss;
   ss << stringNumber;
   SmartDashboard::PutString("DB/String " + ss.str(), value);

}

void DriveStation::setButton(int buttonNumber, bool value) {
   std::stringstream ss;
   ss << buttonNumber;
   SmartDashboard::PutBoolean("DB/Button " + ss.str(), value);

}

void DriveStation::snapShot(){
   for(int i=0; i<12; i++){
   m_buttons[i]=m_gamepad->GetRawButton(i+1);
   }

   for(int j=0; j<10; j++){
      std::stringstream ss;
      ss<<"DB/String ";
      ss<<j;
      std::string temp = ss.str();

      m_stringInputs[j]=SmartDashboard::GetString(temp,"");
   }


   for(int k=0;k<4;k++) {
      std::stringstream ss;
      ss<<"DB/Button ";
      ss<<k;
      std::string temp = ss.str();

      m_buttonInputs[k]=SmartDashboard::GetBoolean(temp,false);
   }
   m_joystickY = m_joystick->GetY();
   m_joystickZ = m_joystick->GetZ();
   m_joystickZ = m_joystick->GetThrottle();

}

DriveStation::~DriveStation()
{
}
