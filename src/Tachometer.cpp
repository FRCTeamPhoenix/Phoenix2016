/*
 * Tachometer.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: Ian
 */

#include "Tachometer.h"

Tachometer::Tachometer(AnalogInput * analogInput) {
   m_analogInput = analogInput;
   m_lastTime = m_timer->Get();
}

float Tachometer::getDistance() {
   return m_distance;
}

void Tachometer::reset() {
   m_distance = 0;
}

void Tachometer::update() {
   float newTime = m_timer->Get();
   float deltat = newTime - m_lastTime;
   m_lastTime = newTime;

   m_distance += deltat * (m_analogInput->GetVoltage() * TachometerConstants::voltageToInchesPerSecond);
}

Tachometer::~Tachometer() {

}
