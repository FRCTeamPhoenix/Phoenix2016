// This class allows for integration of the target aiming process into the Action
// system. Aiming at the target is defined here as its own action.


#include "ActionTargetAim.h"
#include "Aiming.h"

ActionTargetAim::ActionTargetAim(Aiming* aim)
   : Action(), m_aimer(aim)
{
}

// Start the centering process
void ActionTargetAim::init(void)
{
   m_aimer->setCurrentState(Aiming::CENTERING);
   m_initialized = true;
}

// Remove Aiming action from the queue if centering is no longer taking place
bool ActionTargetAim::execute(void)
{
   m_aimer->getNewImageData();
   m_aimer->centering();
   // Continue aiming process if still in centering phase
   if (m_aimer->getCurrentState() == Aiming::CENTERING) {
      return false;
   }
   else {
      // Stop the aiming process once centering is done
      m_aimer->setCurrentState(Aiming::IDLE);
      return true;
   }
}
