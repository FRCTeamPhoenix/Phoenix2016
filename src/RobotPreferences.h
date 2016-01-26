/*
 * RobotPreferences.h
 *
 *  Created on: Jan 25, 2016
 *      Author: ben
 */

#ifndef SRC_ROBOTPREFERENCES_H_
#define SRC_ROBOTPREFERENCES_H_
#include "Preferences.h"

class RobotPreferences {
public:
   RobotPreferences();
   virtual ~RobotPreferences();

   int getInt (std::string key);
   float getFloat (std::string key);
   double getDouble (std::string key);
   std::string getString (std::string key);
};

#endif /* SRC_ROBOTPREFERENCES_H_ */
