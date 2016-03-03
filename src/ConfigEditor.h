/*
 * ConfigEditor.h
 *
 *  Created on: Jan 23, 2016
 *      Author: ben
 */

#ifndef SRC_CONFIGEDITOR_H_
#define SRC_CONFIGEDITOR_H_
#include "DriveStation.h"

class ConfigEditor {
public:
   ConfigEditor(DriveStation* DriveStation);
   virtual ~ConfigEditor();
   void update();

   void saveConfig();
   void getConfig();
   bool isType(std::string str, std::string type);
   void showAllKeys();

   int getInt(std::string key, int defaultValue = 0);
   float getFloat(std::string key, float defaultValue = 0.0f);
   double getDouble(std::string key, double defaultValue = 0.0);
   std::string getString(std::string key, std::string defaultValue = "");
private:
   DriveStation* m_DriveStation;
};

#endif /* SRC_CONFIGEDITOR_H_ */
