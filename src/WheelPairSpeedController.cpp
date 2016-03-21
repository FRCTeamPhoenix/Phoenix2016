/*
 * WheelPairSpeedController.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: Will
 */

#include <WheelPairSpeedController.h>

WheelPairSpeedController::WheelPairSpeedController(Talon* alphaWheel, Talon* betaWheel, Encoder* encoder, float pTerm, float iTerm, float dTerm):
   m_controlledWheelAlpha(alphaWheel),
   m_controlledWheelBeta(betaWheel),
   m_encoder(encoder)

{
   m_encoder->SetPIDSourceType(PIDSourceType::kRate);
   m_controller = new PIDController(pTerm, iTerm, dTerm, m_encoder, this);
   m_controller->SetTolerance(0.5);
   m_controller->SetPIDSourceType(PIDSourceType::kRate);
   m_controller->Enable();
}

void WheelPairSpeedController::setRate(float rate){
   m_controller->SetSetpoint(rate);
}

bool WheelPairSpeedController::atTarget(float tolerance){
   double setPoint = m_controller->GetSetpoint();
   double rate = m_encoder->GetRate();
   return (rate > (setPoint - setPoint*tolerance)) && (rate < (setPoint + setPoint*tolerance));
}

void WheelPairSpeedController::PIDWrite(float output){
   printf("Setpoint: %5.5f CurrentRate: %5.5f\n", m_controller->GetSetpoint(), m_encoder->GetRate());

   m_controlledWheelAlpha->Set(output);
   m_controlledWheelBeta->Set(output);
}


WheelPairSpeedController::~WheelPairSpeedController() {
   // TODO Auto-generated destructor stub
}

