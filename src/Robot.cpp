#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "LoaderController.h"
#include "ShooterController.h"
#include "Flywheel.h"
#include "LidarHandler.h"
#include "Client.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Robot;

void runClient(Robot* robot, Client* client);
void lidarThread(Robot * robot, LidarHandler * lidarHandler);

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
   Client client;
   Relay m_lidarOnSwitch;
   DigitalOutput m_lidarDIOSwitch;
   LidarHandler m_lidarHandler;

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
      m_lidarOnSwitch(0),
      m_lidarDIOSwitch(8),
      m_lidarHandler(&m_lidarOnSwitch, 0, 9){
      SmartDashboard::init();

//      m_driveTrain.SetInvertedMotor(RobotDrive::MotorType::kFrontLeftMotor, true);
//      m_driveTrain.SetInvertedMotor(RobotDrive::MotorType::kRearLeftMotor, true);

      // cout << "call init socket" << endl;
      // client.initilizeSocket();
      // if (client.m_initGood){
      //         std::thread receiveThread(runClient, this, &client);
      // }
   }


   void OperatorControl(){
      m_driveTrainController.setGoalState(DriveTrainController::TELEOP);
      while(IsOperatorControl() && IsEnabled()){
         m_driveStation.snapShot();
         m_robotController.run();
         m_driveTrainController.run();
         m_shooterController.run();
         m_loaderController.run();
      }
   }

   void Test(){
      std::thread lidarThreadInstance(lidarThread, this, &m_lidarHandler);
      lidarThreadInstance.detach();

      SmartDashboard::PutString("DB/String 0", "Entering Test ");
      m_leftWheelEncoder.Reset();
      m_rightWheelEncoder.Reset();
      SmartDashboard::PutString("DB/String 0", " ");
      SmartDashboard::PutString("DB/String 1", " ");
      SmartDashboard::PutString("DB/String 2", " ");
      SmartDashboard::PutString("DB/String 3", " ");
      SmartDashboard::PutString("DB/String 4", " ");
      SmartDashboard::PutString("DB/String 5", " ");
      SmartDashboard::PutString("DB/String 6", " ");
      SmartDashboard::PutString("DB/String 7", " ");
      SmartDashboard::PutString("DB/String 8", " ");
      SmartDashboard::PutString("DB/String 9", " ");

      while(IsTest() && IsEnabled()){

         m_driveStation.snapShot();
         m_driveTrainController.run();
         m_shooterController.run();
         m_loaderController.run();
         SmartDashboard::PutString("DB/String 6", "in");
         if(m_joystick.GetRawButton(1)) {
            m_lidarDIOSwitch.Set(0);
            SmartDashboard::PutString("DB/String 7", "on");
         } else {
            m_lidarDIOSwitch.Set(1);
            SmartDashboard::PutString("DB/String 7", "off");
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
            SmartDashboard::PutString("DB/String 6", ":) Aiming Robot Clockwise 90 Test");
            m_driveTrainController.aimRobotClockwise(90, 0.6);
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonB)){
            SmartDashboard::PutString("DB/String 6", ":) Aiming Robot CounterClockwise 90 Test");
            m_driveTrainController.aimRobotCounterclockwise(90, 0.6);
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonY)){
            SmartDashboard::PutString("DB/String 6", ":) Moving Robot Straight Test");
            m_driveTrainController.moveRobotStraight(45, 0.5);
         }
         //test drivetrain repeatability by running forwards and backward five times.
         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonX)){
            SmartDashboard::PutString("DB/String 6", "Repeatability Test Straight");
            bool changeDirection = true;
            int loop = 0;
            while(loop<=10){
               m_driveStation.snapShot();
               m_driveTrainController.run();
               if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
                  SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

                  m_driveTrainController.stopRobot();
                  m_shooterController.setOff();
                  loop = 111;
               }
               if(m_driveTrainController.getCurrentState()== DriveTrainController::IDLE){
                  loop++;
                  if(changeDirection){
                     m_driveTrainController.moveRobotStraight(20, 0.5);
                     changeDirection = false;
                  }
                  else {
                     m_driveTrainController.moveRobotStraight(-20, 0.5);
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
               m_driveStation.snapShot();
               m_driveTrainController.run();
               if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
                  SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

                  m_driveTrainController.stopRobot();
                  m_shooterController.setOff();
                  loop = 111;
               }
               if(m_driveTrainController.getCurrentState()== DriveTrainController::IDLE){
                  loop++;
                  if(changeRotation){
                     m_driveTrainController.aimRobotClockwise(90, 0.6);
                     changeRotation = false;
                  }
                  else{
                     m_driveTrainController.aimRobotCounterclockwise(90, 0.6);
                     changeRotation = true;
                  }
               }
            }
         }

         if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
            SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

            m_driveTrainController.stopRobot();
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

void lidarThread(Robot * robot, LidarHandler * lidarHandler) {
   while(robot->IsEnabled() && (robot->IsAutonomous() || robot->IsOperatorControl() || robot->IsTest())) {
      //TODO this might not happen all the time
      lidarHandler->run();
      std::stringstream ssaa;
      ssaa<<lidarHandler->getDistance();
      SmartDashboard::PutString("DB/String 3", "Distance: " + ssaa.str());
      Wait(0.1);
   }
}

void runClient(Robot* robot,Client* client)
{
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
