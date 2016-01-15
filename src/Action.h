#pragma once

class Action
{
  enum ActionType { NO_ACTION };

  Action(ActionType act);
  void run();
 private:
  ActionType action;
}
