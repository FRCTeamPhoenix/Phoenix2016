/*
 * DriveTrain.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Will
 */

#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

#include "WheelPairSpeedController.h"

class DriveTrain {
   WheelPairSpeedController m_rightSide;
   WheelPairSpeedController m_leftSide;


public:
   DriveTrain(Talon* FRM, Talon* FLM, Talon* RRM, Talon* RLM, Encoder* RE, Encoder* LE);

   void setLeft(float rate);
   void setRight(float rate);
   void set(float rightRate, float leftRate);

   virtual ~DriveTrain();
};

#endif /* SRC_DRIVETRAIN_H_ */
