#include "ActionButtonWait.h"
#include "DriveStation.h"

ActionButtonWait::ActionButtonWait(DriveStation* ds, int button)
   : Action(), m_driveStation(ds), m_button(button)
{
}

void
ActionButtonWait::init(void)
{
   m_initialized = true;
}

bool
ActionButtonWait::execute(void)
{
   return m_driveStation->getGamepadButton(m_button);
}
