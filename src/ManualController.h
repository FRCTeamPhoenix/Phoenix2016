/*
 * ManualController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_MANUALCONTROLLER_H_
#define SRC_MANUALCONTROLLER_H_

#include "BaseController.h"

class ManualController : public BaseController{
public:
	enum STATE{
	   NO_STATES
	};
   ManualController();
	void run();
	virtual ~ManualController();
};

#endif /* SRC_MANUALCONTROLLER_H_ */
