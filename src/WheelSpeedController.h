/*
 * WheelSpeedController.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Will
 */

#ifndef SRC_WHEELSPEEDCONTROLLER_H_
#define SRC_WHEELSPEEDCONTROLLER_H_

#include "WPILib.h"

class WheelSpeedController{

   Talon* m_controledWheel;
   Encoder* m_encoder;
   PIDController* m_controller;


public:
   WheelSpeedController(Talon*, Encoder*);

   void setRate(float rate);
   bool atTarget(float tolerance);

   virtual ~WheelSpeedController();
};

#endif /* SRC_WHEELSPEEDCONTROLLER_H_ */
