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

class RobotController;

class AutoController {
public:
  AutoController(RobotController* parent);
  ~AutoController();

  void run(void);
  void addAction(ActionType);
  void performAction(void);
private:
  std::vector<Action> m_queue;
  RobotController* m_parent;
  DriveStation* m_dstation;
};

#endif /* SRC_AUTOCONTROLLER_H_ */
