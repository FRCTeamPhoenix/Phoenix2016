/*
 * Flywheel.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#include <Flywheel.h>

Flywheel::Flywheel(Talon* leftFlywheelMotor, Talon* rightFlywheelMotor) :
m_leftFlywheelMotor(leftFlywheelMotor),
m_rightFlywheelMotor(rightFlywheelMotor),
m_power(0),
m_running(false)
{

}

Flywheel::~Flywheel() {
}

void Flywheel::run(){
   if(m_running){
      m_leftFlywheelMotor->Set(-m_power);
      m_rightFlywheelMotor->Set(m_power);
   }
   else{
      m_leftFlywheelMotor->Set(0);
      m_rightFlywheelMotor->Set(0);
   }
}
Flywheel::STATE Flywheel::getCurrentState(){
   if(m_running){

      if(m_timer.HasPeriodPassed(3.0)){
         m_timer.Stop();
         return ON;
      }
      else{
         return STARTING;
      }
   }
   else{
      return OFF;
   }
}
void Flywheel::start(float power){
   m_power = power;
   if(m_running == false){
      m_timer.Reset();
      m_timer.Start();
   }
   m_running = true;
}
void Flywheel::stop(){
   m_power = 0;
   m_running = false;
}
