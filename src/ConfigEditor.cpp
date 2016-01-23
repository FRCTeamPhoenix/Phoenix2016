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
   std::string key = m_DriveStation->getStringInput(0);
   std::string type = m_DriveStation->getStringInput(2);

   if(type == "int") {
      std::stringstream ss;
      ss << Preferences::GetInstance()->GetInt(key,0);
      m_DriveStation->setString(1, ss.str());
   }
   else if(type == "double") {
         std::stringstream ss;
         ss << Preferences::GetInstance()->GetDouble(key,0);
         m_DriveStation->setString(1, ss.str());
      }
   else if(type == "float") {
         std::stringstream ss;
         ss << Preferences::GetInstance()->GetFloat(key,0);
         m_DriveStation->setString(1, ss.str());
      }
   else if(type == "string") {
         std::string s = Preferences::GetInstance()->GetString(key,"");
         m_DriveStation->setString(1, s);
      }
}

void ConfigEditor::saveConfig() {
   std::string key = m_DriveStation->getStringInput(0);
   std::string value = m_DriveStation->getStringInput(1);
   std::string type = m_DriveStation->getStringInput(2);

   if(type == "int") {
      int intValue = std::stoi(value);
      (Preferences::GetInstance())->PutInt(key, intValue);
   } else if(type == "double") {
      int intValue = std::stod(value);
      (Preferences::GetInstance())->PutInt(key, intValue);
   } else if(type == "string") {
      (Preferences::GetInstance())->PutString(key, value);
   } else if(type == "float") {
      int intValue = std::stof(value);
      (Preferences::GetInstance())->PutFloat(key, intValue);
   }
}

void ConfigEditor::update() {
   for (int i = 0; i < 4; i++) {
      if (m_DriveStation->getButtonInput(i)) {
         m_DriveStation->setButton(i, false);
         std::cout << "Button was pressed" << std::endl;

         if(i==1) {
            saveConfig();
         }
         if(i==2) {
            getConfig();
         }
      }
   }


}
