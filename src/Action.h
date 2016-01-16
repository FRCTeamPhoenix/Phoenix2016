#pragma once

enum ActionType { NO_ACTION }; // TODO: Add more types of actions.

class Action
{
public:
  Action(ActionType act);
  void operator()();
private:
  ActionType action;
};
