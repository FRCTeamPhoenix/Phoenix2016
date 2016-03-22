/*
 * CameraSwap.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Ian
 */

#ifndef SRC_CAMERASWAP_H_
#define SRC_CAMERASWAP_H_

#include "WPILib.h"

class CameraSwap {
public:
   CameraSwap(Joystick * joystick, USBCamera * cam0, USBCamera * cam1);
   void update();
   virtual ~CameraSwap();
private:
   Joystick * m_joystick;
   USBCamera * m_cam0;
   USBCamera * m_cam1;
};

#endif /* SRC_CAMERASWAP_H_ */
