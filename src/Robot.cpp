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
   DigitalInput m_loadedSensor;
   DigitalInput m_leftUpperLimitSwitch;
   DigitalInput m_rightUpperLimitSwitch;
   DigitalInput m_leftLowerLimitSwitch;
   DigitalInput m_rightLowerLimitSwitch;
   Encoder m_leftWheelEncoder;
   Encoder m_rightWheelEncoder;
   Encoder m_leftFlywheelEncoder;
   Encoder m_rightFlywheelEncoder;
   Joystick m_joystick;
   Joystick m_gamepad;
   Talon m_leftFlywheelMotor;
   Talon m_rightFlywheelMotor;
   Talon m_armMotorLeft;
   Talon m_armMotorRight;
   Talon m_intakeMotor;
   Talon m_stationaryMotor;
   Client m_client;
   DriveStation m_driveStation;
   Relay m_lidarOnSwitch;
   ConfigEditor m_configEditor;
   LidarHandler m_lidarHandler;
   RobotDrive m_driveTrain;
   DriveTrainController m_driveTrainController;
   USBCamera m_driveCamera;
   LoaderSense m_loaderSense;
   Flywheel m_flywheel;
   LoaderController m_loaderController;
   ShooterController m_shooterController;
   Arm m_arm;
   Aiming m_aiming;
   RobotController m_robotController;

