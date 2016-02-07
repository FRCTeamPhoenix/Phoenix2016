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
   //Creates deadzone for joystick in Y direction
   float getYWithDeadzone();
   //Creates deadzone for twisting the joystick
   float getTwist();
   float GetAngle();
   float getGamepadJoystick();
   float getGamepadJoystickY();
   //Creates deadzone for the gamepad joystick
   float deadzoneOfGamepadJoystick();
   bool getGamepadButton(int);
   bool getJoystickButton(int);

   //Sets member varibles for all inputs
   void snapShot();
   //For printing strings to the dashboard
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
   float m_gamepadJoystick;
   float m_gamepadJoystickY;
};


#endif /* SRC_DRIVESTATION_H_ */
