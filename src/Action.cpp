/*
 * Action API.
 *
 * The ActionType enum inside Action.h is the list of all
 * possible actions. The execute method executes the action
 * that this current object contains.
 *
 * The handling of the actions is put in the execute method,
 * where there is a switch case for every action. You can
 * add action handling here. If the action is done, then you
 * return true. Otherwise, you return false. The action
 * queue will discard the current action as soon as the
 * action returns true.
 *
 * The constructor takes in an array of floats for arguments.
 * You will also pass in the length of the array for safety
 * reasons. If the number of arguments is incorrect, the
 * action will immediately prompt to be removed from the
 * queue and print a warning message.
 */

#include "Action.h"
#include "DriveStation.h"
#include "DriveTrainController.h"

#include <Timer.h>

Action::Action(DriveStation* ds, DriveTrainController* dt, ActionType act, int argc, float* argv)
   : m_controllers(ds), m_driveTrain(dt), m_action(act), m_argc(argc), m_argv(argv)
{
   m_timer = new Timer();
   m_firstTime = true;

   /* Checks for correct number of arguments. In switch
      statement, omit actions that have no arguments. */
   int argn;
   switch (m_action)
      {
      case ACTION_DRIVE:
	 argn = 3;
	 break;
      default:
	 argn = 0;
	 break;
      }
   if (argn != argc)
      {
	 m_invalid = false;
	 printf("Warning: invalid number of arguments "
		"for action. Expected %d arguments, "
		"but received %d.\n", argn, argc);
      }
}

/*
 * Upon function call operator, perform action for one frame.
 * Returns true if action is done, false otherwise.
 */
bool Action::execute(void)
{
   /* If action is invalid, immediately remove from queue. */
   if (m_invalid)
      return true;
   /* Performs action. */
   switch (m_action)
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
	 // TODO: Make robot brake.
	 return true;
      case NO_ACTION:
         return true;
      }
   return true;
}

/*
 * Drives with specified power and time in milliseconds.
 */
bool Action::drive(void)
{
   if (m_firstTime)
      {
	 m_firstTime = false;
	 m_timer->Start();
         //m_driveTrain->setCurrentState(DriveTrainController::AUTOTEST);
	 //m_driveTrain->setDriveConstants(power, twist);
      }
   float currentTime = m_timer->Get();
   printf("%f\n", currentTime);
   if (currentTime >= m_argv[1])
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
   return m_controllers->getGamepadButton(buttonCode);
}

/*
 * Simply gets the action type of this action.
 */
ActionType Action::getAction()
{
   return m_action;
}
