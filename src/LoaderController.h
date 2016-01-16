/*
 * LoaderController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_LOADERCONTROLLER_H_
#define SRC_LOADERCONTROLLER_H_

#include "BaseController.h"

class LoaderController : public BaseController{
public:
	enum STATE {
		LOADER_EMPTY,
		LOADER_LOADING,
		LOADER_LOADED
	};
   LoaderController();
	void run();
	virtual ~LoaderController();
};

#endif /* SRC_LOADERCONTROLLER_H_ */
