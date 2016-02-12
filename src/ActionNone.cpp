#include "ActionNone.h"

ActionNone::ActionNone(void)
   : Action()
{
}

void
ActionNone::init(void)
{
   m_initialized = true;
}

bool
ActionNone::execute(void)
{
   return true;
}
