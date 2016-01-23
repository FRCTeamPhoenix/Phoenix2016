/*
 * AutoController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Rose
 */

#ifndef SRC_AUTOCONTROLLER_H_
#define SRC_AUTOCONTROLLER_H_

#include <vector>
#include "Action.h"
#include "DriveStation.h"
#include "DriveTrainController.h"

class RobotController;

class AutoController {
public:
  AutoController(DriveStation*, DriveTrainController*);
  ~AutoController();

  void run(void);
  void addAction(ActionType, float = 0.0f, int = 0, float = 0.0f);
  void performAction(void);
private:
  std::vector<Action*> m_queue;
  DriveStation* m_dstation;
  DriveTrainController* m_drivet;
};

#endif /* SRC_AUTOCONTROLLER_H_ */
