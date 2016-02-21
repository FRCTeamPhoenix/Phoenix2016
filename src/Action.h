#pragma once

class Action
{
 public:
   Action(void);
   virtual ~Action(void);

   virtual void init(void) = 0;
   virtual bool execute(void) = 0;
   bool isInitialized(void) const;
 protected:
   bool m_initialized;
};
