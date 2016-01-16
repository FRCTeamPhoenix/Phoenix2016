/*
 * DriveTrainController.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#include <DriveTrainController.h>

DriveTrainController::DriveTrainController() :

m_joystick(Port::joystick),
m_driveTrain(Port::frontLeftWheelMotor,
        Port::rearLeftWheelMotor,
        Port::frontRightWheelMotor,
        Port::rearRightWheelMotor)
{

}

DriveTrainController::~DriveTrainController() {

}

void DriveTrainController::run() {
if(getCurrentState()== STATE::DRIVETRAIN_NORMAL){
   float throttle = - m_joystick.GetY();
   if (fabs(throttle) < 0.05f) //This makes a deadzone
   {
       throttle = 0;
   }

   float twist = m_joystick.GetZ();
   if (fabs(twist) < 0.05f) //This also makes a deadzone
   {
      twist = 0;
   }
   float throttleRatio = 0.7f;// .8 is too high :(
   float twistRatio = 1 - throttleRatio;
   float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
   float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

   m_driveTrain.TankDrive(leftPower, rightPower);
}
}

DriveTrainController::STATE DriveTrainController::getCurrentState() {
   return STATE::DRIVETRAIN_NORMAL;
}
