/*
 * ConfigEditor.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: ben
 */

#include <ConfigEditor.h>

ConfigEditor::ConfigEditor(DriveStation* DriveStation):
m_DriveStation(DriveStation){
   // TODO Auto-generated constructor stub
}

ConfigEditor::~ConfigEditor() {
   // TODO Auto-generated destructor stub
}

void ConfigEditor::getConfig() {

}

void ConfigEditor::saveConfig() {
std::string keyName = m_DriveStation->getStringInput(10);
}

void ConfigEditor::update() {
   for (int i = 0; i < 6; i++) {
      if (m_DriveStation->getButtonInput(i)) {
         m_DriveStation->setButton(i, false);
         std::cout << "Button was pressed" << std::endl;

         if(i==5) {
            saveConfig();
         }
         if(i==4) {
            getConfig();
         }
      }
   }


}
