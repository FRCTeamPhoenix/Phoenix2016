#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"

class Robot: public SampleRobot
{
   Talon m_flywheels;

   DriveStation m_DriveStation;
   RobotDrive m_driveTrain;
   RobotController m_robotController;
public:
   Robot() :
      m_flywheels(Port::flywheels),

      m_driveTrain(Port::frontLeftWheelMotor,
            Port::rearLeftWheelMotor,
            Port::frontRightWheelMotor,
            Port::rearRightWheelMotor)
   {

   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {
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

         if(m_gamepad.GetRawButton(1))
         {
            m_flywheels.Set(1);
         }
         if(m_gamepad.GetRawButton(2))
         {
            m_flywheels.Set(0);
         }
      }
   }

};

START_ROBOT_CLASS(Robot);
