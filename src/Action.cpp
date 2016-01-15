#include "Action.h"

Action(ActionType act)
{
  action = act;
}

void operator()()
{
  switch (action) // TODO: Add more implementations for actions.
    {
    case NO_ACTION:
      break;
    }
}
