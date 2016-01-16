/*
 * ManualController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_MANUALCONTROLLER_H_
#define SRC_MANUALCONTROLLER_H_

#include "BaseController.h"

enum ManualStates{
   NO_STATES
};

class ManualController : public BaseController{
public:
   ManualController();
	void run();
	virtual ~ManualController();
};

#endif /* SRC_MANUALCONTROLLER_H_ */
