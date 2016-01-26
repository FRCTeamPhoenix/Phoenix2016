/*
 * RobotPreferences.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: ben
 */

#include <RobotPreferences.h>

RobotPreferences::RobotPreferences() {
   // TODO Auto-generated constructor stub

}

RobotPreferences::~RobotPreferences() {
   // TODO Auto-generated destructor stub
}

int RobotPreferences::getInt(std::string key) {
   return Preferences::GetInstance()->GetInt(key, 0);
}

float RobotPreferences::getFloat(std::string key) {
   return Preferences::GetInstance()->GetFloat(key, 0);
}

double RobotPreferences::getDouble(std::string key) {
   return Preferences::GetInstance()->GetDouble(key, 0);
}

std::string RobotPreferences::getString(std::string key) {
   return Preferences::GetInstance()->GetString(key, "");
}
