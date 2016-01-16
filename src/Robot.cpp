//#include <iostream>
#include <thread>
#include "WPILib.h"
#include "constants.h"
#include "Client.h"

class Robot;

void runClient(Client* client);

class Robot: public SampleRobot
{
   Talon m_flywheels;
   Joystick m_joystick;
   Joystick m_gamepad;

   RobotDrive driveTrain;

   Client client;

public:
   Robot() :
      m_flywheels(Port::flywheels),
      m_joystick(Port::joystick),
      m_gamepad(Port::gamepad),

      driveTrain(Port::frontLeftWheelMotor,
            Port::rearLeftWheelMotor,
            Port::frontRightWheelMotor,
            Port::rearRightWheelMotor)
   {
      //std::thread receiveThread(runClient, client);
      //receiveThread.join();

   }

   void OperatorControl()
   {
      while(IsOperatorControl() && IsEnabled())
      {
         float throttle = - m_joystick.GetY();
         if (abs(throttle) < 0.05f) //This makes a deadzone
         {
             throttle = 0;
         }
         float twist = m_joystick.GetZ();
         if (abs(twist) < 0.05f) //This also makes a deadzone
         {
            twist = 0;
         }
         float throttleRatio = 0.7f;// .8 is too high :(
         float twistRatio = 1 - throttleRatio;
         float leftPower = (throttle * throttleRatio) + (twist * twistRatio);
         float rightPower = (throttle * throttleRatio) - (twist * twistRatio);

         driveTrain.TankDrive(leftPower, rightPower);

         if(m_gamepad.GetRawButton(1))
         {
            m_flywheels.Set(1);
         }
         if(m_gamepad.GetRawButton(2))
         {
            m_flywheels.Set(0);
         }
      }
   }

};

void runClient(Client* client)
   {
      client->receivePacket();
   }

START_ROBOT_CLASS(Robot);
