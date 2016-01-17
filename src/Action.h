#pragma once

class DriveStation;

enum ActionType { NO_ACTION, ACTION_A, ACTION_B, ACTION_X };

class Action
{
public:
   Action(DriveStation* ds, ActionType act);
   bool operator()();
   bool waitUntil(int buttonCode);
   ActionType getAction(void);
private:
   ActionType action;
   DriveStation* controllers;
};
