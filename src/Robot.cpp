#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "LoaderController.h"
#include "ShooterController.h"
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
   ShooterController m_shooter;
   LoaderController m_loader;
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
      m_shooter(&m_flywheels),
      m_robotController(&m_driveStation, &m_driveTrainController, &m_shooter, &m_loader)
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
	    m_robotController.run();
	    m_driveTrainController.run();
	 }
   }

};

void runClient(Robot* robot,Client* client)
{
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
