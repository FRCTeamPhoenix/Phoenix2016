#include "WPILib.h"
#include "constants.h"
/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{
    Encoder m_leftDriveEncoder;
    Encoder m_righDriveEncoder;
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
    Talon m_rightDriveMotor1;
    Talon m_rightDriveMotor2;
    Talon m_leftDriveMotor1;
    Talon m_leftDriveMotor2;
    Joystick m_gamepad;

public:
    Robot():
        m_leftDriveEncoder(PortAssign::leftWheelEncoderChannelA, PortAssign::leftWheelEncoderChannelB),
        m_righDriveEncoder(PortAssign::rightWheelEncoderChannelA, PortAssign::rightWheelEncoderChannelB),
        m_rightFly(PortAssign::leftFlywheelEncoderChannelA, PortAssign::leftFlywheelEncoderChannelB),
        m_leftFly(PortAssign::rightFlywheelEncoderChannelA, PortAssign::rightFlywheelEncoderChannelB),
        m_leftFlywheelMotor(PortAssign::flywheelLeftMotor),
        m_rightFlywheelMotor(PortAssign::flywheelRightMotor),
        m_armMotorLeft(PortAssign::armMotorLeft),
        m_armMotorRight(PortAssign::armMotorRight),
        m_intakeMotor(PortAssign::intakeMotor),
        m_stationaryMotor(PortAssign::stationaryMotor),
        m_leftClimberMotor(PortAssign::leftClimberMotor),
        m_rightClimberMotor(PortAssign::rightClimberMotor),
        m_rightDriveMotor1(PortAssign::frontLeftWheelMotor),
        m_rightDriveMotor2(PortAssign::frontRightWheelMotor),
        m_leftDriveMotor1(PortAssign::rearRightWheelMotor),
        m_leftDriveMotor2(PortAssign::rearLeftWheelMotor),
        m_gamepad(PortAssign::gamepad)
{
}

    void RobotInit() override{
        CameraServer::GetInstance()->SetQuality(50);
        CameraServer::GetInstance()->StartAutomaticCapture("cam1");
    }
    void OperatorControl()
    {
        while (IsOperatorControl() && IsEnabled())
        {
            if(m_gamepad.GetRawButton(DriveStationConstants::buttonA)){
                m_leftFlywheelMotor.Set(1.0);
            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonX)){
                m_rightFlywheelMotor.Set(1.0);

            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonY)){
                m_armMotorLeft.Set(1.0);
            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonB)){
                m_armMotorRight.Set(1.0);
            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonLB)){
                m_leftDriveMotor1.Set(-1.0);
            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonRB)){
                m_rightDriveMotor1.Set(1.0);

            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::triggerLT)){
                m_leftDriveMotor2.Set(-1.0);
            }

            else if(m_gamepad.GetRawButton(DriveStationConstants::triggerRT)){
                m_rightDriveMotor1.Set(1.0);

            }
            else if(m_gamepad.GetRawButton(DriveStationConstants::buttonBack)){
                m_intakeMotor.Set(1.0);
            }
            Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        }
    }
    void Test(){

    }

};

START_ROBOT_CLASS(Robot)
