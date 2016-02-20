#include "WPILib.h"
#include "constants.h"
#include "RobotController.h"
#include "DriveStation.h"
#include "DriveTrainController.h"
#include "LoaderController.h"
#include "ShooterController.h"
#include "Flywheel.h"
#include "LoaderSense.h"
#include "Client.h"
#include "Aiming.h"
#include "Arm.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConfigEditor.h"
#include "LidarHandler.h"
using namespace std;

class Robot;

void runClient(Robot* robot, Client* client);
void lidarThread(Robot * robot, LidarHandler * lidarHandler);


class Robot: public SampleRobot
{
   AnalogGyro m_gyro;
   AnalogInput m_leftPotentiometer;
   AnalogInput m_rightPotentiometer;
   DigitalOutput m_lidarDIOSwitch;
   DigitalInput m_loadedSensor;
   DigitalInput m_leftUpperLimitSwitch;
   DigitalInput m_rightUpperLimitSwitch;
   DigitalInput m_leftLowerLimitSwitch;
   DigitalInput m_rightLowerLimitSwitch;
   Encoder m_leftWheelEncoder;
   Encoder m_rightWheelEncoder;
   Joystick m_joystick;
   Joystick m_gamepad;
   Relay m_lidarOnSwitch;
   Talon m_flywheelLeftMotor;
   Talon m_flywheelRightMotor;
   Talon m_armMotorLeft;
   Talon m_armMotorRight;
   Talon m_intakeMotor;
   Talon m_stationaryMotor;
   Client m_client;
   DriveStation m_driveStation;
   LoaderSense m_loaderSense;
   Aiming m_aiming;
   LidarHandler m_lidarHandler;
   ConfigEditor m_configEditor;
   RobotDrive m_driveTrain;
   DriveTrainController m_driveTrainController;
   Flywheel m_flywheel;
   LoaderController m_loaderController;
   ShooterController m_shooterController;
   Arm m_arm;
   USBCamera m_driveCamera;
   RobotController m_robotController;

public:
   Robot() :

      m_gyro(PortAssign::gyroscope),
      m_leftPotentiometer(PortAssign::leftPotentiometer),
      m_rightPotentiometer(PortAssign::rightPotentiometer),
      m_lidarDIOSwitch(15),
      m_loadedSensor(PortAssign::loadedSensor),
      m_leftUpperLimitSwitch(PortAssign::leftUpperLimitSwitch),
      m_rightUpperLimitSwitch(PortAssign::rightUpperLimitSwitch),
      m_leftLowerLimitSwitch(PortAssign::leftLowerLimitSwitch),
      m_rightLowerLimitSwitch(PortAssign::rightLowerLimitSwitch),
      m_leftWheelEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
      m_rightWheelEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_lidarOnSwitch(0),
      m_flywheelLeftMotor(PortAssign::flywheelLeftMotor),
      m_flywheelRightMotor(PortAssign::flywheelRightMotor),
      m_armMotorLeft(PortAssign::armMotorLeft),
      m_armMotorRight(PortAssign::armMotorRight),
      m_intakeMotor(PortAssign::intakeMotor),
      m_stationaryMotor(PortAssign::stationaryMotor),
      m_driveStation(&m_joystick, &m_gamepad),
      m_loaderSense(&m_client, &m_driveTrainController, &m_driveStation),
      m_aiming(&m_client, &m_driveTrainController, &m_driveStation),
      m_lidarHandler(&m_lidarOnSwitch, 0, 9),
      m_configEditor(&m_driveStation),
      m_driveTrain(PortAssign::frontLeftWheelMotor, PortAssign::rearLeftWheelMotor, PortAssign::frontRightWheelMotor, PortAssign::rearRightWheelMotor),
      m_driveTrainController(&m_driveTrain, &m_driveStation, &m_leftWheelEncoder, &m_rightWheelEncoder, &m_gyro, &m_configEditor, &m_lidarHandler),
      m_flywheel(&m_flywheelLeftMotor, &m_flywheelRightMotor),
      m_loaderController(&m_intakeMotor, &m_stationaryMotor, &m_loadedSensor, &m_driveStation, &m_configEditor),
      m_shooterController(&m_loaderController, &m_flywheel, &m_configEditor),
      m_arm(&m_armMotorLeft, &m_armMotorRight, &m_leftPotentiometer,&m_rightPotentiometer,&m_leftUpperLimitSwitch,&m_rightUpperLimitSwitch,&m_leftLowerLimitSwitch,&m_rightLowerLimitSwitch, &m_configEditor),
      m_driveCamera("cam0",false),
      m_robotController(&m_driveStation, &m_driveTrainController,&m_shooterController, &m_loaderController, &m_flywheel, &m_configEditor, &m_arm){

      SmartDashboard::init();
      m_gyro.Calibrate();
      m_leftWheelEncoder.SetDistancePerPulse(RobotConstants::leftDistancePerPulse);
      m_rightWheelEncoder.SetDistancePerPulse(RobotConstants::rightDistancePerPulse);
      m_configEditor.showAllKeys();

      //      m_driveTrain.SetInvertedMotor(RobotDrive::MotorType::kFrontLeftMotor, true);
      //      m_driveTrain.SetInvertedMotor(RobotDrive::MotorType::kRearLeftMotor, true);

      // cout << "call init socket" << endl;
      // client.initilizeSocket();
      // if (client.m_initGood){
      //         std::thread receiveThread(runClient, this, &client);
      // }
   }
   void RobotInit() override{
      cout<<"run init socket function" << endl;
      //m_client.initilizeSocket();
      if (m_client.m_initGood){
         cout<<"init good start thread" << endl;
         std::thread receiveThread(runClient, this, &m_client);
         receiveThread.detach();
      }

      m_driveCamera.SetExposureManual(20);
      m_driveCamera.SetWhiteBalanceAuto();
      CameraServer::GetInstance()->SetQuality(50);
      CameraServer::GetInstance()->StartAutomaticCapture("cam0");

   }
   void OperatorControl(){
      SmartDashboard::PutString("DB/String 0", "Teleop ");
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

      m_driveTrainController.setGoalState(DriveTrainController::TELEOP);
      while(IsOperatorControl() && IsEnabled()){
         m_driveStation.snapShot();
         m_robotController.run();
         m_driveTrainController.run();
         m_shooterController.run();
         m_arm.run();
      }
   }

