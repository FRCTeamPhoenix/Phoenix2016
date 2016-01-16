#pragma once

enum ActionType { NO_ACTION }; // TODO: Add more types of actions.

class Action
{
  Action(ActionType act);
  void operator()();
 private:
  ActionType action;
};
