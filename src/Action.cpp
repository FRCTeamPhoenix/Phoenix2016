

#include "Action.h"

Action::Action(ActionType act)
{
  action = act;
}

void Action::operator()()
{
  switch (action) // TODO: Add more implementations for actions.
    {
    case NO_ACTION:
      break;
    }
}
