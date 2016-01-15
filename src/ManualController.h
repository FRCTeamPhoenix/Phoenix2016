/*
 * ManualController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_MANUALCONTROLLER_H_
#define SRC_MANUALCONTROLLER_H_

class ManualController {
private:
	DriveTrainController * m_driveTrain;
	ShooterController * m_shooter;
	LoaderController * m_loader;
public:
	ManualController(DriveTrainController * driveTrain, ShooterController * shooter, LoaderController * loader);
	virtual ~ManualController();

	void run();
};

#endif /* SRC_MANUALCONTROLLER_H_ */
