/*
 * Flywheel.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#include <Flywheel.h>

Flywheel::Flywheel(Talon* leftFlywheelMotor, Talon* rightFlywheelMotor) :
m_leftFlywheelMotor(leftFlywheelMotor),
m_rightFlywheelMotor(rightFlywheelMotor)
{

   // TODO Auto-generated constructor stub

}

Flywheel::~Flywheel() {
   // TODO Auto-generated destructor stub
}

bool Flywheel::getFlywheelMotorRunning(Talon * motor){
   float motorPower = motor->Get();
   return ((motorPower < -0.01f) || (motorPower > 0.01) );
}

Flywheel::STATE Flywheel::getCurrentState(){
   STATE currentGoal = getGoalState();
   float leftFlywheel = m_leftFlywheelMotor->Get();
   float rightFlywheel = m_rightFlywheelMotor->Get();
   switch(currentGoal){
   case OFF:
      if(!getFlywheelMotorRunning(m_leftFlywheelMotor) && !getFlywheelMotorRunning(m_rightFlywheelMotor)){
         return OFF;
      }
      else{
         return ON;
      }
      break;
   case ON:
      if(getFlywheelMotorRunning(m_leftFlywheelMotor) &&
         getFlywheelMotorRunning(m_rightFlywheelMotor)
         m_timer.HasPeriodPassed(3.0f)){
         m_timer.Start();
         return STARTING;
      }
      else (leftFlywheel !=0 && rightFlywheel !=0 && ){

        return ON;
     }

     break;
   default:
     break;
   }
}
