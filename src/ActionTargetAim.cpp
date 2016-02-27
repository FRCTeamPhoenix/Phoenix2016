#include "ActionTargetAim.h"
#include "Aiming.h"

ActionTargetAim::ActionTargetAim(Aiming* aim)
   : Action(), m_aimer(aim)
{
}

void
ActionTargetAim::init(void)
{
   m_aimer->centering();
   m_initialized = true;
}

bool
ActionTargetAim::execute(void)
{
   if (m_aimer->getCurrentState() == Aiming::CENTERING) {
      return false;
   }
   else {
      m_aimer->setCurrentState(Aiming::IDLE);
      return true;
   }
}
