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
   float getZWithDeadzone();
   float GetAngle();
   float getGamepadJoystick();
   float getGamepadJoystickY();
   //Creates deadzone for the gamepad joystick
   float deadzoneOfGamepadJoystick();
   bool getGamepadButton(int);
   bool getJoystickButton(int);
   std::string getStringInput(int);
   bool getButtonInput(int);

   void setString(int, std::string);

   void setButton(int, bool);


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
   bool m_buttonInputs[6];
   std::string m_stringInputs[13];
};


#endif /* SRC_DRIVESTATION_H_ */
