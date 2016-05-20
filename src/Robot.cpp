#include "WPILib.h"
#include "constants.h"
/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{
    Encoder m_leftDriveEncoder;
    Encoder m_rightDriveEncoder;
    Encoder m_rightFly;
    Encoder m_leftFly;
    Talon m_leftFlywheelMotor;
    Talon m_rightFlywheelMotor;
    Talon m_armMotorLeft;
    Talon m_armMotorRight;
    Talon m_intakeMotor;
    Talon m_stationaryMotor;
    Talon m_leftClimberMotor;
    Talon m_rightClimberMotor;
    Talon m_rightDriveMotorRear;
    Talon m_rightDriveMotorFront;
    Talon m_leftDriveMotorRear;
    Talon m_leftDriveMotorFront;
    Joystick m_gamepad;



public:
    Robot():
        m_leftDriveEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
        m_rightDriveEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
        m_rightFly(PortAssign::leftFlywheelEncoderChannelA, PortAssign::leftFlywheelEncoderChannelB),
        m_leftFly(PortAssign::rightFlywheelEncoderChannelA, PortAssign::rightFlywheelEncoderChannelB),
        m_leftFlywheelMotor(PortAssign::flywheelLeftMotor), //6
        m_rightFlywheelMotor(PortAssign::flywheelRightMotor), //5
        m_armMotorLeft(PortAssign::armMotorLeft), //7
        m_armMotorRight(PortAssign::armMotorRight), //8
        m_intakeMotor(PortAssign::intakeMotor), //4
        m_stationaryMotor(PortAssign::stationaryMotor), //400
        m_leftClimberMotor(PortAssign::leftClimberMotor), //20
        m_rightClimberMotor(PortAssign::rightClimberMotor),//16
        m_rightDriveMotorRear(PortAssign::rearRightWheelMotor), //3
        m_rightDriveMotorFront(PortAssign::frontRightWheelMotor), //2
        m_leftDriveMotorRear(PortAssign::rearLeftWheelMotor), //0
        m_leftDriveMotorFront(PortAssign::frontLeftWheelMotor), //1
        m_gamepad(0)
{
}
    /*
     * X =  5
     * Y =  7
     * A =  6
     * B =  8
     * LT = 1
     * LB = 0
     * RT = 2
     * RB = 3
     * back = 4
     * RJoystick = reverse
     */

    void RobotInit() override{
        CameraServer::GetInstance()->SetQuality(50);
        CameraServer::GetInstance()->StartAutomaticCapture("cam1");
    }
    void OperatorControl()
    {
        int speed = 1;
        while (IsOperatorControl() && IsEnabled())
        {

            std::ostringstream encoders;
            encoders << "L: " << m_leftDriveEncoder.Get() << "R: " << m_rightDriveEncoder.Get();
            SmartDashboard::PutString("DB/String 0",encoders.str());
            if (m_gamepad.GetRawButton(DriveStationConstants::joystickRightButton)){
                speed = -1.0;
            }
            else {
                speed =1.0;
            }

            if(m_gamepad.GetRawButton(DriveStationConstants::buttonA)){
                m_leftFlywheelMotor.Set(speed);
            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonX)){
                m_rightFlywheelMotor.Set(speed);

            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonY)){
                m_armMotorLeft.Set(speed);
            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonB)){
                m_armMotorRight.Set(speed);

            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonLB)){
                m_leftDriveMotorRear.Set(-speed);
            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonRB)){
                m_rightDriveMotorRear.Set(speed);

            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::triggerLT)){
                m_leftDriveMotorFront.Set(-speed);
            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::triggerRT)){
                m_rightDriveMotorFront.Set(speed);

            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonBack)){
                m_intakeMotor.Set(speed);
            }

            else {
               m_intakeMotor.Set(0);
               m_rightDriveMotorRear.Set(0);
               m_leftDriveMotorFront.Set(0);
               m_rightDriveMotorFront.Set(0);
               m_leftDriveMotorRear.Set(0);
               m_leftFlywheelMotor.Set(0);
               m_rightFlywheelMotor.Set(0);
               m_armMotorRight.Set(0);
               m_armMotorLeft.Set(0);
            }
            Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        }
    }
    void Test(){

    }

};

START_ROBOT_CLASS(Robot)
