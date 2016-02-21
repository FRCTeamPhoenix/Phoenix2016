#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "LidarHandler.h"
#include <sstream>

class Robot;

void lidarThread(Robot * robot, LidarHandler * lidarHandler);

class Robot: public SampleRobot
{
   //Talon m_flywheels;
   Joystick m_joystick;
   Talon m_loader;
   Talon m_RFly;
   Talon m_LFly;
   Talon m_LLif;
   Talon m_RLif;
   Talon m_roller;

//   Talon RF;
//   Talon LF;
//   Talon RR;
//   Talon LR;

//   Talon m_leftPotMotor;
//   Talon m_rightPotMotor;


   AnalogInput m_LPot;
   AnalogInput m_RPot;

   DigitalInput m_ballSensor;

   Encoder m_LEncoder;
   Encoder m_REncoder;

   Encoder m_flyEncoder;

   Joystick m_gamepad;
   DriveStation m_DriveStation;
   RobotDrive m_driveTrain;
   RobotController m_robotController;


   DriveTrainController m_driveTrainController;

   Relay m_lidarOnSwitch;
   LidarHandler m_lidarHandler;

public:
   Robot() :
      //m_flywheels(PortAssign::flywheels),
      m_joystick(PortAssign::joystick),
      m_loader(4),
      m_RFly(5),
      m_LFly(6),
      m_LLif(7),
      m_RLif(8),
      m_roller(9),


//      RF(0),
//      LF(1),
//      RR(2),
//      LR(3),

//      m_leftPotMotor(7),
//      m_rightPotMotor(8),

      m_RPot(1),
      m_LPot(2),

      m_ballSensor(8),

      m_LEncoder(0, 1),
      m_REncoder(2, 3),

      m_flyEncoder(4, 5),

      m_gamepad(PortAssign::gamepad),
      m_DriveStation(&m_joystick, &m_gamepad),
      m_driveTrain(PortAssign::frontLeftWheelMotor,
            PortAssign::rearLeftWheelMotor,
            PortAssign::frontRightWheelMotor,
            PortAssign::rearRightWheelMotor),
      m_robotController(&m_DriveStation),


      m_driveTrainController(&m_driveTrain, &m_DriveStation),

      m_lidarOnSwitch(0),
      m_lidarHandler(&m_lidarOnSwitch, 0, 9)
   {
      SmartDashboard::init();
   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled()){

      }
   }


   void Test(){

      std::thread lidarRun(lidarThread, this, &m_lidarHandler);
      lidarRun.detach();

      while(IsTest() && IsEnabled()){
         std::ostringstream outputL;
         outputL << "Left Encoder: ";
         outputL << m_LEncoder.Get();
         SmartDashboard::PutString("DB/String 0", outputL.str());

         std::ostringstream outputR;
         outputR << "Right Encoder: ";
         outputR << m_REncoder.Get();
         SmartDashboard::PutString("DB/String 1", outputR.str());

         std::ostringstream outputE;
         outputE << "Fly Encoder: ";
         outputE << m_flyEncoder.Get();
         SmartDashboard::PutString("DB/String 2", outputE.str());

         std::ostringstream outputS;
         outputS << "Ball Sensor: ";
         if(m_ballSensor.Get()){
            outputS << "Not there";
         }
         else{
            outputS << "Is there";
         }
         SmartDashboard::PutString("DB/String 4", outputS.str());

         std::ostringstream outputLPot;
         outputLPot << "Left Pot: ";
         outputLPot << m_LPot.GetVoltage();
         SmartDashboard::PutString("DB/String 5", outputLPot.str());

         std::ostringstream outputRPot;
         outputRPot << "Right Pot: ";
         outputRPot << m_RPot.GetVoltage();
         SmartDashboard::PutString("DB/String 6", outputRPot.str());

         std::ostringstream Lidar;
         Lidar << "Lidar: ";
         Lidar << m_lidarHandler.getDistance();
         Lidar << " Resets: ";
         Lidar << m_lidarHandler.getResetCount();
         SmartDashboard::PutString("DB/String 7", Lidar.str());

//
//         if(m_joystick.GetRawButton(1)){
//            RF.Set(1);
//            LF.Set(1);
//            RR.Set(1);
//            LR.Set(1);
//            m_loader.Set(1);
//            m_RFly.Set(1);
//            m_LFly.Set(1);
//            m_LLif.Set(1);
//            m_RLif.Set(1);
//            m_roller.Set(1);
//
//         }
//
//         if(m_joystick.GetRawButton(2)){
//            RF.Set(-1);
//            LF.Set(-1);
//            RR.Set(-1);
//            LR.Set(-1);
//            m_loader.Set(-1);
//            m_RFly.Set(-1);
//            m_LFly.Set(-1);
//            m_LLif.Set(-1);
//            m_RLif.Set(-1);
//            m_roller.Set(-1);
//
//         }
//
//         if(m_joystick.GetRawButton(3)){
//            RF.Set(0);
//            LF.Set(0);
//            RR.Set(0);
//            LR.Set(0);
//            m_loader.Set(0);
//            m_RFly.Set(0);
//            m_LFly.Set(0);
//            m_LLif.Set(0);
//            m_RLif.Set(0);
//            m_roller.Set(0);
//
//         }





         if(m_joystick.GetRawButton(5)){
            m_LLif.Set(0.5);
            m_RLif.Set(0.5);
         }
         else if(m_joystick.GetRawButton((3))) {
            m_LLif.Set(-0.5);
            m_RLif.Set(-0.5);
         }
         else{
            m_LLif.Set(0.0);
            m_RLif.Set(0.0);
         }


         if(m_joystick.GetRawButton(1)){
            m_RFly.Set(1);
            m_LFly.Set(-1);
         }
         else{
            m_RFly.Set(0.0);
            m_LFly.Set(0.0);
         }


         if(m_joystick.GetRawButton(2)){
            m_loader.Set(-1);
         }
         else{
            m_loader.Set(0.0);
         }

         if(m_joystick.GetRawButton(4)){
            m_roller.Set(0.5);
         }
         else{
            m_roller.Set(0.0);
         }
//
         m_driveTrainController.run();

      }

   lidarRun.join();
   }
};


void lidarThread(Robot * robot, LidarHandler * lidarHandler) {
   while(robot->IsEnabled() && (robot->IsAutonomous() || robot->IsOperatorControl() || robot->IsTest())) {
      lidarHandler->run();
      Wait(0.1);
   }
}
START_ROBOT_CLASS(Robot);
