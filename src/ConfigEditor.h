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
private:
   DriveStation* m_DriveStation;
};

#endif /* SRC_CONFIGEDITOR_H_ */
