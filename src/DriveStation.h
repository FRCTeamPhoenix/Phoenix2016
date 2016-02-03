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
   float getYWithDeadzone();
   float getTwist();
   float GetAngle();
   bool getGamepadButton(int);
   bool getJoystickButton(int);

   void snapShot();
   void printToDashboard(unsigned long *pointToString, int space);
   void gyroTest();


private:
   Joystick * m_joystick;
   Joystick * m_gamepad;

   bool m_buttons[DriveStationConstants::gamepadButtons];
   float m_joystickY;
   float m_joystickZ;
   float m_joystickThrottle;
   float m_gyroAngle;
};


#endif /* SRC_DRIVESTATION_H_ */
