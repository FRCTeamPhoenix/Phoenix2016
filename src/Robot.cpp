#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include <sstream>

class Robot: public SampleRobot
{
   //Talon m_flywheels;
   Joystick m_joystick;
//   Talon m_testMotor1;
//   Talon m_testMotor2;
//   Talon m_testMotor3;
//   Talon m_testMotor4;
   Talon m_testMotor5;
   Talon m_testMotor6;
   Talon m_testMotor7;
   Talon m_leftPotMotor;
   Talon m_rightPotMotor;
//   Talon m_testMotor10;

   AnalogInput m_LPot;
   AnalogInput m_RPot;

   DigitalOutput m_pinTest;
   PWM m_PWMTest;

   Encoder m_LEncoder;
   Encoder m_REncoder;

   Joystick m_gamepad;
   DriveStation m_DriveStation;
   RobotDrive m_driveTrain;
   RobotController m_robotController;


   DriveTrainController m_driveTrainController;

public:
   Robot() :
      //m_flywheels(PortAssign::flywheels),
      m_joystick(PortAssign::joystick),
//      m_testMotor1(0),
//      m_testMotor2(1),
//      m_testMotor3(2),
//      m_testMotor4(3),
      m_testMotor5(4),
      m_testMotor6(5),
      m_testMotor7(6),
      m_leftPotMotor(7),
      m_rightPotMotor(8),
//      m_testMotor10(9),
      m_LPot(1),
      m_RPot(2),

      m_pinTest(9),
      m_PWMTest(9),

      m_LEncoder(0, 1),
      m_REncoder(2, 3),
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
      while(IsOperatorControl() && IsEnabled()){
         if(m_joystick.GetRawButton(1)){
            m_pinTest.Set(1);
         }
         else{
            m_pinTest.Set(0);
         }
         if(m_joystick.GetRawButton(2)){
            m_PWMTest.SetRaw(128);
         }
         else{
            m_PWMTest.SetRaw(240);
         }
      }
   }


   void Test(){

      while(IsTest() && IsEnabled()){
         std::ostringstream outputL;
         outputL << "Left Encoder: ";
         outputL << m_LEncoder.Get();
         SmartDashboard::PutString("DB/String 0", outputL.str());

         std::ostringstream outputR;
         outputR << "Right Encoder: ";
         outputR << m_REncoder.Get();
         SmartDashboard::PutString("DB/String 1", outputR.str());

         std::ostringstream outputLPot;
         outputLPot << "Left Pot: ";
         outputLPot << m_LPot.GetVoltage();
         SmartDashboard::PutString("DB/String 2", outputLPot.str());

         std::ostringstream outputRPot;
         outputRPot << "Right Pot: ";
         outputRPot << m_RPot.GetVoltage();
         SmartDashboard::PutString("DB/String 3", outputRPot.str());

         m_driveTrainController.run();

         if(m_joystick.GetRawButton(5)){
            m_leftPotMotor.Set(1.0f);
         }
         else if(m_joystick.GetRawButton(3)) {
            m_leftPotMotor.Set(-1.0f);
         }
         else{
            m_leftPotMotor.Set(0.0f);
         }

         if(m_joystick.GetRawButton(6)){
            m_rightPotMotor.Set(1.0f);
         }
         else if(m_joystick.GetRawButton(4)){
            m_rightPotMotor.Set(-1.0f);
         }
         else{
            m_rightPotMotor.Set(0.0f);
         }

      }



   }
};

START_ROBOT_CLASS(Robot);
