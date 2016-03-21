/*
 * DriveTrain.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: Will
 */

#include <DriveTrain.h>

DriveTrain::DriveTrain(Talon* FRM, Talon* FLM, Talon* RRM, Talon* RLM, Encoder* RE, Encoder* LE):
   m_rightSide(FRM, RRM, RE, 0.002, 0.0, 0.0),
   m_leftSide(FLM, RLM, LE, 0.002, 0.0, 0.0)

{
}

void DriveTrain::setRight(float rate){
   m_rightSide.setRate(rate);
}

void DriveTrain::setLeft(float rate){
   m_leftSide.setRate(rate);
}

void DriveTrain::set(float rightRate, float leftRate){
   std::ostringstream rates;
   rates << "Right: " << int(rightRate) << " Left: " << int(leftRate);
   SmartDashboard::PutString("DB/String 9", rates.str());
   setRight(rightRate);
   setLeft(leftRate);

}



DriveTrain::~DriveTrain() {
   // TODO Auto-generated destructor stub
}

