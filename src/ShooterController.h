/*
 * ShooterController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_SHOOTERCONTROLLER_H_
#define SRC_SHOOTERCONTROLLER_H_

#include "BaseController.h"

enum ShooterStates{
   FIRING
};

class ShooterController : public BaseController{
public:
   ShooterController();
	void run();
	virtual ShooterController();
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */
