/*
 * ShooterController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_SHOOTERCONTROLLER_H_
#define SRC_SHOOTERCONTROLLER_H_

#include "BaseController.h"

class ShooterController : public BaseController{
public:
   enum STATE{
      FIRING
   };
   ShooterController();
   void run();
   virtual ~ShooterController();
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */
