/*
 * RobotController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Will
 */

#ifndef SRC_ROBOTCONTROLLER_H_
#define SRC_ROBOTCONTROLLER_H_

#include "BaseController.h"

class RobotController : public BaseController{
public:
   enum STATE{
      AUTO,
      MANUAL
   };
   RobotController();
   void run();
   virtual ~RobotController();
};

#endif /* SRC_ROBOTCONTROLLER_H_ */
