/*
 * ManualController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_MANUALCONTROLLER_H_
#define SRC_MANUALCONTROLLER_H_

#include "BaseController.h"
#include "DriveTrainController.h"
#include "ShooterController.h"
#include "LoaderController.h"

class ManualController : public BaseController{
public:
	enum STATE{
	   NO_STATES
	};
   ManualController(DriveTrainController * driveTrain, ShooterController * shooter, LoaderController * loader);
	void run();
	virtual ~ManualController();
private:
	DriveTrainController * m_driveTrain;
	ShooterController * m_shooter;
	LoaderController * m_loader;
};

#endif /* SRC_MANUALCONTROLLER_H_ */
