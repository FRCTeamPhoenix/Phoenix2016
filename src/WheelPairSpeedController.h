/*
 * WheelPairSpeedController.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Will
 */

#ifndef SRC_WHEELPAIRSPEEDCONTROLLER_H_
#define SRC_WHEELPAIRSPEEDCONTROLLER_H_

#include "WPILib.h"

class WheelPairSpeedController : PIDOutput{

   Talon* m_controlledWheelAlpha;
   Talon* m_controlledWheelBeta;
   Encoder* m_encoder;
   PIDController* m_controller;

public:
   WheelPairSpeedController(Talon* alphaWheel, Talon* betaWheel, Encoder* encoder, float pTerm, float iTerm, float dTerm);

   void setRate(float rate);
   bool atTarget(float tolerance);
   void PIDWrite(float output);

   virtual ~WheelPairSpeedController();
};

#endif /* SRC_WHEELPAIRSPEEDCONTROLLER_H_ */
