#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"

class Robot: public SampleRobot
{
   Talon m_flywheels;
   Joystick m_joystick;
   Joystick m_gamepad;

   DriveStation m_DriveStation;
   RobotDrive m_driveTrain;
   RobotController m_robotController;

   DriveTrainController m_driveTrainController;
public:
   Robot() :
      m_flywheels(PortAssign::flywheels),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_DriveStation(&m_joystick, &m_gamepad),
      m_driveTrain(PortAssign::frontLeftWheelMotor,
            PortAssign::rearLeftWheelMotor,
            PortAssign::frontRightWheelMotor,
            PortAssign::rearRightWheelMotor),
      m_robotController(&m_DriveStation),

      m_driveTrainController(&m_driveTrain, &m_DriveStation)
   {

   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {
       /*  float throttle = - m_joystick.GetY();
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

         m_driveTrain.TankDrive(leftPower, rightPower); */

         /*if(m_gamepad.GetRawButton(1))
         {
            m_flywheels.Set(1);
         }
         if(m_gamepad.GetRawButton(2))
         {
            m_flywheels.Set(0);
         }*/

         m_driveTrainController.run();
      }
   }

};

START_ROBOT_CLASS(Robot);
