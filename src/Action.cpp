/*
 * Action API.
 *
 * The ActionType enum inside Action.h is the list
 * of all possible actions. The "operator()" function
 * is an overload of the function-call operator, so
 * you can treat an action as a function. The overloading
 * was purely aesthetic.
 * 
 * The handling of the actions is put in the "operator()"
 * function, where there is a switch case for every action.
 * You can add action handling here. If the action is done,
 * then you return true. Otherwise, you return false. The
 * action queue will discard the current action as soon as
 * the action returns true.
 */

#include "Action.h"
#include "DriveStation.h"
#include "DriveTrainController.h"

#include <Timer.h>

Action::Action(DriveStation* ds, DriveTrainController* dt, ActionType act, float pow, float seconds, float turn)
   : controllers(ds), drive_t(dt), action(act), power(pow), time(seconds), twist(turn)
{
   timer = new Timer();
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
	 firstTime = false;
	 timer->Start();
         drive_t->setCurrentState(DriveTrainController::AUTO);
	 drive_t->setDriveConstants(power, twist);
      }
   float currentTime = timer->Get();
   printf("%f\n", currentTime);
   if (currentTime >= time)
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
