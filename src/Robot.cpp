#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "LoaderController.h"
#include "ShooterController.h"
#include "Flywheel.h"
#include "Client.h"
#include "Aiming.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Robot;

void runClient(Robot* robot, Client* client);

class Robot: public SampleRobot
{
   Talon m_flywheelLeftMotor;
   Talon m_flywheelRightMotor;
   Flywheel m_flywheel;
   Joystick m_joystick;
   Joystick m_gamepad;
   Encoder m_leftWheelEncoder;
   Encoder m_rightWheelEncoder;
   DriveStation m_driveStation;
   RobotDrive m_driveTrain;
   DriveTrainController m_driveTrainController;
   Talon m_armMotorLeft;
   Talon m_armMotorRight;
   Talon m_intakeMotor;
   Talon m_stationaryMotor;
   DigitalInput m_upperLimit;
   DigitalInput m_lowerLimit;
   DigitalInput m_loadedSensor;
   Encoder m_armEncoder;
   LoaderController m_loaderController;
   ShooterController m_shooterController;
   RobotController m_robotController;
   Client m_client;
   Aiming m_aiming;
   
public:
   Robot() :
       m_flywheelLeftMotor(PortAssign::flywheelLeftMotor),
      m_flywheelRightMotor(PortAssign::flywheelRightMotor),
      m_flywheel(&m_flywheelLeftMotor, &m_flywheelRightMotor),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_leftWheelEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
      m_rightWheelEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
      m_driveStation(&m_joystick, &m_gamepad),
      m_driveTrain(PortAssign::frontLeftWheelMotor,
            PortAssign::rearLeftWheelMotor,
            PortAssign::frontRightWheelMotor,
            PortAssign::rearRightWheelMotor),
      m_driveTrainController(&m_driveTrain, &m_driveStation, &m_leftWheelEncoder, &m_rightWheelEncoder),
      m_armMotorLeft(PortAssign::armMotorLeft),
      m_armMotorRight(PortAssign::armMotorRight),
      m_intakeMotor(PortAssign::intakeMotor),
      m_stationaryMotor(PortAssign::stationaryMotor),
      m_upperLimit(PortAssign::upperLimit),
      m_lowerLimit(PortAssign::lowerLimit),
      m_loadedSensor(PortAssign::loadedSensor),
      m_armEncoder(PortAssign::armEncoderChannelA, PortAssign::armEncoderChannelB),
      m_loaderController(&m_armMotorLeft, &m_armMotorRight, &m_intakeMotor, &m_stationaryMotor, &m_upperLimit, &m_lowerLimit, &m_loadedSensor, &m_armEncoder),
      m_shooterController(&m_loaderController, &m_flywheel),
      m_robotController(&m_driveStation, &m_driveTrainController,&m_shooterController, &m_loaderController),
      m_client(),
      m_aiming(&m_client, &m_driveTrainController)

   {
      SmartDashboard::init();

      cout<<"run init socket function" << endl;
       m_client.initilizeSocket();
       if (m_client.m_initGood){
          cout<<"init good start thread" << endl;
          std::thread receiveThread(runClient, this, &m_client);
          receiveThread.detach();
       }
   }

   void OperatorControl(){
      while(IsOperatorControl() && IsEnabled()){
         m_driveStation.snapShot();
         m_robotController.run();
         m_driveTrainController.run();
         m_shooterController.run();
         m_loaderController.run();
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
