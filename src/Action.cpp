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
#include "LoaderSense.h"
#include "Aiming.h"

#include <Timer.h>

Action::Action(DriveStation* ds, DriveTrainController* dt, LoaderSense* lsense, Aiming* aimer, ActionType act, int argc, float* argv)
   : m_controllers(ds), m_driveTrain(dt), m_loaderSense(lsense), m_aimer(aimer), m_action(act), m_argc(argc), m_argv(argv)
{
   m_timer = new Timer();
   m_firstTime = true;
   m_invalid = false;

   /* Checks for correct number of arguments. In switch
      statement, omit actions that have no arguments. */
   int argn;
   switch (m_action)
      {
      case ACTION_DRIVE:
      case ACTION_TURN:
	 argn = 2;
	 break;
      default:
	 argn = 0;
	 break;
      }
   if (argn != argc)
      {
	 m_invalid = true;
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
	 if (m_firstTime)
	    m_driveTrain->moveRobotStraight(m_argv[0], m_argv[1]);
	 if (m_driveTrain->getCurrentState() == DriveTrainController::ENCODERDRIVE)
	    return true;
	 return false;
      case ACTION_TURN:
	 if (m_firstTime)
	    m_driveTrain->aimRobotClockwise(m_argv[0], m_argv[1]);
	 if (m_driveTrain->getCurrentState() == DriveTrainController::ENCODERDRIVE)
	    return true;
	 return false;
      case ACTION_BRAKE:
	 // TODO: Make robot brake.
	 return true;
      case ACTION_BALL_AIM:
	 if (m_firstTime)
	    m_loaderSense->beginAligning();
	 return m_loaderSense->getCurrentState() == LoaderSense::IDLE;
      case ACTION_TARGET_AIM:
	 if (m_firstTime)
	    m_aimer->beginAiming();
	 return m_aimer->getCurrentState() == Aiming::IDLE;
      case NO_ACTION:
         return true;
      }
   m_firstTime = false;
   return true;
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
