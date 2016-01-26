#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "AutoController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include <thread>
#include "Client.h"
#include <Aiming.h>
#include <iostream>
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
   Client m_client;
   Aiming m_aiming;
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
      m_client(),
      m_aiming(&m_client, &m_driveTrainController)

   {
       /*cout<<"run init socket function" << endl;
       m_client.initilizeSocket();
       if (m_client.m_initGood){
          cout<<"init good start thread" << endl;
          std::thread receiveThread(runClient, this, &m_client);
       }*/

   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {
         m_aiming.run();
      }
   }

};

void runClient(Robot* robot,Client* client)
   {
      client->receivePacket();
   }

START_ROBOT_CLASS(Robot);