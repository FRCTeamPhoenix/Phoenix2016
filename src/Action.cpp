#include "Action.h"

/*
 * Default constructor.
 * In initializer list for derived classes, do the following:
 *
 * ActionNone::ActionNone(void)
 *    : Action()
 *
 * so that this default constructor is called.
 */
Action::Action(void)
{
   m_initialized = false;
}

/*
 * Added for safety reasons.
 * It is always good to have a destructor.
 */
Action::~Action(void)
{
}

bool
Action::isInitialized(void) const
{
   return m_initialized;
}
