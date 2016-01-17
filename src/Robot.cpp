#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include <thread>
#include "Client.h"

class Robot;

void runClient(Robot* robot, Client* client);

class Robot: public SampleRobot
{
   Talon m_flywheels;
   Joystick m_joystick;
   Joystick m_gamepad;

   DriveStation m_DriveStation;
   RobotDrive m_driveTrain;
   RobotController m_robotController;

   DriveTrainController m_driveTrainController;
   Client client;
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
      std::thread receiveThread(runClient, this, &client);
      receiveThread.join();
   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {
         m_driveTrainController.run();
      }
   }

};

void runClient(Robot* robot,Client* client)
   {
      client->receivePacket();
   }

START_ROBOT_CLASS(Robot);
