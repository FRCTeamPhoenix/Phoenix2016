#pragma once

class Timer;

class DriveStation;
class DriveTrainController;

enum ActionType { NO_ACTION,
		  ACTION_A,
		  ACTION_B,
		  ACTION_X,
		  ACTION_DRIVE,
		  ACTION_CLOCKWISE,
		  ACTION_COUNTERCLOCKWISE,
		  ACTION_BRAKE, };

class Action
{
 public:
   Action(DriveStation*, DriveTrainController*, ActionType, int, float*);
   bool execute(void);
   ActionType getAction(void);
 private:
   bool m_invalid;
   bool m_firstTime;
   DriveStation* m_controllers;
   DriveTrainController* m_driveTrain;
   ActionType m_action;
   int m_argc;
   float* m_argv;
   Timer* m_timer;

   bool waitUntil(int buttonCode);
};
