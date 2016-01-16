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

class AutoController {
public:
  AutoController();

  ~AutoController();
private:
  std::vector<Action> queue;
};

#endif /* SRC_AUTOCONTROLLER_H_ */
