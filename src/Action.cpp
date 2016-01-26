#include "Action.h"
#include "DriveStation.h"

Action::Action(DriveStation* ds, ActionType act)
{
   action = act;
   controllers = ds;
}

/*
 * Upon function call operator, perform action for one frame.
 * Returns true if action is done, false otherwise.
 */
bool Action::operator()()
{
   switch (action)
      {
      case ACTION_A:
         return waitUntil(2);
      case ACTION_B:
         return waitUntil(3);
      case ACTION_X:
         return waitUntil(1);
      case NO_ACTION:
         return true;
      }
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

ActionType Action::getAction()
{
   return action;
}
