#pragma once

class Timer;

class DriveStation;
class DriveTrainController;

enum ActionType { NO_ACTION,
		  ACTION_A,
		  ACTION_B,
		  ACTION_X,
		  ACTION_DRIVE,
		  ACTION_TURN,
		  ACTION_BRAKE, };

class Action
{
 public:
   Action(void);
   void init(void) = 0;
   bool execute(void) = 0;
 protected:
   bool m_initialized;
};