public:
   Robot() :
      m_gyro(PortAssign::gyroscope),
      m_leftPotentiometer(PortAssign::leftPotentiometer),
      m_rightPotentiometer(PortAssign::rightPotentiometer),
      m_loadedSensor(PortAssign::loadedSensor),
      m_leftUpperLimitSwitch(PortAssign::leftUpperLimitSwitch),
      m_rightUpperLimitSwitch(PortAssign::rightUpperLimitSwitch),
      m_leftLowerLimitSwitch(PortAssign::leftLowerLimitSwitch),
      m_rightLowerLimitSwitch(PortAssign::rightLowerLimitSwitch),
      m_leftWheelEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
      m_rightWheelEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
      m_leftFlywheelEncoder(PortAssign::leftFlywheelEncoderChannelA, PortAssign::leftFlywheelEncoderChannelB),
      m_rightFlywheelEncoder(PortAssign::rightFlywheelEncoderChannelA, PortAssign::rightFlywheelEncoderChannelB),
      m_joystick(PortAssign::joystick),
      m_gamepad(PortAssign::gamepad),
      m_leftFlywheelMotor(PortAssign::flywheelLeftMotor),
      m_rightFlywheelMotor(PortAssign::flywheelRightMotor),
      m_armMotorLeft(PortAssign::armMotorLeft),
      m_armMotorRight(PortAssign::armMotorRight),
      m_intakeMotor(PortAssign::intakeMotor),
      m_stationaryMotor(PortAssign::stationaryMotor),
      m_driveStation(&m_joystick, &m_gamepad),
      m_lidarOnSwitch(0),
      m_configEditor(&m_driveStation),
      m_lidarHandler(&m_lidarOnSwitch, &m_configEditor, 9),
      m_driveTrain(PortAssign::frontLeftWheelMotor, PortAssign::rearLeftWheelMotor, PortAssign::frontRightWheelMotor, PortAssign::rearRightWheelMotor),
      m_driveTrainController(&m_driveTrain, &m_driveStation, &m_leftWheelEncoder, &m_rightWheelEncoder, &m_gyro, &m_configEditor, &m_lidarHandler),
      m_driveCamera("cam0",false),//cam0 is nice camera cam1 is microsoft lifecam.
      m_loaderSense(&m_client, &m_driveTrainController, &m_driveStation),
      m_flywheel(&m_leftFlywheelMotor, &m_rightFlywheelMotor, &m_leftFlywheelEncoder, &m_rightFlywheelEncoder, &m_lidarHandler, &m_configEditor),
      m_loaderController(&m_intakeMotor, &m_stationaryMotor, &m_loadedSensor, &m_driveStation, &m_configEditor),
      m_shooterController(&m_loaderController, &m_flywheel, &m_configEditor),
      m_arm(&m_armMotorLeft, &m_armMotorRight, &m_leftPotentiometer,&m_rightPotentiometer,&m_leftUpperLimitSwitch,&m_rightUpperLimitSwitch,&m_leftLowerLimitSwitch,&m_rightLowerLimitSwitch, &m_configEditor, &m_driveStation),
      m_aiming(&m_client, &m_driveTrainController, &m_driveStation, &m_lidarHandler, &m_shooterController),
      m_robotController(&m_driveStation, &m_driveTrainController,&m_shooterController, &m_loaderController, &m_flywheel, &m_configEditor, &m_arm, &m_aiming)
{
}
   void RobotInit() override{
      SmartDashboard::init();
      m_leftWheelEncoder.SetDistancePerPulse(m_configEditor.getDouble("leftDistancePerPulse"));
      m_rightWheelEncoder.SetDistancePerPulse(m_configEditor.getDouble("rightDistancePerPulse"));
      m_gyro.Calibrate();
      m_configEditor.showAllKeys();
//TODO: uncomment this block of code
//      cout<<"run init socket function" << endl;
//      m_client.initilizeSocket();
//      if (m_client.m_initGood){
//         cout<<"init good start thread" << endl;
//         std::thread receiveThread(runClient, this, &m_client);
//         receiveThread.detach();
//      }

      m_driveCamera.SetExposureManual(20);
      m_driveCamera.SetWhiteBalanceAuto();
      CameraServer::GetInstance()->SetQuality(50);
      CameraServer::GetInstance()->StartAutomaticCapture("cam1");

      std::thread lidarRun(lidarThread, this, &m_lidarHandler);
      lidarRun.detach();
   }
   void Autonomous (){
      m_driveStation.clearDriveStation();
      bool addedToQueue = false;

      while (IsAutonomous()&& IsEnabled()){
         displayDriverInfo();
         if(!addedToQueue){
            m_robotController.initAutonomousModeQueue();
            addedToQueue = true;
         }
         m_driveStation.snapShot();
         m_driveTrainController.run();
         m_robotController.run();
         m_shooterController.run();
         //m_arm.run();
      }
      m_robotController.clearQueue();
   }

   void OperatorControl(){
      m_driveStation.clearDriveStation();
      std::thread lidarRun(lidarThread, this, &m_lidarHandler);
      lidarRun.detach();
      m_driveTrainController.setGoalState(DriveTrainController::TELEOP);
      m_robotController.setManual();


      while(IsOperatorControl() && IsEnabled()){
         displayDriverInfo();
         m_driveStation.snapShot();
         m_robotController.run();
         m_driveTrainController.run();
         m_shooterController.run();
         //m_aiming.run();
         m_arm.run();
      }
      m_robotController.clearQueue();
   }

   void Test(){
      //Resets the encoders
      m_leftWheelEncoder.Reset();
      m_rightWheelEncoder.Reset();

      m_driveStation.clearDriveStation();

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

         m_loaderController.run();
         m_driveStation.snapShot();
         m_driveTrainController.run();
         m_configEditor.update();
         m_arm.run();
         //            m_shooterController.run();
         //Calls all run functions involved with testing

         //Outputs the encoder value of the left and right wheels
         std::ostringstream outputR;
         outputR << "EncoderR: ";
         outputR << (m_rightWheelEncoder.GetDistance());
         SmartDashboard::PutString("DB/String 0", outputR.str());
         std::ostringstream outputL;
         outputL << "EncoderL: ";
         outputL << (m_leftWheelEncoder.GetDistance());
         SmartDashboard::PutString("DB/String 1", outputL.str());

         //DriveTrainController

         //Aiming Robot Clockwise 90 degrees
         //         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
         //          SmartDashboard::PutString("DB/String 6", ":) Aiming Robot Clockwise 90 Test");
         //        m_driveTrainController.aimRobotClockwise(m_configEditor.getFloat("degree"), m_configEditor.getFloat("motorPower"));
         //      }
         //      if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
         //         m_driveTrainController.driveLidar(36,0.5);
         //      }
         //Aiming Robot Counter Clockwise 90 degrees
//         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonB)){
//           SmartDashboard::PutString("DB/String 6", "Rotation");
//           m_driveTrainController.aimRobotClockwise(90,0.5);
//
//         }
         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonA)){
            SmartDashboard::PutString("DB/String 6", "Arm Preset 1");
            m_arm.moveArmToPosition(1);
         }
         //Aiming Robot Counter Clockwise 90 degrees
         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonB)){
            SmartDashboard::PutString("DB/String 6", "Arm Preset 0.5");
            m_arm.moveArmToPosition(0.5);
         }
         if(m_driveStation.getGamepadButton(DriveStationConstants::buttonX)){
            SmartDashboard::PutString("DB/String 6", "Arm Preset 0.0");
            m_arm.moveArmToPosition(0.0);
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


   void displayDriverInfo(){
      static int _DisplayCounter = 0;



      if((_DisplayCounter % 10) == 0) {

         //Space 0
         std::ostringstream output1;
         output1 << "Drive State " << m_robotController.getState();
         m_driveStation.printToDashboard(output1.str(), 0);

         //Space 1
         std::ostringstream output2;
         output2 << "Distance: " << m_lidarHandler.getFastAverage();
         m_driveStation.printToDashboard(output2.str(), 1);


         //Space 2
         std::ostringstream output3;
         output3 << "Deviaion: " <<  m_aiming.getDeviaion();
         m_driveStation.printToDashboard(output3.str(), 2);

         //Space 3
         string turnDirection;
         std::ostringstream output4;

         if(m_aiming.getDeviaion()<0){
            turnDirection ="Turn Left";
         }
         else {
            turnDirection = "Turn Right";
         }
         output4 << turnDirection;
         m_driveStation.printToDashboard(output4.str(), 3);


         //Space 4
         if (m_loaderController.loaded()) {
            m_driveStation.printToDashboard("Ball loaded", 4);
         }
         else {
            m_driveStation.printToDashboard("Ball not loaded", 4);
         }

         //Space 5

         //Space 6
         Flywheel::STATE flyState = m_flywheel.getCurrentState();
         if (flyState == Flywheel::STATE::READY) {
            m_driveStation.printToDashboard("Flywheel ready", 6);
         }
         else if (flyState == Flywheel::STATE::NOTREADY) {
            m_driveStation.printToDashboard("Flywheel not ready", 6);
         }
         else {
            m_driveStation.printToDashboard("Flywheel off", 6);
         }

         //Space 7
         float dist = m_lidarHandler.getFastAverage();
         if (dist < m_configEditor.getFloat("minDistFlywheel", 24)) {
            m_driveStation.printToDashboard("To Close", 7);
         }
         else if (dist > m_configEditor.getFloat("maxDistFlywheel", 120)) {
            m_driveStation.printToDashboard("To Far", 7);
         }
         else {
            m_driveStation.printToDashboard("In Range", 7);
         }

         //Space 8
         std::ostringstream part8;
         part8 << m_lidarHandler.getResetCount();
         SmartDashboard::PutString("DB/String 8",part8.str());
         //Space 9

      }

      _DisplayCounter++;

   }



};

void lidarThread(Robot * robot, LidarHandler * lidarHandler) {
   while(true) {
      lidarHandler->run();
      Wait(0.1);
   }
}

void runClient(Robot* robot, Client* client){
   client->receivePacket();
}

START_ROBOT_CLASS(Robot);
