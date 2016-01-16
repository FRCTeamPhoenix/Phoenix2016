#pragma once

class Action
{
  enum ActionType { NO_ACTION }; // TODO: Add more types of actions.

  Action(ActionType act);
  void operator()();
 private:
  ActionType action;
}
