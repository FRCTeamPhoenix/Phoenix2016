/*
 * Tachometer.h
 *
 *  Created on: Jan 17, 2016
 *      Author: Ian
 */

#ifndef SRC_TACHOMETER_H_
#define SRC_TACHOMETER_H_

#include "AnalogInput.h"
#include "Timer.h"
#include "constants.h"

class Tachometer {
public:
   Tachometer(AnalogInput * analogInput);
   virtual ~Tachometer();

   void update();
   float getDistance();
   void reset();

private:
   AnalogInput * m_analogInput;
   Timer * m_timer;
   float m_distance;
   float m_lastTime;
};

#endif /* SRC_TACHOMETER_H_ */
