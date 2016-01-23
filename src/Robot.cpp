#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "AutoController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
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
   DriveTrainController m_driveTrainController;
   AutoController m_autoController;
   RobotController m_robotController;
   Client client;
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
      m_driveTrainController(&m_driveTrain, &m_driveStation),
      m_autoController(&m_driveStation, &m_driveTrainController),
      m_robotController(&m_driveStation, &m_autoController)
   {
      // cout << "call init socket" << endl;
      // client.initilizeSocket();
      // if (client.m_initGood){
      // 	 std::thread receiveThread(runClient, this, &client);
      // }
   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
	 {
	    m_autoController.run();
	    m_driveTrainController.run();
	 }
   }

};

void runClient(Robot* robot,Client* client)
{
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
