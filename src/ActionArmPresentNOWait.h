/*
 * ActionArmPresentNOWait.h
 *
 *  Created on: Mar 25, 2016
 *      Author: connortess
 */

#ifndef SRC_ACTIONARMPRESENTNOWAIT_H_
#define SRC_ACTIONARMPRESENTNOWAIT_H_


#include "Action.h"
#include "Arm.h"

class ActionArmPresentNOWait : public Action{
public:
   ActionArmPresentNOWait(Arm*, float);
   void init(void);
   bool execute(void);
   ~ActionArmPresentNOWait();
private:
   Arm* m_arm;
   float m_goal;
};

#endif /* SRC_ACTIONARMPRESENTNOWAIT_H_ */
