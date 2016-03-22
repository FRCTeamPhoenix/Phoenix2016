/*
 * CameraSwap.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: Ian
 */

#include <CameraSwap.h>

CameraSwap::CameraSwap(Joystick * joystick, USBCamera * cam0, USBCamera * cam1) :
   m_joystick(joystick),
   m_cam0(cam0),
   m_cam1(cam1){

}

void CameraSwap::update() {
   Image * image = 0;
   USBCamera * cam = m_joystick->GetRawButton(2) ? m_cam1 : m_cam0;
   printf("phase 0");
   cam->GetImage(image);
   printf("phase 1");
   CameraServer::GetInstance()->SetImage(image);
   printf("phase 2");
}

CameraSwap::~CameraSwap() {
   // TODO Auto-generated destructor stub
}

