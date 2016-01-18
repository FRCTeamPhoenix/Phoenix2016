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

class DriveStation {
public:
   DriveStation(Joystick*, Joystick*);
   virtual ~DriveStation();

   float getJoystickY();
   float getJoystickZ();
   float getJoystickThrottle();
   float getThrottle();
   float getTwist();
   bool getGamepadButton(int);
   bool getJoystickButton(int);
   void getButtons();

private:
   Joystick * m_joystick;
   Joystick * m_gamepad;

   bool m_buttons[DriveStationConstants::gamepadButtons];
};


#endif /* SRC_DRIVESTATION_H_ */
