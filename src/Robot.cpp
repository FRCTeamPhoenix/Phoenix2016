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
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConfigEditor.h"
#include "LidarHandler.h"
using namespace std;

class Robot;

void runClient(Robot* robot, Client* client);
void lidarThread(LidarHandler * lidarHandler);


class Robot: public SampleRobot
{
   AnalogGyro m_gyro;
   ConfigEditor m_configEditor;
   Talon m_flywheelLeftMotor;
   Talon m_flywheelRightMotor;
   Flywheel m_flywheel;
   Joystick m_joystick;
   Joystick m_gamepad;
   Encoder m_leftWheelEncoder;
   Encoder m_rightWheelEncoder;
   DriveStation m_driveStation;
   RobotDrive m_driveTrain;
   Relay m_lidarOnSwitch;
   DigitalOutput m_lidarDIOSwitch;
   LidarHandler m_lidarHandler;
   DriveTrainController m_driveTrainController;
   Talon m_armMotorLeft;
   Talon m_armMotorRight;
   Talon m_intakeMotor;
   Talon m_stationaryMotor;
   DigitalInput m_upperLimit;
   DigitalInput m_lowerLimit;
   DigitalInput m_loadedSensor;
   Encoder m_armEncoder;
   AnalogPotentiometer m_potentiometer;
   LoaderController m_loaderController;
   ShooterController m_shooterController;
   RobotController m_robotController;
   USBCamera m_driveCamera;
   Client m_client;
   Aiming m_aiming;
   LoaderSense m_loaderSense;

public:
   Robot() :
      m_gyro(PortAssign::gyroscope),
      m_configEditor(&m_driveStation),
      m_flywheelLeftMotor(PortAssign::flywheelLeftMotor),
      m_flywheelRightMotor(PortAssign::flywheelRightMotor),
      m_flywheel(&m_flywheelLeftMotor, &m_flywheelRightMotor),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_leftWheelEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
      m_rightWheelEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
      m_driveStation(&m_joystick, &m_gamepad),
      m_driveTrain(PortAssign::frontLeftWheelMotor, PortAssign::rearLeftWheelMotor, PortAssign::frontRightWheelMotor, PortAssign::rearRightWheelMotor),
      m_lidarOnSwitch(0),
      m_lidarDIOSwitch(15),
      m_lidarHandler(&m_lidarOnSwitch, &m_configEditor, 9),
      m_driveTrainController(&m_driveTrain, &m_driveStation, &m_leftWheelEncoder, &m_rightWheelEncoder, &m_gyro, &m_configEditor, &m_lidarHandler),
      m_armMotorLeft(PortAssign::armMotorLeft),
      m_armMotorRight(PortAssign::armMotorRight),
      m_intakeMotor(PortAssign::intakeMotor),
      m_stationaryMotor(PortAssign::stationaryMotor),
      m_upperLimit(PortAssign::upperLimit),
      m_lowerLimit(PortAssign::lowerLimit),
      m_loadedSensor(PortAssign::loadedSensor),
      m_armEncoder(PortAssign::armEncoderChannelA, PortAssign::armEncoderChannelB),
      m_potentiometer(PortAssign::potentiometer),
      m_loaderController(&m_intakeMotor, &m_stationaryMotor, &m_loadedSensor, &m_driveStation, &m_configEditor),
      m_shooterController(&m_loaderController, &m_flywheel, &m_configEditor),
      m_robotController(&m_driveStation, &m_driveTrainController,&m_shooterController, &m_loaderController, &m_flywheel, &m_configEditor),
      m_driveCamera("cam0",false),
      m_aiming(&m_client, &m_driveTrainController, &m_driveStation),
      m_loaderSense(&m_client, &m_driveTrainController, &m_driveStation){

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

      std::thread lidarRun(lidarThread, &m_lidarHandler);
      lidarRun.detach();
   }
   void OperatorControl(){
      m_driveTrainController.setGoalState(DriveTrainController::TELEOP);
      while(IsOperatorControl() && IsEnabled()){
         m_driveStation.snapShot();
         m_robotController.run();
         m_driveTrainController.run();
         m_shooterController.run();
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
         /*if(SmartDashboard::GetBoolean("DB/Button 3",false)) {
            std::ostringstream slid;
            slid.str(std::string());
            slid << m_lidarHandler.getFastAverage();
            SmartDashboard::PutString("DB/String 0", "Fast: " + slid.str());
            slid.str(std::string());
            slid << m_lidarHandler.getSlowAverage();
            SmartDashboard::PutString("DB/String 1", "Slow: " + slid.str());
            continue;
         }*/

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
         m_configEditor.update();
//      }
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
   }
   }
};

void lidarThread(LidarHandler * lidarHandler) {
   while(true) {
   lidarHandler->run();
   Wait(0.1);
   }
}

void runClient(Robot* robot, Client* client){
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
