#include "Action.h"
#include "DriveStation.h"
#include "DriveTrainController.h"

#include <ctime>

Action::Action(DriveStation* ds, DriveTrainController* dt, ActionType act, float pow, int ms, float turn)
   : controllers(ds), drive_t(dt), action(act), power(pow), time(ms), twist(turn)
{
   firstTime = true;
}

/*
 * Upon function call operator, perform action for one frame.
 * Returns true if action is done, false otherwise.
 */
bool Action::operator()(void)
{
   switch (action)
      {
      case ACTION_A:
         return waitUntil(2);
      case ACTION_B:
         return waitUntil(3);
      case ACTION_X:
         return waitUntil(1);
      case ACTION_DRIVE:
	 return drive();
      case ACTION_BRAKE:
	 drive_t->setCurrentState(DriveTrainController::IDLE);
	 return true;
      case NO_ACTION:
         return true;
      }
}

/*
 * Drives with specified power and time in milliseconds.
 */
bool Action::drive(void)
{
   if (firstTime)
      {
	 startTime = clock() * 1000 / CLOCKS_PER_SEC;
	 drive_t->setDriveConstants(power, twist);
	 firstTime = false;
      }
   if (clock() * 1000 / CLOCKS_PER_SEC - startTime >= time)
      return true;
   return false;
}

/*
 * Given DriveStation class that provides a gamepad input,
 * returns true upon the button corresponding to buttonCode
 * being pressed.
 */
bool Action::waitUntil(int buttonCode)
{
   return controllers->getGamepadButton(buttonCode);
}

/*
 * Simply gets the action type of this action.
 */
ActionType Action::getAction()
{
   return action;
}
