/*
 * WheelSpeedController.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: Will
 */

#include "WheelSpeedController.h"

WheelSpeedController::WheelSpeedController(Talon* motor, Encoder* encoder):
        m_controledWheel(motor),
        m_encoder(encoder)
{
   m_encoder->SetPIDSourceType(PIDSourceType::kRate);
   m_controller = new PIDController(0.20, 0.00, 0.00, m_encoder, m_controledWheel);
   m_controller->SetTolerance(0.05);


}

void WheelSpeedController::setRate(float rate) {
   m_controller->SetSetpoint(rate);
}

bool WheelSpeedController::atTarget(float tolerance) {
   double setPoint = m_controller->GetSetpoint();
   double rate = m_encoder->GetRate();
   return (rate > (setPoint - setPoint*tolerance)) && (rate < (setPoint + setPoint*tolerance));
}


WheelSpeedController::~WheelSpeedController() {
   // TODO Auto-generated destructor stub
}

