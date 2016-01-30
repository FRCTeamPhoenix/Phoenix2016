#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "LoaderController.h"
#include "ShooterController.h"
#include "Flywheel.h"
#include "Client.h"
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
   Talon m_verticalMotor;
   Talon m_intakeMotor;
   Talon m_stationaryMotor;
   DigitalInput m_upperLimit;
   DigitalInput m_lowerLimit;
   DigitalInput m_loadedSensor;
   Encoder m_armEncoder;
   LoaderController m_loaderController;
   ShooterController m_shooterController;
   RobotController m_robotController;
   Client client;

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
      m_driveTrain(PortAssign::frontLeftWheelMotor, PortAssign::rearLeftWheelMotor, PortAssign::frontRightWheelMotor, PortAssign::rearRightWheelMotor),
      m_driveTrainController(&m_driveTrain, &m_driveStation, &m_leftWheelEncoder, &m_rightWheelEncoder),
      m_verticalMotor(PortAssign::verticalMotor),
      m_intakeMotor(PortAssign::intakeMotor),
      m_stationaryMotor(PortAssign::stationaryMotor),
      m_upperLimit(PortAssign::upperLimit),
      m_lowerLimit(PortAssign::lowerLimit),
      m_loadedSensor(PortAssign::loadedSensor),
      m_armEncoder(PortAssign::armEncoderChannelA, PortAssign::armEncoderChannelB),
      m_loaderController(&m_verticalMotor, &m_intakeMotor, &m_stationaryMotor, &m_upperLimit, &m_lowerLimit, &m_loadedSensor, &m_armEncoder),
      m_shooterController(&m_loaderController, &m_flywheel),
      m_robotController(&m_driveStation, &m_driveTrainController,&m_shooterController, &m_loaderController){
      SmartDashboard::init();

      // cout << "call init socket" << endl;
      // client.initilizeSocket();
      // if (client.m_initGood){
      //         std::thread receiveThread(runClient, this, &client);
      // }
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

         m_driveTrainController.run();
         m_loaderController.run();
         m_shooterController.run();

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
            m_driveTrainController.aimRobotClockwise(90, 0.5);
            SmartDashboard::PutString("DB/String 6", "Aiming Robot Clockwise 90");

         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonB)){
            m_driveTrainController.aimRobotCounterclockwise(90, 0.5);
            SmartDashboard::PutString("DB/String 6", "Aiming Robot CounterClockwise 90");

         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonY)){
            m_driveTrainController.moveRobotStraight(45, 0.5);
            SmartDashboard::PutString("DB/String 6", "Moving Robot Straight");

         }
         //test drivetrain repeatability by running forwards and backward five times.
         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonX)){
            SmartDashboard::PutString("DB/String 6", "Repeatability Test Straight");
            bool changeDirection = true;
            int loop = 0;
            while(loop<=10){
               m_driveTrainController.run();
               if(m_driveTrainController.getCurrentState()== DriveTrainController::IDLE){
                  loop++;
                  if(changeDirection){
                     m_driveTrainController.moveRobotStraight(45, 0.5);
                     changeDirection = false;
                  }
                  else {
                     m_driveTrainController.moveRobotStraight(-45, 0.5);
                     changeDirection = true;
                  }
               }
            }
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonRB)){
            SmartDashboard::PutString("DB/String 6", "Repeatability Test Rotation");
            bool changeRotation = true;
            int loop = 0;
            while(loop<=10){
               m_driveTrainController.run();
               if(m_driveTrainController.getCurrentState()== DriveTrainController::IDLE){
                  loop++;
                  if(changeRotation){
                     m_driveTrainController.aimRobotClockwise(90, 0.5);
                     changeRotation = false;
                  }
                  else{
                     m_driveTrainController.aimRobotCounterclockwise(90, 0.5);
                     changeRotation = true;
                  }
               }
            }
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
            SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

            m_driveTrainController.stopRobot();
            m_loaderController.setIdle();
            m_shooterController.setOff();
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonLB)){
            SmartDashboard::PutString("DB/String 6", "Loader Test");

            m_loaderController.setLoaded();
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::triggerRT)){
            SmartDashboard::PutString("DB/String 6", "Shooter Test");

            if(m_shooterController.getCurrentState() == ShooterController::ARMED){
               m_shooterController.setShooting();
            }
            else{
               m_shooterController.setArmed();
            }
         }
      }

      std::ostringstream outputR;
      outputR << "EncoderR: ";
      outputR << (m_rightWheelEncoder.Get());
      SmartDashboard::PutString("DB/String 0", outputR.str());
      std::ostringstream outputL;
      outputL << "EncoderL: ";
      outputL << (m_leftWheelEncoder.Get());
      SmartDashboard::PutString("DB/String 1", outputL.str());
   }

};

void runClient(Robot* robot,Client* client)
{
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
