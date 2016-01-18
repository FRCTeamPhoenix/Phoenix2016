#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include <sstream>

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
      SmartDashboard::init();
   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {

      }
   }


   void Test(){

      SmartDashboard::PutString("DB/String 0", " ");
      m_driveTrainController.setCurrentState(DriveTrainController::DRIVETRAIN_TEST);

      while(IsTest() && IsEnabled()){
         std::ostringstream output;
         output << "Throttle: ";
         output << (-m_DriveStation.getJoystickThrottle() + 1) / 2;
         SmartDashboard::PutString("DB/String 0", output.str());
         m_driveTrainController.run();
      }

      m_driveTrainController.setCurrentState(DriveTrainController::DRIVETRAIN_NORMAL);
      SmartDashboard::PutString("DB/String 0", " ");

   }
};

START_ROBOT_CLASS(Robot);
