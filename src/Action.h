#pragma once

class DriveStation;
class DriveTrainController;

enum ActionType { NO_ACTION,
		  ACTION_A,
		  ACTION_B,
		  ACTION_X,
		  ACTION_DRIVE,
		  ACTION_BRAKE,
		  ACTION_STOP, };

class Action
{
public:
   Action(DriveStation*, DriveTrainController*, ActionType, float, int, float);
   bool operator()(void);
   ActionType getAction(void);
private:
   bool firstTime;
   DriveStation* controllers;
   DriveTrainController* drive_t;
   ActionType action;
   float power;
   float twist;
   int time;
   int startTime;

   bool drive(void);
   bool waitUntil(int buttonCode);
};
