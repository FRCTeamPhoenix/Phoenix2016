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
   std::string keyName = m_DriveStation->getStringInput(10);

   int pos = -1;
   for(int i=0;i<ConfigVariables::numberOfVars;i++) {
      if(keyName == ConfigVariables::variables[i]) {
         pos = i;
         break;
      }
   }

   if(pos == -1) {
      std::cout << "Key entered was not a valid variables" << std::endl;
      return;
   }

   std::string type = ConfigVariables::types[pos];

   if(type == "int") {
      std::stringstream ss;
      ss << Preferences::GetInstance()->GetInt(keyName, 0);
      m_DriveStation->setString(11, ss.str());
   } else if(type == "float") {
      std::stringstream ss;
      ss << Preferences::GetInstance()->GetFloat(keyName, 0);
      m_DriveStation->setString(11, ss.str());
   } else if(type == "double") {
      std::stringstream ss;
      ss << Preferences::GetInstance()->GetDouble(keyName, 0);
      m_DriveStation->setString(11, ss.str());
   } else {
      m_DriveStation->setString(11, Preferences::GetInstance()->GetString(keyName, 0));
   }
}

int ConfigEditor::getInt(std::string key) {
   return Preferences::GetInstance()->GetInt(key,0);
}

float ConfigEditor::getFloat(std::string key) {
   return Preferences::GetInstance()->GetFloat(key,0.0f);
}

double ConfigEditor::getDouble(std::string key) {
   return Preferences::GetInstance()->GetDouble(key,0.0);
}

std::string ConfigEditor::getString(std::string key) {
   return Preferences::GetInstance()->GetString(key,"");
}

void ConfigEditor::saveConfig() {
   std::string keyName = m_DriveStation->getStringInput(10);
   std::string newValue = m_DriveStation->getStringInput(12);

   int pos = -1;
   for(int i=0;i<ConfigVariables::numberOfVars;i++) {
      if(keyName == ConfigVariables::variables[i]) {
         pos = i;
         break;
      }
   }

   if(pos == -1) {
      std::cout << "Key entered was not a valid variable" << std::endl;
      return;
   }

   std::string type = ConfigVariables::types[pos];

   if(! isType(newValue,type))
      return;

   if(type == "int") {
      Preferences::GetInstance()->PutInt(keyName, std::stoi(newValue));
   } else if(type == "float") {
      Preferences::GetInstance()->PutFloat(keyName, std::stof(newValue));
   } else if(type == "double") {
      Preferences::GetInstance()->PutDouble(keyName, std::stod(newValue));
   } else {
      Preferences::GetInstance()->PutString(keyName, newValue);
   }
}

bool ConfigEditor::isType(std::string str, std::string type){
   if(type == "int"){
      try{
         std::stoi(str);
      }
      catch(std::invalid_argument& e){
         return false;
      }
   }
   else if(type == "float"){
         try{
            std::stof(str);
         }
         catch(std::invalid_argument& e){
            return false;
         }
      }

   else if(type == "double"){
         try{
            std::stod(str);
         }
         catch(std::invalid_argument& e){
            return false;
         }
      }
return true;
}

void ConfigEditor::showAllKeys(){
   std::string final = "";
   for(int i=0; i<ConfigVariables::numberOfVars; i++){
      final+=ConfigVariables::variables[i]+"     "+ConfigVariables::types[i]+"\n";
   }
   std::cout<<final<<std::endl;
   SmartDashboard::PutString("Keys",final);
}

void ConfigEditor::update() {
   for (int i = 0; i < 6; i++) {
      if (m_DriveStation->getButtonInput(i)) {
         m_DriveStation->setButton(i, false);
         std::cout << "Button was pressed" << std::endl;

         if(i==5) {
            std::cout << "reached stage one" << std::endl;
            saveConfig();
            std::cout << "reached stage two with " << Preferences::GetInstance()->GetInt("teamNumber",481516) << std::endl;
         }
         if(i==4) {
            getConfig();
         }
      }
   }

}

void ConfigEditor::putProgDouble(std::string key, double value) {
   if(!key.find("prog")==0) {
      Preferences::GetInstance()->PutDouble(key, value);
   }
}
