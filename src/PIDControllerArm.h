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

   void setTarget(float target);
   bool atTarget(float tolerance);
   void PIDWrite(float output);
   void adjustTarget(float increment);
   float getSetpoint();

   virtual ~PIDControllerArm();
};

#endif /* PIDCONTROLLERARM_H_ */
