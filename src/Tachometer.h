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
   Tachometer(AnalogInput * analogInput); //the analog input going into here should be your tachometer
   virtual ~Tachometer();

   void update(); //add a distance increment to the total
   float getDistance(); //get the current total distance
   void reset(); //set the current total distance to zero

private:
   AnalogInput * m_analogInput;
   Timer * m_timer;
   float m_distance;
   float m_lastTime;
};

#endif /* SRC_TACHOMETER_H_ */
