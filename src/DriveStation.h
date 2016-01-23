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
#include "string.h"
#include "sstream"

class DriveStation {
public:
   DriveStation(Joystick*, Joystick*);
   virtual ~DriveStation();

   float getJoystickY();
   float getJoystickZ();
   float getJoystickThrottle();
   float getYWithDeadzone();
   float getTwist();
   bool getGamepadButton(int);
   bool getJoystickButton(int);
   std::string getStringInput(int);
   bool getButtonInput(int);

   void setString(int, std::string);

   void setButton(int, bool);

   void snapShot();
private:
   Joystick * m_joystick;
   Joystick * m_gamepad;

   bool m_buttons[DriveStationConstants::gamepadButtons];
   std::string m_stringInputs[10];
   bool m_buttonInputs[4];
   float m_joystickY;
   float m_joystickZ;
   float m_joystickThrottle;
};


#endif /* SRC_DRIVESTATION_H_ */
