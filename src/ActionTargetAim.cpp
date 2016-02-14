#include "ActionTargetAim.h"
#include "Aiming.h"

ActionTargetAim::ActionTargetAim(Aiming* aim)
   : Action(), m_aimer(aim)
{
}

void
ActionTargetAim::init(void)
{
   m_aimer->beginAiming();
   m_initialized = true;
}

bool
ActionTargetAim::execute(void)
{
   return m_aimer->getCurrentState() == Aiming::IDLE;
}
