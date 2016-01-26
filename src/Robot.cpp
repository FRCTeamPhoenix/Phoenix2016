#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "AutoController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include <sstream>
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
   Encoder m_leftWheelEncoder;
   Encoder m_rightWheelEncoder;
   DriveStation m_driveStation;
   RobotDrive m_driveTrain;
   DriveTrainController m_driveTrainController;
   AutoController m_autoController;
   RobotController m_robotController;
   Client client;

public:
   Robot() :
      m_flywheels(PortAssign::flywheels),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_leftWheelEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
      m_rightWheelEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
      m_driveStation(&m_joystick, &m_gamepad),
      m_driveTrain(PortAssign::frontLeftWheelMotor, PortAssign::rearLeftWheelMotor, PortAssign::frontRightWheelMotor, PortAssign::rearRightWheelMotor),
      m_driveTrainController(&m_driveTrain, &m_driveStation, &m_leftWheelEncoder, &m_rightWheelEncoder),
      m_autoController(&m_driveStation,&m_driveTrainController),
      m_robotController(&m_driveStation, &m_autoController)
{
      SmartDashboard::init();
      // cout << "call init socket" << endl;
      // client.initilizeSocket();
      // if (client.m_initGood){
      //         std::thread receiveThread(runClient, this, &client);
      // }
}


   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {
         m_driveStation.snapShot();
         m_robotController.run();
      }
   }

   void Test(){
      SmartDashboard::PutString("DB/String 0", " ");
      m_leftWheelEncoder.Reset();
      m_rightWheelEncoder.Reset();

      while(IsTest() && IsEnabled()){
         std::ostringstream outputR;
         outputR << "EncoderR: ";
         outputR << (m_rightWheelEncoder.Get());
         SmartDashboard::PutString("DB/String 0", outputR.str());
         std::ostringstream outputL;
         outputL << "EncoderL: ";
         outputL << (m_leftWheelEncoder.Get());
         SmartDashboard::PutString("DB/String 1", outputL.str());
      }
   }

};

void runClient(Robot* robot,Client* client)
{
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