   void Test(){
      //Resets the encoders
      m_leftWheelEncoder.Reset();
      m_rightWheelEncoder.Reset();

      //Clears the Dashboard
      SmartDashboard::PutString("DB/String 0", "Entering Test ");
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
         std::ostringstream outputG;
         outputG << "Gyro: ";
         outputG << (m_gyro.GetAngle());
         SmartDashboard::PutString("DB/String 9", outputG.str());

         //Homes robot arm at the beginning of test
         //         m_loaderController.setHoming();
         //
         //         m_loaderController.run();
         //
         //         if (m_loaderController.homed()){
         m_driveStation.snapShot();
         m_driveTrainController.run();
         //            m_shooterController.run();
         //         }
         //Calls all run functions involved with testing

         //Outputs the encoder valuse of the left and right wheels
         std::ostringstream outputR;
         outputR << "EncoderR: ";
         outputR << (m_rightWheelEncoder.Get());
         SmartDashboard::PutString("DB/String 0", outputR.str());
         std::ostringstream outputL;
         outputL << "EncoderL: ";
         outputL << (m_leftWheelEncoder.Get());
         SmartDashboard::PutString("DB/String 1", outputL.str());

         //         //LoaderController
         //         std::ostringstream outputLoad;
         //         outputLoad << "Loader State: " << (m_loaderController.getGoalState());
         //         SmartDashboard::PutString("DB/String 2", outputLoad.str());

         //DriveTrainController
         std::ostringstream outputDriveTrainController;
         outputDriveTrainController << "DriveTrainController State: " << (m_driveTrainController.getCurrentState());
         SmartDashboard::PutString("DB/String 3", outputDriveTrainController.str());

         //         //ShooterController
         //         std::ostringstream outputShooter;
         //         outputShooter << "Shooter State: " << (m_shooterController.getGoalState());
         //         SmartDashboard::PutString("DB/String 4", outputShooter.str());

         //Aiming Robot Clockwise 90 degrees
         //         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
         //          SmartDashboard::PutString("DB/String 6", ":) Aiming Robot Clockwise 90 Test");
         //        m_driveTrainController.aimRobotClockwise(m_configEditor.getFloat("degree"), m_configEditor.getFloat("motorPower"));
      }
      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
         m_driveTrainController.driveLidar(36,0.5);
      }
      //Aiming Robot Counter Clockwise 90 degrees
      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonB)){
         SmartDashboard::PutString("DB/String 6", ":) Aiming Robot CounterClockwise 90 Test");
         m_driveTrainController.aimRobotCounterclockwise(m_configEditor.getFloat("degree"), m_configEditor.getFloat("motorPower"));
      }

      //Robot drives straight
      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonY)){
         SmartDashboard::PutString("DB/String 6", ":) Moving Robot Straight Test");
         m_driveTrainController.moveRobotStraight(45, m_configEditor.getFloat("motorPower"));
      }
      //test drivetrain repeatability by running forwards and backward five times.
      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonX)){
         SmartDashboard::PutString("DB/String 6", "Repeatability Test Straight");
         bool changeDirection = true;
         int loop = 0;
         while(loop<=10){
            m_driveStation.snapShot();
            m_driveTrainController.run();
            //Stops everything on the robot
            if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
               SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

               m_driveTrainController.stopRobot();
               m_shooterController.setOff();
               loop = 111;
            }
            //Switching between going forward and backward
            if(m_driveTrainController.getCurrentState()== DriveTrainController::IDLE){
               loop++;
               if(changeDirection){
                  m_driveTrainController.moveRobotStraight(m_configEditor.getFloat("distance"), m_configEditor.getFloat("motorPower"));
                  changeDirection = false;
               }
               else {
                  m_driveTrainController.moveRobotStraight(m_configEditor.getFloat("distance"), m_configEditor.getFloat("motorPower"));
                  changeDirection = true;
               }
            }
         }
      }

      //Tests drivetrain repeatablity test
      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonRB)){
         SmartDashboard::PutString("DB/String 6", "Repeatability Test Rotation");
         bool changeRotation = true;
         int loop = 0;
         while(loop<=10){
            m_driveStation.snapShot();
            m_driveTrainController.run();
            //Stops everything on the robot
            if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
               SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

               m_driveTrainController.stopRobot();
               m_shooterController.setOff();
               loop = 111;
            }
            //Switches the dirctions between
            if(m_driveTrainController.getCurrentState()== DriveTrainController::IDLE){
               loop++;
               if(changeRotation){
                  m_driveTrainController.aimRobotClockwise(m_configEditor.getFloat("degree"), m_configEditor.getFloat("motorPower"));
                  changeRotation = false;
               }
               else{
                  m_driveTrainController.aimRobotCounterclockwise(m_configEditor.getFloat("degree"), m_configEditor.getFloat("motorPower"));
                  changeRotation = true;
               }
            }
         }
      }

      //Stops everything on robot
      if(m_driveStation.getGamepadButton(DriveStationConstants::triggerLT)){
         SmartDashboard::PutString("DB/String 6", "STOP ROBOT!!");

         m_shooterController.setOff();
         //m_loaderController.stop();
         m_driveTrainController.stopRobot();
      }

      //Tests the loader by running the motors
      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonLB)){
         SmartDashboard::PutString("DB/String 6", "Loader Test");
         m_loaderController.start();
      }

      //Tests the shooter by running the flywheels
      if(m_driveStation.getGamepadButton(DriveStationConstants::triggerRT)){
         SmartDashboard::PutString("DB/String 6", "Shooter Test");

         if(m_shooterController.getCurrentState() == ShooterController::ARMED){
            m_shooterController.setShooting();
         }
         else{
            m_shooterController.setArmed();
         }
      }

      m_configEditor.update();
   }
};

void lidarThread(Robot * robot, LidarHandler * lidarHandler) {
   while(robot->IsEnabled() && (robot->IsAutonomous() || robot->IsOperatorControl() || robot->IsTest())) {
      std::ostringstream lidar;
      lidar << "Lidar Value: ";
      lidar << lidarHandler->getDistance();
      SmartDashboard::PutString("DB/String 0", lidar.str());

      lidarHandler->run();
      Wait(0.1);
   }
}

void runClient(Robot* robot, Client* client){
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
