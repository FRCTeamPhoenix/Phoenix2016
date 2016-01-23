#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "AutoController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "ConfigEditor.h"
#include <thread>
#include "Client.h"
#include <iostream>
#include <fstream>
using namespace std;


class Robot;

void runClient(Robot* robot, Client* client);

class Robot: public SampleRobot
{
   Talon m_flywheels;
   Joystick m_joystick;
   Joystick m_gamepad;

   DriveStation m_driveStation;
   RobotDrive m_driveTrain;
   AutoController m_autoC;
   RobotController m_robotController;

   DriveTrainController m_driveTrainController;
   Client client;

   ConfigEditor m_ConfigEditor;
public:
   Robot() :
      m_flywheels(PortAssign::flywheels),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_driveStation(&m_joystick, &m_gamepad),
      m_driveTrain(PortAssign::frontLeftWheelMotor,
            PortAssign::rearLeftWheelMotor,
            PortAssign::frontRightWheelMotor,
            PortAssign::rearRightWheelMotor),
      m_autoC(&m_driveStation),
      m_robotController(&m_driveStation, &m_autoC),
      m_driveTrainController(&m_driveTrain, &m_driveStation),
      m_ConfigEditor(&m_driveStation)
   {
       cout << "call init socket" << endl;
       client.initilizeSocket();
       if (client.m_initGood){
          std::thread receiveThread(runClient, this, &client);
       }

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
         m_driveStation.snapShot();
         m_robotController.run();
      }
   }
   void Test(){
      std::cout<<"This is test mode"<<std::endl;
      while (IsTest() && IsEnabled()) {
         m_driveStation.snapShot();
         m_ConfigEditor.update();
      }
   }
};

void runClient(Robot* robot,Client* client)
   {
      client->receivePacket();
   }


START_ROBOT_CLASS(Robot);
