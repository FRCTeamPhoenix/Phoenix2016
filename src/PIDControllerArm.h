/*
 * PIDControllerArm.h
 *
 *  Created on: Mar 15, 2016
 *      Author: connortess
 */

#ifndef PIDCONTROLLERARM_H_
#define PIDCONTROLLERARM_H_

#include "WPILib.h"
#include "ConfigEditor.h"

class PIDControllerArm: PIDOutput {
   Talon* m_armMotor;
   AnalogInput* m_potentiometer;
   ConfigEditor* m_configEditor;
   PIDController* m_controller;
   float m_upperLimit;
   float m_lowerLimit;

public:
   PIDControllerArm(Talon* armMotor,
         AnalogInput* potentiometer,
         ConfigEditor* configEditor,
         float upperLimit,
         float lowerLimit);

   void setTarget(float targetPercent);
   bool atTarget(float tolerance);
   void PIDWrite(float output);
   void adjustTarget(float increment);
   float percentToVoltage(float goal);
   float voltageToPercent(float volts);
   float getSetpoint();

   void run();
   bool armIsDeccelerating();
   float accelerationProfile();


   float m_desiredSetPoint;
   float m_profileSetPoint;
   float m_currentVelocity;

   virtual ~PIDControllerArm();
};

#endif /* PIDCONTROLLERARM_H_ */
