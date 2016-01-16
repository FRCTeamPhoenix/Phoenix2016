/*
 * RobotController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#ifndef SRC_ROBOTCONTROLLER_H_
#define SRC_ROBOTCONTROLLER_H_

#include "BaseController.h"

enum RobotStates{
   AUTO,
   MANUAL
};

class RobotController : public BaseController{
public:
   RobotController();
   void run();
   virtual ~RobotController();
};

#endif /* SRC_ROBOTCONTROLLER_H_ */
