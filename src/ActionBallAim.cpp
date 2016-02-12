#include "ActionBallAim.h"
#include "LoaderSense.h"

ActionBallAim::ActionBallAim(LoaderSense* ls)
  : Action(), m_loaderSense(ls)
{
}

void
ActionBallAim::init(void)
{
   m_loaderSense->beginAligning();
   m_initialized = true;
}

bool
ActionBallAim::execute(void)
{
   return m_loaderSense->getCurrentState() == LoaderSense::IDLE;
}
