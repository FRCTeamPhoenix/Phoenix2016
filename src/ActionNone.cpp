/*
 * The template for any Action-derived class.
 * Do not forget to replace ActionNone with
 * whatever else you wanted.
 *
 * Please delete these comments in your code.
 */

#include "ActionNone.h"

/*
 * Always keep the Action() bit in;
 * it calls the base class's constructor,
 * which sets m_initialized to false.
 *
 * This avoids some repetition of code.
 */
ActionNone::ActionNone(void)
   : Action()
{
}

/*
 * You must have m_initialized = true
 * as the last statement in your init
 * function. Otherwise, this code will
 * be repeated every time through.
 */
void
ActionNone::init(void)
{
   m_initialized = true;
}

/*
 * This function is executed for every
 * frame. When you want the action to
 * be removed from the queue, return true.
 * Otherwise, you need to return false
 * so that it won't be removed.
 */
bool
ActionNone::execute(void)
{
   return true;
}
